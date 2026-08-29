#ifndef HAZARD_UNLOCKDOORTUPLE_HPP
#define HAZARD_UNLOCKDOORTUPLE_HPP
#include "HazardTypedef.hpp"

struct UnlockDoorTuple {
  int32_t value1;
  int32_t value2;
};
typedef struct UnlockDoorTuple UnlockDoorTuple, *PUnlockDoorTuple;

#endif
