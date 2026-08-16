#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassAniBg_RestoreItemAndSpellcasterAura.hpp"
#include "HazardGlobals.hpp"

SceneClassAniBg_RestoreItemAndSpellcasterAura::SceneClassAniBg_RestoreItemAndSpellcasterAura(char* actName, int32_t positionX, int32_t positionY) {
  CoreActClass* actObject;
  int32_t standActionIndex;

  actObject = new CoreActClass(actName);
  this->actObject = actObject;
  standActionIndex = actObject->GetActionIndexByName(s_stand);
  this->actOffsetStand = standActionIndex;
  standActionIndex = this->actObject->GetFrameCountForAction(standActionIndex);
  this->frame_or_actValueStand = standActionIndex;
  this->truncatedRng = 0;
  this->UpdateObjectOnGrid(positionX << 4, positionY << 4);
}
