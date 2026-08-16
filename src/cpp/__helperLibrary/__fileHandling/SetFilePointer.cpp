#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

__declspec(nothrow) int32_t __cdecl SetFilePointer(uint32_t fileHandleId, LONG distanceToMove, DWORD moveMethod) {
  if (fileHandleId >= uNumber) {
    HandlesLowerValue = 0;
    HandlesUpperValue = 9;
    return -1;
  }

  uint32_t componentIndex = (int32_t)fileHandleId >> 5;
  uint32_t slotIndex = fileHandleId & 0x1f;
  FileHandleComponent* component = FileHandleComponentAddresses[componentIndex];
  HandleEntry* entry = &component->entries[slotIndex];

  if ((entry->flags & 1) == 0) {
    HandlesLowerValue = 0;
    HandlesUpperValue = 9;
    return -1;
  }

  HANDLE hFile = entry->handle;
  if (hFile == INVALID_HANDLE_VALUE) {
    HandlesUpperValue = 9;
    return -1;
  }

  DWORD newPos = SetFilePointer(hFile, distanceToMove, nullptr, moveMethod);

  if (newPos == -1) {
    DWORD lastError = GetLastError();
    if (lastError != NO_ERROR) {
      MapErrorCode(lastError);
      return -1;
    }
  }

  entry->flags &= ~0x02;

  return newPos;
}

#pragma optimize("s", off)
