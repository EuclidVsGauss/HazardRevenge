#ifndef HAZARD_INVENTORYITEMWEAPON_HPP
#define HAZARD_INVENTORYITEMWEAPON_HPP
#include "HazardTypedef.hpp"

struct InventoryItemWeapon {
  int32_t quantity;
  int32_t typeId;
  int32_t equipFlags;
  int32_t actOffset;
  int32_t itemGroup;
  int32_t currentPower;
  int32_t maxPower;
  int32_t toHit;
  int32_t maxToHit;
  int32_t resFire;
  int32_t resIce;
  int32_t resLightning;
  int32_t resWind;
  int32_t resLand;
  int32_t numberSharants;
  int32_t mp;
  int32_t nothing[3];
};
typedef struct InventoryItemWeapon InventoryItemWeapon, *PInventoryItemWeapon;

#endif
