#include "HazardGlobals.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/HandleEntry.hpp"

#pragma optimize("s", on)

int32_t __cdecl SetFileTextModeFlag(uint32_t file_id, int32_t text_mode_flag) {
  if (file_id >= uNumber) {
    HandlesUpperValue = 9;
    return -1;
  }

  uint32_t component_index = (int32_t)file_id >> 5;
  uint32_t slot_index = file_id & 0x1f;
  FileHandleComponent* component = FileHandleComponentAddresses[component_index];
  HandleEntry* entry = &component->entries[slot_index];

  if ((entry->flags & 1) == 0) {
    HandlesUpperValue = 9;
    return -1;
  }

  uint8_t old_flags = entry->flags;

  if (text_mode_flag == 0x8000) {
    entry->flags &= ~0x80;
  }
  else if (text_mode_flag == 0x4000) {
    entry->flags |= 0x80;
  }
  else {
    HandlesUpperValue = 0x16;
    return -1;
  }

  return (-(uint32_t)((old_flags & 0x80) != 0) & 0xffffc000) + 0x8000;
}

#pragma optimize("s", off)
