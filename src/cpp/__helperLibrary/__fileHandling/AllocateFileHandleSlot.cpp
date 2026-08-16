#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

int32_t AllocateFileHandleSlot(void) {
  for (int32_t slotGroupIndex = 0; slotGroupIndex < 64; ++slotGroupIndex) {
    FileHandleComponent* component = FileHandleComponentAddresses[slotGroupIndex];
    if (component == nullptr) {
      component = (FileHandleComponent*)malloc(sizeof(FileHandleComponent));
      if (component == nullptr) {
        return -1;
      }
      uNumber += 32;
      FileHandleComponentAddresses[slotGroupIndex] = component;
      for (int32_t entryIndex = 0; entryIndex < 32; ++entryIndex) {
        component->entries[entryIndex].handle = INVALID_HANDLE_VALUE;
        component->entries[entryIndex].flags = 0;
        component->entries[entryIndex].stored_char = 10;
      }

      component->entries[0].flags |= 1;
      return slotGroupIndex * 32;
    }

    for (int32_t entryIndex = 0; entryIndex < 32; ++entryIndex) {
      if ((component->entries[entryIndex].flags & 1) == 0) {

        component->entries[entryIndex].flags |= 1;
        component->entries[entryIndex].handle = INVALID_HANDLE_VALUE;
        return (slotGroupIndex * 32) + entryIndex;
      }
    }
  }
  return -1;
}

#pragma optimize("s", off)
