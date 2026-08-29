#ifndef HAZARD_RAWITEMCOLLECTION62400B_HPP
#define HAZARD_RAWITEMCOLLECTION62400B_HPP
#include "HazardStructs/ItemRawStruct.hpp"
#include "HazardTypedef.hpp"

struct ItemRawCollection {
  ItemRawStruct rawItemArray[300];
};
typedef struct ItemRawCollection ItemRawCollection, *PItemRawCollection;

#endif
