#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

HANDLE __cdecl GetIndexedFileHandle(uint32_t fileIndex) {
  if (fileIndex < uNumber) {
    FileHandleComponent* component = FileHandleComponentAddresses[(int32_t)fileIndex >> 5];
    uint32_t slotIndex = fileIndex & 0x1f;
    HandleEntry* entry = &component->entries[slotIndex];
    if ((entry->flags & 1) != 0) {
      return entry->handle;
    }
  }
  HandlesLowerValue = 0;
  HandlesUpperValue = 9;
  return INVALID_HANDLE_VALUE;
}

#pragma optimize("s", off)
