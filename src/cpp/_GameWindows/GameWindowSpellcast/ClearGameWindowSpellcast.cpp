#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSpellcast.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardStructs/WindowReference.hpp"

GameWindowSpellcast::~GameWindowSpellcast() {
  SceneHandler* sceneHandler;
  sceneHandler = this->mainSceneHandler;
  sceneHandler->primarySwitchSingleParam_SetWindow_0x7d16(6, nullptr);
}
