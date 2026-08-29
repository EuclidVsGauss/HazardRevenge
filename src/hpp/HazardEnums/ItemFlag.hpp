#ifndef HAZARD_ITEMFLAG_HPP
#define HAZARD_ITEMFLAG_HPP

#include "HazardTypedef.hpp"

typedef int32_t EquipFlagEnum;

struct ItemFlag {
  enum Value {
    Unknown_2 = 2,
    SellRelated_4 = 4,
    AlsoWindow_0x10 = 0x10,
    Scene_0x20 = 0x20,
    WindowSlot_0x40 = 0x40,
    Value_0x100 = 0x100,
    Value_0x200 = 0x200,
    Value_0x300 = 0x300,
    Value_0x500 = 0x500,

    WindowRelated_0x600 = 0x600,
    SellAndWindowRelated_0x700 = 0x700,
  };
};

#endif
