#ifndef HAZARD_ITEMCOLLECTION12000B_HPP
#define HAZARD_ITEMCOLLECTION12000B_HPP
#include "HazardStructs/ItemReferenceStruct.hpp"
#include "HazardTypedef.hpp"

struct ItemReferenceCollection {
  ItemReferenceStruct itemArray[500];
};
typedef struct ItemReferenceCollection ItemReferenceCollection, *PItemReferenceCollection;

#endif
