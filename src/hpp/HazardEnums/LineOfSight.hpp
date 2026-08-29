#ifndef HAZARD_LINEOFSIGHTENUM_HPP
#define HAZARD_LINEOFSIGHTENUM_HPP

#include "HazardTypedef.hpp"

typedef int32_t LineOfSightEnum;

struct LineOfSight {
  enum Value {
    Transparent = 0,
    Opaque = 1,
  };
};

#endif
