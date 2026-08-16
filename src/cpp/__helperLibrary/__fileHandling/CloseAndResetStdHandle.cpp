#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

int32_t __cdecl CloseAndResetStdHandle(uint32_t file_id) {
  if (file_id >= uNumber) {
    HandlesLowerValue = 0;
    HandlesUpperValue = 9;
    return -1;
  }

  uint32_t component_index = (int32_t)file_id >> 5;
  uint32_t slot_index = file_id & 0x1f;
  FileHandleComponent* component = FileHandleComponentAddresses[component_index];
  HandleEntry* entry = &component->entries[slot_index];

  if ((entry->flags & 1) != 0 && entry->handle != INVALID_HANDLE_VALUE) {
    if (WriteErrorLogConfig == 1) {
      DWORD nStdHandle;
      if (file_id == 0) {
        nStdHandle = STD_INPUT_HANDLE;
      }
      else if (file_id == 1) {
        nStdHandle = STD_OUTPUT_HANDLE;
      }
      else if (file_id == 2) {
        nStdHandle = STD_ERROR_HANDLE;
      }
      else {
        goto label_skip_set_std_handle;
      }
      SetStdHandle(nStdHandle, nullptr);
    }
  label_skip_set_std_handle:
    entry->handle = INVALID_HANDLE_VALUE;
    return 0;
  }

  HandlesLowerValue = 0;
  HandlesUpperValue = 9;
  return -1;
}

#pragma optimize("s", off)
