#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassButton.hpp"
#include "HazardExterns/SceneClassButton.hpp"
#include "HazardGlobals.hpp"

SceneClassButton::SceneClassButton(int32_t coord1, int32_t coord2, int32_t orientation, int32_t gameFlag, char* actFilename) {
  CoreActClass* buttonActObject;

  buttonActObject = new CoreActClass(actFilename);
  this->fileObject = buttonActObject;
  this->spriteIndex = orientation;
  this->actSpriteIndex = buttonActObject->GetActionIndexByName(Button_s_fstand[orientation]);
  this->gameFlag = gameFlag;
  this->openStatus = 0;
  this->counter = 0;
  this->UpdateObjectOnGrid(coord1 << 4, coord2 << 4);
}
