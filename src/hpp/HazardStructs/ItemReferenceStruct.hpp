#ifndef HAZARD_ITEMPTRSTRUCT12000BCOPY_HPP
#define HAZARD_ITEMPTRSTRUCT12000BCOPY_HPP
#include "HazardTypedef.hpp"

struct ItemStatsTemplate;

struct ItemReferenceStruct {
  int32_t equipFlags;
  int32_t actOffset;
  int32_t price;
  char* name;
  char* description;
  ItemStatsTemplate* stats;
};
typedef struct ItemReferenceStruct ItemReferenceStruct, *PItemReferenceStruct;

#endif
