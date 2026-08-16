#ifndef HAZARD_INVENTORYITEMBOOTS_HPP
#define HAZARD_INVENTORYITEMBOOTS_HPP
#include "HazardTypedef.hpp"

struct InventoryItemBoots {
  int32_t quantity;
  int32_t typeId;
  int32_t equipFlags;
  int32_t actOffset;
  int32_t itemGroup;
  int32_t speed;
  int32_t resFire;
  int32_t resIce;
  int32_t resLightning;
  int32_t resWind;
  int32_t resLand;
  int32_t nothing[8];
};
typedef struct InventoryItemBoots InventoryItemBoots, *PInventoryItemBoots;

#endif
