#ifndef HAZARD_SMALLWINDOWFRAME_HPP
#define HAZARD_SMALLWINDOWFRAME_HPP
#include "HazardTypedef.hpp"

struct WeaponSlotFrame {
  int32_t itemCoord1;
  int32_t itemCoord2;
  int32_t itemFlag1;
  int32_t itemFlag2;
};
typedef struct WeaponSlotFrame WeaponSlotFrame, *PWeaponSlotFrame;

#endif
