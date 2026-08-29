#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowWeapon.hpp"
#include "HazardExterns/GameWindowWeapon.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"

GameWindowWeapon::GameWindowWeapon() {
  int32_t currentIndex;
  int32_t* frameArrayPtr;

  this->actWin2 = new CoreActClass(s_win2_act);
  frameArrayPtr = &this->actFrame;
  for (currentIndex = 20; currentIndex != 0; currentIndex = currentIndex + -1) {
    *frameArrayPtr = -1;
    frameArrayPtr = frameArrayPtr + 1;
  }
  this->actFrame = this->actWin2->GetActionIndexByName(s_frame);
  this->actSlot = this->actWin2->GetActionIndexByName(s_slot);
  this->staticXBoundary = 0;
  this->dynamicYBoundary = -288;
  this->hideOpenCloseFlag = 0;
  this->latestEquipmentItem.quantity = 0;
}
