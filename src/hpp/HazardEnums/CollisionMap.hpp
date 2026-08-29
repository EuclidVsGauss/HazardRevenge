#ifndef HAZARD_COLLISIONMAPENUM_HPP
#define HAZARD_COLLISIONMAPENUM_HPP

#include "HazardTypedef.hpp"

typedef int32_t CollisionMapEnum;

struct CollisionMap {
  enum Value {
    ImpassableWall = -1,
    EmptyCell = -2,
  };
};

#endif
