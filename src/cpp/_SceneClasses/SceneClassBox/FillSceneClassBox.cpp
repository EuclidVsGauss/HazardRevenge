#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassBox.hpp"
#include "HazardExterns/SceneClassBox.hpp"
#include "HazardGlobals.hpp"

SceneClassBox::SceneClassBox(int32_t possCord1, int32_t possCord2, int32_t gameFlag, int32_t standAnimationIndex, char* fileName) {
  CoreActClass* fileObj;

  fileObj = new CoreActClass(fileName);
  this->fileObject = fileObj;
  this->chestDirectionIndex = standAnimationIndex;
  if (GameFlags[gameFlag] != 0) {
    standAnimationIndex = standAnimationIndex + 4;
  }
  this->actionIndex = fileObj->GetActionIndexByName(Box_s_fstand[standAnimationIndex]);
  this->gameFlag = gameFlag;
  this->openStatus = (GameFlags[gameFlag] != 0) ? 2 : 0;
  this->UpdateObjectOnGrid(possCord1 << 4, possCord2 << 4);
}
