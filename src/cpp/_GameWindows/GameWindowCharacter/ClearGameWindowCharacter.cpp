#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowCharacter.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardStructs/WindowReference.hpp"

GameWindowCharacter::~GameWindowCharacter() {
  SceneHandler* mainSceneHandler;
  SceneHandler* sceneHandlerForWindow;
  CoreActClass* winAct;

  mainSceneHandler = this->mainSceneHandler;
  mainSceneHandler->primarySwitchSingleParam_0x7d14(0, 0x1);
  sceneHandlerForWindow = this->mainSceneHandler;
  sceneHandlerForWindow->primarySwitchSingleParam_SetWindow_0x7d16(2, nullptr);
  winAct = this->win1Act;
  if (winAct != nullptr) {
    delete winAct;
  }
}
