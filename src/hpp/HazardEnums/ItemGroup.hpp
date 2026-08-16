#ifndef HAZARD_ITEMGROUP_HPP
#define HAZARD_ITEMGROUP_HPP

#include "HazardTypedef.hpp"

typedef int32_t ItemGroupEnum;

struct ItemGroup {
  enum Value {
    Gold = 1,
    HpRecovery = 2,
    MpRecovery = 3,
    StatusRecovery = 4,
    HoldableItem = 5,
    Map = 6,
  };
};

#endif
