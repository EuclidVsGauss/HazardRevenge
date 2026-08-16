#ifndef HAZARD_INVENTORYITEMACCESSORY_HPP
#define HAZARD_INVENTORYITEMACCESSORY_HPP
#include "HazardTypedef.hpp"

struct InventoryItemAccessory {
  int32_t quantity;
  int32_t typeId;
  int32_t equipFlags;
  int32_t actOffset;
  int32_t itemGroup;
  int32_t hp;
  int32_t mp;
  int32_t resLand;
  int32_t resLightning;
  int32_t resFire;
  int32_t resWind;
  int32_t resIce;
  int32_t power;
  int32_t maxPower;
  int32_t guard;
  int32_t maxGuard;
  int32_t nothing[3];
};
typedef struct InventoryItemAccessory InventoryItemAccessory, *PInventoryItemAccessory;

#endif
