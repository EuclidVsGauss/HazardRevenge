#include "HazardClasses/BloodObject.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardExterns/BloodObject.hpp"
#include "HazardGlobals.hpp"

BloodObject::BloodObject(int32_t coordinate1, int32_t coordinate2, int32_t rng) {
  CoreActClass* actObject;
  int32_t actionIndex;

  if (BloodActObject == nullptr) {
    BloodActObject = new CoreActClass(s_blood_act);
    BloodActStand = BloodActObject->GetActionIndexByName(s_stand);
    actObject = BloodActObject;
    actionIndex = BloodActObject->GetActionIndexByName(s_stand);
    NestedContentFromAct = actObject->GetFrameCountForAction(actionIndex);
  }
  this->spriteFrameIndex = 0;
  this->spriteOrientation = (rng - 4) & 7;
  this->UpdateObjectOnGrid(coordinate1 << 4, coordinate2 << 4);
}
