#include "HazardClasses/AnimationSummon.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardGlobals.hpp"

AnimationSummon::AnimationSummon(char* resourceName) {
  CoreActClass* coreAct;
  int32_t standActIndex;

  coreAct = new CoreActClass(resourceName);
  this->coreActClass = coreAct;
  standActIndex = coreAct->GetActionIndexByName(s_stand);
  this->firstStandActIndex = standActIndex;
  this->maxStandActIndex = this->coreActClass->GetFrameCountForAction(standActIndex);
  this->currentStandIndex = 0;
}
