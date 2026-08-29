#ifndef HAZARD_INVENTORYITEMBRACER_HPP
#define HAZARD_INVENTORYITEMBRACER_HPP
#include "HazardTypedef.hpp"

struct InventoryItemBracer {
  int32_t quantity;
  int32_t typeId;
  int32_t equipFlags;
  int32_t actOffset;
  int32_t itemGroup;
  int32_t currentPower;
  int32_t maxPower;
  int32_t currentGuard;
  int32_t maxGuard;
  int32_t resLand;
  int32_t nothing[9];
};
typedef struct InventoryItemBracer InventoryItemBracer, *PInventoryItemBracer;

#endif
