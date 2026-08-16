#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

int32_t __cdecl WriteFileWithTranslation(DWORD file_id, char* buffer, uint32_t nBytesToWrite) {
  if (file_id >= uNumber) {
    HandlesLowerValue = 0;
    HandlesUpperValue = 9;
    return -1;
  }

  uint32_t component_index = file_id >> 5;
  uint32_t slot_index = file_id & 0x1f;
  FileHandleComponent* component = FileHandleComponentAddresses[component_index];
  HandleEntry* file_entry = &component->entries[slot_index];

  if ((file_entry->flags & 1) == 0) {
    HandlesLowerValue = 0;
    HandlesUpperValue = 9;
    return -1;
  }

  if (nBytesToWrite == 0) {
    return 0;
  }

  if ((file_entry->flags & 0x20) != 0) {
    SetFilePointer(file_id, 0, 2);
  }

  DWORD total_bytes_written = 0;
  DWORD error_code = 0;

  if ((file_entry->flags & 0x80) == 0) {
    BOOL write_success = WriteFile(file_entry->handle, buffer, nBytesToWrite, &total_bytes_written, nullptr);
    if (!write_success) {
      error_code = GetLastError();
    }
  }
  else {
    char local_buffer[1024];
    char* current_pos = buffer;
    char* end_pos = buffer + nBytesToWrite;

    while (current_pos < end_pos) {
      char* write_buffer_ptr = local_buffer;
      char* buffer_end = local_buffer + sizeof(local_buffer);
      char* line_start = current_pos;

      while (current_pos < end_pos && write_buffer_ptr < buffer_end) {
        if (*current_pos == '\n') {
          if (write_buffer_ptr + 1 < buffer_end) {
            *write_buffer_ptr++ = '\r';
            *write_buffer_ptr++ = '\n';
          }
          else {
            break;
          }
        }
        else {
          *write_buffer_ptr++ = *current_pos;
        }
        current_pos++;
      }

      DWORD chunk_size = write_buffer_ptr - local_buffer;
      if (chunk_size > 0) {
        DWORD bytes_written_now = 0;
        BOOL write_success = WriteFile(file_entry->handle, local_buffer, chunk_size, &bytes_written_now, nullptr);
        total_bytes_written += (current_pos - line_start);
        if (!write_success) {
          error_code = GetLastError();
          break;
        }
        if (bytes_written_now < chunk_size) {
          break;
        }
      }
    }
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

  if (total_bytes_written > 0) {
    return total_bytes_written;
  }

  if (((file_entry->flags & 0x40) != 0) && (*buffer == 0x1a)) {
    return 0;
  }

  HandlesUpperValue = 28;
  HandlesLowerValue = 0;
  return -1;
}

#pragma optimize("s", off)
