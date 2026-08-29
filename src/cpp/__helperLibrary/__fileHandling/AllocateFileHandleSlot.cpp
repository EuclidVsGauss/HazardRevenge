#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

int32_t AllocateFileHandleSlot(void) {
  FileHandleComponent** componentSlot = FileHandleComponentAddresses;
  HandleEntry* entry;
  HandleEntry* entryEnd;
  int32_t slotBase = 0;
  int32_t groupIndex = 0;
  int32_t result = -1;

  while (componentSlot < &FileHandleComponentAddresses[64]) {
    FileHandleComponent* component = *componentSlot;
    if (component == nullptr) {
      component = (FileHandleComponent*)malloc(sizeof(FileHandleComponent));
      if (component == nullptr) {
        break;
      }
      uNumber += 32;
      *componentSlot = component;

      entry = component->entries;
      entryEnd = component->entries + 32;
      while (entry < entryEnd) {
        entry->handle = INVALID_HANDLE_VALUE;
        entry->flags = 0;
        entry->stored_char = 10;
        entry++;
      }

      result = groupIndex * 32;
      break;
    }

    entry = component->entries;
    entryEnd = component->entries + 32;
    while (entry < entryEnd) {
      if ((entry->flags & 1) == 0) {
        entry->handle = INVALID_HANDLE_VALUE;
        result = slotBase + (int32_t)(entry - component->entries);
        break;
      }
      entry++;
    }
    if (result != -1) {
      break;
    }

    componentSlot++;
    groupIndex++;
    slotBase += 32;
  }

  return result;
}

#pragma optimize("s", off)
