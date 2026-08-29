#ifndef HAZARD_SPELLTYPEENUM_HPP
#define HAZARD_SPELLTYPEENUM_HPP

#include "HazardTypedef.hpp"

typedef int32_t SpellTypeEnum;

struct SpellType {
  enum Value {
    Magic = 1,
    Special = 2,
    Summon = 3,
  };
};

#endif
