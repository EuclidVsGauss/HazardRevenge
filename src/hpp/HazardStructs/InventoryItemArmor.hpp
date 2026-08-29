#ifndef HAZARD_INVENTORYITEMARMOR_HPP
#define HAZARD_INVENTORYITEMARMOR_HPP
#include "HazardTypedef.hpp"

struct InventoryItemArmor {
  int32_t quantity;
  int32_t typeId;
  int32_t equipFlags;
  int32_t actOffset;
  int32_t itemGroup;
  int32_t currentPower;
  int32_t maxPower;
  int32_t currentToHit;
  int32_t maxToHit;
  int32_t currentGuard;
  int32_t maxGuard;
  int32_t currentSpeed;
  int32_t maxSpeed;
  int32_t resFire;
  int32_t resIce;
  int32_t resLightning;
  int32_t resWind;
  int32_t resLand;
  int32_t mp;
};
typedef struct InventoryItemArmor InventoryItemArmor, *PInventoryItemArmor;

#endif
