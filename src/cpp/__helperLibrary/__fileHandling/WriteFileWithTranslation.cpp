#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

int32_t __cdecl WriteFileWithTranslation(DWORD file_id, char* buffer, uint32_t nBytesToWrite) {
  if (file_id < uNumber) {

    uint32_t component_index = (int32_t)file_id >> 5;
    uint32_t slot_index = file_id & 0x1f;

    if ((FileHandleComponentAddresses[component_index]->entries[slot_index].flags & 1) != 0) {

      DWORD total_bytes_written = 0;
      DWORD error_code = 0;
      DWORD translatedByteCount = 0;

      if (nBytesToWrite == 0) {
        return 0;
      }

      if ((FileHandleComponentAddresses[component_index]->entries[slot_index].flags & 0x20) != 0) {
        SetFilePointer(file_id, 0, 2);
      }

      if ((FileHandleComponentAddresses[component_index]->entries[slot_index].flags & 0x80) == 0) {
        DWORD bytes_written_now = 0;
        BOOL write_success = WriteFile(FileHandleComponentAddresses[component_index]->entries[slot_index].handle, buffer, nBytesToWrite, &bytes_written_now, nullptr);
        if (write_success) {
          total_bytes_written = bytes_written_now;
        }
        else {
          error_code = GetLastError();
        }
      }
      else {
        char local_buffer[1024];
        char* current_pos = buffer;

        while ((int32_t)(current_pos - buffer) < nBytesToWrite) {
          char* write_buffer_ptr = local_buffer;

          do {
            char ch = *current_pos++;
            if (ch == '\n') {
              translatedByteCount++;
              *write_buffer_ptr++ = '\r';
            }
            *write_buffer_ptr++ = ch;
          } while ((int32_t)(write_buffer_ptr - local_buffer) < (int32_t)sizeof(local_buffer));

          DWORD chunk_size = write_buffer_ptr - local_buffer;
          DWORD bytes_written_now = 0;
          BOOL write_success = WriteFile(FileHandleComponentAddresses[component_index]->entries[slot_index].handle, local_buffer, chunk_size, &bytes_written_now, nullptr);
          if (!write_success) {
            error_code = GetLastError();
            break;
          }
          total_bytes_written += bytes_written_now;
          if (bytes_written_now < chunk_size) {
            break;
          }
        }
      }

      if (total_bytes_written > 0) {
        return total_bytes_written - translatedByteCount;
      }

      if (error_code != 0) {
        if (error_code == ERROR_ACCESS_DENIED) {
          HandlesUpperValue = 9;
          HandlesLowerValue = 5;
        }
        else {
          MapErrorCode(error_code);
        }
        return -1;
      }

      if (((FileHandleComponentAddresses[component_index]->entries[slot_index].flags & 0x40) != 0) && (*buffer == 0x1a)) {
        return 0;
      }

      HandlesUpperValue = 28;
      HandlesLowerValue = 0;
      return -1;
    }
  }

  HandlesLowerValue = 0;
  HandlesUpperValue = 9;
  return -1;
}

#pragma optimize("s", off)
