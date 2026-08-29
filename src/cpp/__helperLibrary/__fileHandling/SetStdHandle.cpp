#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

int32_t __cdecl SetStdHandle_(uint32_t handleId, HANDLE handle) {
  DWORD nStdHandle;
  if (handleId < uNumber) {
    uint32_t componentIndex = (int32_t)handleId >> 5;
    uint32_t slotIndex = handleId & 0x1f;

    if (FileHandleComponentAddresses[componentIndex]->entries[slotIndex].handle == INVALID_HANDLE_VALUE) {
      if (WriteErrorLogConfig == 1) {
        switch (handleId) {
        case 0:
          nStdHandle = STD_INPUT_HANDLE;
          break;
        case 1:
          nStdHandle = STD_OUTPUT_HANDLE;
          break;
        case 2:
          nStdHandle = STD_ERROR_HANDLE;
          break;
        default:
          goto label_skip_set_std_handle;
        }
        SetStdHandle(nStdHandle, handle);
      }
    label_skip_set_std_handle:
      FileHandleComponentAddresses[componentIndex]->entries[slotIndex].handle = handle;
      return 0;
    }
  }
  HandlesLowerValue = 0;
  HandlesUpperValue = 9;
  return -1;
}

#pragma optimize("s", off)
