#ifndef HAZARD_DOORSTATE_HPP
#define HAZARD_DOORSTATE_HPP

#include "HazardTypedef.hpp"

typedef int32_t DoorStateEnum;

struct DoorState {
  enum Value {
    Open = 0,
    Closed = 1,
    Opening = 2,
  };
};

#endif
