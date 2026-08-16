#ifndef HAZARD_SPRITEFRAMEENUM_HPP
#define HAZARD_SPRITEFRAMEENUM_HPP

#include "HazardTypedef.hpp"

typedef int32_t SpriteFrameSceneClassUserEnum;

struct SpriteFrameSceneClassUser {
  enum Value {
    Stand = 0,
    Magic = 10,
    SpecialAttack = 12,
  };
};

#endif
