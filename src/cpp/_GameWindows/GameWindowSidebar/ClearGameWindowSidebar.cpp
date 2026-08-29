#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSidebar.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardStructs/WindowReference.hpp"

GameWindowSidebar::~GameWindowSidebar() {
  SceneHandler* mainSceneHandler;
  CoreActClass* winActObject;

  mainSceneHandler = this->mainSceneHandler;
  mainSceneHandler->primarySwitchSingleParam_SetWindow_0x7d16(1, nullptr);
  winActObject = this->win0act;
  if (winActObject != nullptr) {
    delete winActObject;
  }
}
