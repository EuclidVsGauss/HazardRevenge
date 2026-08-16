#ifndef HAZARD_INVENTORYITEMSHARANT_HPP
#define HAZARD_INVENTORYITEMSHARANT_HPP
#include "HazardTypedef.hpp"

struct InventoryItemSharant {
  int32_t quantity;
  int32_t typeId;
  int32_t equipFlags;
  int32_t actOffset;
  int32_t itemGroup;
  int32_t nothing[14];
};
typedef struct InventoryItemSharant InventoryItemSharant, *PInventoryItemSharant;

#endif
