#ifndef HAZARD_INTERNALKEYENUM_HPP
#define HAZARD_INTERNALKEYENUM_HPP

#include "HazardTypedef.hpp"

typedef int32_t InternalKeyEnum;

struct InternalKey {
  enum Value {
    InternalKey_ESCAPE = 1,
    InternalKey_1 = 2,
    InternalKey_2 = 3,
    InternalKey_3 = 4,
    InternalKey_4 = 5,
    InternalKey_5 = 6,
    InternalKey_SPACE = 57,
    InternalKey_W = 17,
    InternalKey_I = 23,
    InternalKey_C = 46,
    InternalKey_P = 50,
    InternalKey_F1 = 59,
    InternalKey_F2 = 60,
    InternalKey_F3 = 61,
    InternalKey_F4 = 62,
    InternalKey_M = 68,
    InternalKey_UP = 72,
    InternalKey_LEFT = 75,
    InternalKey_RIGHT = 77,
    InternalKey_DOWN = 80,
    InternalKey_F11 = 87,
    InternalKey_CONTROL = 29,
  };
};

#endif
