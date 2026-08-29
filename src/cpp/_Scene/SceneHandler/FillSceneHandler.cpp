#include "HazardClasses/EventHandler.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneClassCommand.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/MapType.hpp"
#include "HazardGlobals.hpp"

SceneHandler::SceneHandler() {
  int32_t i;
  int32_t index;
  int32_t row;
  int32_t col;

  this->gameWindowsArray = new GameWindowBase*[512];
  for (i = 0; i < 512; i = i + 1) {
    this->gameWindowsArray[i] = nullptr;
  }

  this->selectedUnits32 = new GameWindowBase*[32];
  for (i = 0; i < 32; i++) {
    this->selectedUnits32[i] = nullptr;
  }

  for (index = 0; index < 16384; index = index + 1) {
    row = index >> 7;
    col = index & 0x7f;
    this->matrix_128x128[row][col] = nullptr;
  }

  this->sceneMusicIndex = -1;
  this->isViewportEnabled = 1;
  this->isMagicEnabled = 1;
  this->gameWindowsCounter = 0;
  this->currentObject = nullptr;
  this->sceneClassCommand = nullptr;
  this->sceneCamera = nullptr;
  this->mainSceneHandler = nullptr;
  this->mapType = MapTypeEnum(0x0);
  this->__InlineableQueueEvent(0x7d03);
}
