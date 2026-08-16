#ifndef HAZARD_INVENTORYITEMSTRUCT_HPP
#define HAZARD_INVENTORYITEMSTRUCT_HPP
#include "HazardTypedef.hpp"

struct InventoryItemStruct {
  int32_t quantity;
  int32_t typeId;
  int32_t equipFlags;
  int32_t actOffset;
  int32_t itemGroup;
  int32_t aParameter;
  int32_t bParameter;
  int32_t cParameter;
  int32_t dParameter;
  int32_t eParameter;
  int32_t fParameter;
  int32_t gParameter;
  int32_t hParameter;
  int32_t iParameter;
  int32_t jParameter;
  int32_t kParameter;
  int32_t lParameter;
  int32_t mParameter;
  int32_t nParameter;
};
typedef struct InventoryItemStruct InventoryItemStruct, *PInventoryItemStruct;

#endif
