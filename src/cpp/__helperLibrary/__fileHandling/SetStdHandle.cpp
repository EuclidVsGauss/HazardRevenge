#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

int32_t __cdecl SetStdHandle_(uint32_t handleId, HANDLE handle) {
  DWORD nStdHandle;
  if (handleId < uNumber) {
    FileHandleComponent* component = FileHandleComponentAddresses[(int32_t)handleId >> 5];
    uint32_t slotIndex = handleId & 0x1f;
    HandleEntry* entry = &component->entries[slotIndex];

    if (entry->handle == INVALID_HANDLE_VALUE) {
      if (WriteErrorLogConfig == 1) {
        if (handleId == 0) {
          nStdHandle = STD_INPUT_HANDLE;
        }
        else if (handleId == 1) {
          nStdHandle = STD_OUTPUT_HANDLE;
        }
        else {
          if (handleId != 2) {
            goto label_skip_set_std_handle;
          }
          nStdHandle = STD_ERROR_HANDLE;
        }
        SetStdHandle(nStdHandle, handle);
      }
    label_skip_set_std_handle:
      entry->handle = handle;
      entry->flags = 1;
      return 0;
    }
  }
  HandlesLowerValue = 0;
  HandlesUpperValue = 9;
  return -1;
}

#pragma optimize("s", off)
