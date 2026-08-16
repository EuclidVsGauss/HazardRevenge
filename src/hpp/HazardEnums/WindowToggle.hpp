#ifndef HAZARD_WINDOWTOGGLEENUM_HPP
#define HAZARD_WINDOWTOGGLEENUM_HPP

#include "HazardTypedef.hpp"

typedef int32_t WindowToggleEnum;

struct WindowToggle {
  enum Value {
    Hidden = 0,
    Opening = 1,
    Closing = 2,
  };
};

#endif
