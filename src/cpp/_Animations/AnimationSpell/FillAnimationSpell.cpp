#include "HazardClasses/AnimationSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardGlobals.hpp"

AnimationSpell::AnimationSpell(char* actName, int32_t coord1, int32_t coord2) {
  int32_t standActionIndex;

  this->actWithSfx = new CoreActClass(actName);
  standActionIndex = this->actWithSfx->GetActionIndexByName(s_stand);
  this->stand = standActionIndex;
  this->numberOfFramesForStandAnimation = this->actWithSfx->GetFrameCountForAction(standActionIndex);
  this->presumablyCurrentAnimationIndex = 0;
  this->UpdateObjectOnGrid(coord1 << 4, coord2 << 4);
}
