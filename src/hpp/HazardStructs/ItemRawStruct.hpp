#ifndef HAZARD_RAWITEMSTRUCT208B_HPP
#define HAZARD_RAWITEMSTRUCT208B_HPP
#include "HazardTypedef.hpp"

struct ItemRawStruct {
  int32_t ItemId;
  int32_t EquipmentFlags;
  int32_t Price;
  char actKeyword[10];
  char Name[42];
  char Description[80];
  int32_t StatsArray[16];
};
typedef struct ItemRawStruct ItemRawStruct, *PItemRawStruct;

#endif
