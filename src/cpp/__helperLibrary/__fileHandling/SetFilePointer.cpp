#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

__declspec(nothrow) int32_t __cdecl SetFilePointer(uint32_t fileHandleId, LONG distanceToMove, DWORD moveMethod) {
  if (fileHandleId < uNumber) {
    uint32_t componentIndex = (int32_t)fileHandleId >> 5;
    uint32_t slotIndex = fileHandleId & 0x1f;

    if ((FileHandleComponentAddresses[componentIndex]->entries[slotIndex].flags & 1) != 0) {
      HANDLE hFile = GetIndexedFileHandle(fileHandleId);
      if (hFile == INVALID_HANDLE_VALUE) {
        HandlesUpperValue = 9;
        return -1;
      }

      DWORD newPos = SetFilePointer(hFile, distanceToMove, nullptr, moveMethod);

      DWORD lastError = (newPos == -1) ? GetLastError() : NO_ERROR;
      if (lastError != NO_ERROR) {
        MapErrorCode(lastError);
        return -1;
      }

      FileHandleComponentAddresses[componentIndex]->entries[slotIndex].flags &= ~0x02;

      return newPos;
    }
  }

  HandlesLowerValue = 0;
  HandlesUpperValue = 9;
  return -1;
}

#pragma optimize("s", off)
