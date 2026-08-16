#ifndef HAZARD_CURSORSPRITEENUM_HPP
#define HAZARD_CURSORSPRITEENUM_HPP

#include "HazardTypedef.hpp"

typedef int32_t CursorSpriteEnum;

struct CursorSprite {
  enum Value {
    Normal = 0,
    Go = 1,
    DontGo = 2,
    Select = 3,
    Attack = 4,
    Ctrl = 5,
    Board = 6,
    Outofsight = 7,
    Magic = 8,
    GetTalk = 9,
    OpenPickup = 10,
    Talk_unconfirmed = 11,
    Warp = 12,

  };
};

#endif
