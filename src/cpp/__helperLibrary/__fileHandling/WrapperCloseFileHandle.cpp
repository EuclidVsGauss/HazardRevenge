#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

int32_t __cdecl WrapperCloseFileHandle(uint32_t handleIndex) {
  if (handleIndex < uNumber) {
    uint32_t componentIndex = handleIndex >> 5;
    uint32_t slotIndex = handleIndex & 0x1f;

    if ((FileHandleComponentAddresses[componentIndex]->entries[slotIndex].flags & 1) != 0) {
      DWORD lastError = 0;

      if (GetIndexedFileHandle(handleIndex) != INVALID_HANDLE_VALUE) {
        if (handleIndex == 1 || handleIndex == 2) {
          HANDLE hStderr = GetIndexedFileHandle(2);
          HANDLE hStdout = GetIndexedFileHandle(1);
          if (hStdout == hStderr) {
            goto label_skip_close;
          }
        }

        if (!CloseHandle(GetIndexedFileHandle(handleIndex))) {
          lastError = GetLastError();
        }
      }

    label_skip_close:
      CloseAndResetStdHandle(handleIndex);
      FileHandleComponentAddresses[componentIndex]->entries[slotIndex].flags = 0;

      if (lastError == 0) {
        return 0;
      }

      MapErrorCode(lastError);
      return -1;
    }
  }

  HandlesLowerValue = 0;
  HandlesUpperValue = 9;
  return -1;
}

#pragma optimize("s", off)
