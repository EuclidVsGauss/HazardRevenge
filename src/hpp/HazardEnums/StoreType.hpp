#ifndef HAZARD_STORETYPEENUM_HPP
#define HAZARD_STORETYPEENUM_HPP

#include "HazardTypedef.hpp"

typedef int32_t StoreTypeEnum;

struct StoreType {
  enum Value {
    ItemStore = 0,
    OrdinanceStore = 1,
  };
};

#endif
