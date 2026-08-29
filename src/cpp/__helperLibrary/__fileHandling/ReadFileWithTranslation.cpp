#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

__declspec(nothrow) int32_t __cdecl ReadFileWithTranslation(uint32_t file_id, byte* buffer, int32_t nBytesToRead) {
  if (file_id < uNumber) {

    uint32_t component_index = (int32_t)file_id >> 5;
    uint32_t slot_index = file_id & 0x1f;

    if ((FileHandleComponentAddresses[component_index]->entries[slot_index].flags & 1) != 0) {

      DWORD bytes_were_read = 0;
      int32_t total_bytes_read = 0;

      if (nBytesToRead == 0 || (FileHandleComponentAddresses[component_index]->entries[slot_index].flags & 2) != 0) {
        return 0;
      }

      byte* current_buffer_pos = buffer;
      if (((FileHandleComponentAddresses[component_index]->entries[slot_index].flags & 0x48) != 0) && (FileHandleComponentAddresses[component_index]->entries[slot_index].stored_char != 10)) {
        if (nBytesToRead > 0) {
          nBytesToRead--;
          *current_buffer_pos = FileHandleComponentAddresses[component_index]->entries[slot_index].stored_char;
          current_buffer_pos++;
          total_bytes_read = 1;
          FileHandleComponentAddresses[component_index]->entries[slot_index].stored_char = 10;
        }
      }

      if (nBytesToRead > 0) {
        BOOL read_success = ReadFile(FileHandleComponentAddresses[component_index]->entries[slot_index].handle, current_buffer_pos, nBytesToRead, &bytes_were_read, nullptr);

        if (!read_success) {
          DWORD error = GetLastError();
          if (error == ERROR_ACCESS_DENIED) {
            HandlesUpperValue = 9;
            HandlesLowerValue = 5;
            return -1;
          }
          if (error == ERROR_BROKEN_PIPE) {
            return total_bytes_read;
          }
          MapErrorCode(error);
          return -1;
        }
        total_bytes_read += bytes_were_read;
      }

      if ((FileHandleComponentAddresses[component_index]->entries[slot_index].flags & 0x80) == 0) {
        return total_bytes_read;
      }

      byte* read_ptr = buffer;
      byte* write_ptr = buffer;
      byte* end_ptr = buffer + total_bytes_read;

      while (read_ptr < end_ptr) {
        if (*read_ptr == 0x1a) {
          if ((FileHandleComponentAddresses[component_index]->entries[slot_index].flags & 0x40) == 0) {
            FileHandleComponentAddresses[component_index]->entries[slot_index].flags |= 2;
          }
          break;
        }

        if (*read_ptr == 0x0d) {
          if (read_ptr + 1 >= end_ptr) {
            byte lookaheadChar;
            DWORD lookaheadBytesRead = 0;
            read_ptr++;
            if ((!ReadFile(FileHandleComponentAddresses[component_index]->entries[slot_index].handle, &lookaheadChar, 1, &lookaheadBytesRead, nullptr) && GetLastError() != 0) || lookaheadBytesRead == 0) {
              *write_ptr++ = 0x0d;
            }
            else if ((FileHandleComponentAddresses[component_index]->entries[slot_index].flags & 0x48) != 0) {
              if (lookaheadChar == 0x0a) {
                *write_ptr++ = 0x0a;
              }
              else {
                *write_ptr++ = 0x0d;
                FileHandleComponentAddresses[component_index]->entries[slot_index].stored_char = lookaheadChar;
              }
            }
            else if (write_ptr == buffer && lookaheadChar == 0x0a) {
              *write_ptr++ = 0x0a;
            }
            else {
              SetFilePointer(file_id, -1, 1);
              if (lookaheadChar != 0x0a) {
                *write_ptr++ = 0x0d;
              }
            }
          }
          else if (read_ptr[1] == 0x0a) {
            read_ptr += 2;
            *write_ptr++ = 0x0a;
          }
          else {
            *write_ptr++ = 0x0d;
            read_ptr++;
          }
        }
        else {
          *write_ptr++ = *read_ptr++;
        }
      }

      return write_ptr - buffer;
    }
  }

  HandlesLowerValue = 0;
  HandlesUpperValue = 9;
  return -1;
}

#pragma optimize("s", off)
