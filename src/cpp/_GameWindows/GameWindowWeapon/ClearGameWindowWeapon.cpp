#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowWeapon.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"

GameWindowWeapon::~GameWindowWeapon() {
  CoreActClass* actWindow2;

  if (0 < this->latestEquipmentItem.quantity) {
    this->primarySwitchSingleParam(0x7d2e, (intptr_t)(&this->latestEquipmentItem), 1);
  }

  this->mainSceneHandler->primarySwitchSingleParam(0x7d14, 0, 0x2);
  this->mainSceneHandler->primarySwitchSingleParam(0x7d16, 3, 0x0);

  actWindow2 = this->actWin2;
  if (actWindow2 != nullptr) {
    delete actWindow2;
  }
}
