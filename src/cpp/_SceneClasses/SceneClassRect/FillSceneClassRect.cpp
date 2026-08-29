#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassRect.hpp"
#include "HazardGlobals.hpp"

SceneClassRect::SceneClassRect(int32_t lowerX, int32_t lowerY, int32_t upperX, int32_t upperY, int32_t dialogueIndex, int32_t flagIndex) : GameWindowBase() {
  this->lowerX = lowerX;
  this->lowerY = lowerY;
  this->rectangleWidth = (upperX - lowerX) + 1;
  this->rectangleHeight = (upperY - lowerY) + 1;
  this->gameflagIndex = flagIndex;
  this->dialogueIndex = dialogueIndex;
  this->isTriggered = 0;
}
