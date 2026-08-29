#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardGlobals.hpp"

AnimationStatusSpell::AnimationStatusSpell(char* actName, int32_t gridX, int32_t gridY, int32_t repeatCount) {
  CoreActClass* actObject;
  int32_t actionIdx;

  actObject = new CoreActClass(actName);
  this->coreActClass = actObject;
  actionIdx = actObject->GetActionIndexByName(s_stand);
  this->actionIndex = actionIdx;
  actionIdx = this->coreActClass->GetFrameCountForAction(actionIdx);
  this->actionFrameCount = actionIdx;
  this->currentFrameIndex = 0;
  this->repeatCounter = repeatCount;
  this->UpdateObjectOnGrid(gridX << 4, gridY << 4);
}
