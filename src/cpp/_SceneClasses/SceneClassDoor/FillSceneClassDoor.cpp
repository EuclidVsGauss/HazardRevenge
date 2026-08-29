#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassDoor.hpp"
#include "HazardExterns/SceneClassDoor.hpp"
#include "HazardGlobals.hpp"

SceneClassDoor::SceneClassDoor(int32_t coord1, int32_t coord2, int32_t orientation, int32_t gameFlag, char* fileName) {
  CoreActClass* actObject;

  actObject = new CoreActClass(fileName);
  this->actClass = actObject;
  this->actStand = actObject->GetActionIndexByName(s_fstand);
  this->doorUnlockType = orientation;
  this->gameFlag = gameFlag;
  this->currentState = GameFlags[gameFlag] != 0;
  this->UpdateObjectOnGrid(coord1 << 4, coord2 << 4);
}
