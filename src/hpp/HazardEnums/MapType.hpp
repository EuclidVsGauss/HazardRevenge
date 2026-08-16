#ifndef HAZARD_MAPTYPEENUM_HPP
#define HAZARD_MAPTYPEENUM_HPP

#include "HazardTypedef.hpp"

typedef int32_t MapTypeEnum;

struct MapType {
  enum Value {
    Field = 0,
    Village = 1,
    World = 2,
  };
};

#endif
