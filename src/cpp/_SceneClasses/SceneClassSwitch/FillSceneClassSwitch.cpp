#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassSwitch.hpp"
#include "HazardExterns/SceneClassSwitch.hpp"
#include "HazardGlobals.hpp"

SceneClassSwitch::SceneClassSwitch(int32_t coord1, int32_t coord2, int32_t directionIndex, int32_t gameFlagIndex, char* actFile, int32_t isPermanent) {
  CoreActClass* actObject;
  int32_t actionIndex;
  char* actionKeyword;
  uint32_t state;

  actObject = new CoreActClass(actFile);
  this->isPermanent = isPermanent;
  this->actObject = actObject;
  this->directionIndex = directionIndex;
  this->gameFlagIndex = gameFlagIndex;
  state = (GameFlags[gameFlagIndex] != 0) ? 2 : 0;
  this->currentState = state;
  if (state == 0) {
    actionKeyword = Switch_s_fstand[directionIndex];
  }
  else {
    actionKeyword = Switch_s_fopened[directionIndex];
  }
  actionIndex = actObject->GetActionIndexByName(actionKeyword);
  this->actionIndex = actionIndex;
  this->currentFrame = 0;
  this->UpdateObjectOnGrid(coord1 << 4, coord2 << 4);
}
