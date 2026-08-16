#ifndef HAZARD_UnitStatusCondition_HPP
#define HAZARD_UnitStatusCondition_HPP

#include "HazardTypedef.hpp"

typedef int32_t UnitStatusConditionEnum;

struct UnitStatusCondition {
  enum Value {
    Normal = 0,

    Dead = 666,
    DyingRelatesToFlag0x400 = 667,
    DialogueWhileDying = 1818,

    DarkenedEye = 0x7d22,
    Wander_Confused = 0x7d23,
    Gloomy_Stopped = 0x7d24,
    Frozen_Stopped = 0x7d25,
  };
};

#endif
