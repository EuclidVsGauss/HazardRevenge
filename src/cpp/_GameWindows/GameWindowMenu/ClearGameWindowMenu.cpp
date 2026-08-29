#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowMenu.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardStructs/WindowReference.hpp"

GameWindowMenu::~GameWindowMenu() {
  SceneHandler* mainSceneHandler;
  SceneHandler* mainSceneHandler2;
  CoreActClass* menuAct;

  mainSceneHandler = this->mainSceneHandler;

  mainSceneHandler->primarySwitchSingleParam_0x7d14(0, 0x6);
  mainSceneHandler2 = this->mainSceneHandler;
  mainSceneHandler2->primarySwitchSingleParam_SetWindow_0x7d16(8, nullptr);
  menuAct = this->menuAct;
  if (menuAct != nullptr) {
    delete menuAct;
  }
}
