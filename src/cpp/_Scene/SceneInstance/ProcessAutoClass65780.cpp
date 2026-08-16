#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/EventHandler.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/SceneInstance.hpp"
#include "HazardExterns/SceneInstance.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/WindowReference.hpp"

__forceinline void SceneInstance::Case_0x7d11(intptr_t param_1) {
  WindowReference windowReference;
  this->mainSceneHandler = (SceneHandler*)param_1;
  windowReference.windowAddress = (intptr_t)(GameWindowBase*)this;
  windowReference.coords[0] = 0;
  windowReference.coords[1] = 0;
  windowReference.coords[2] = 0;
  windowReference.coords[3] = 0;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d16, this->sceneInstanceIndex_10to14, (intptr_t)&windowReference);
  this->mainSceneHandler->primarySwitchSingleParam(0x7d28, (intptr_t)this, (intptr_t)this->sceneName);
}

__forceinline void SceneInstance::Case_0x7d3c() {
  this->ParseSceneTxt();
}

__forceinline void SceneInstance::Case_0x7d07(int32_t switchParam, intptr_t param_1, intptr_t param_2) {
  if (param_1 != 0x0) {
    this->latestUnitToMoveToNewScene = (GameWindowBase*)param_1;
    return;
  }
  this->__InlineQueueEvent(param_2);
  this->__InlineQueueEvent(0);
  this->__InlineQueueEvent(switchParam);
}

__forceinline void SceneInstance::Case_0x7d1a(int32_t switchParam, intptr_t param_1, intptr_t param_2) {
  if (param_1 == 0x0) {
    return;
  }
  this->Case_0x7d2b(switchParam, param_1, param_2);
}

__forceinline void SceneInstance::Case_0x7d2b(int32_t switchParam, intptr_t param_1, intptr_t param_2) {
  this->QueueEvent(param_2);
  this->QueueEvent(param_1);
  this->QueueEvent(switchParam);
}

void SceneInstance::primarySwitchSingleParam(int32_t switchParam, intptr_t param_1, intptr_t param_2) {
  WindowReference windowReference;

  switch (switchParam) {

  case 0x7d11: {
    this->mainSceneHandler = (SceneHandler*)param_1;
    windowReference.windowAddress = (intptr_t)(GameWindowBase*)this;
    windowReference.coords[0] = 0;
    windowReference.coords[1] = 0;
    windowReference.coords[2] = 0;
    windowReference.coords[3] = 0;
    this->mainSceneHandler->primarySwitchSingleParam(0x7d16, this->sceneInstanceIndex_10to14, (intptr_t)&windowReference);
    this->mainSceneHandler->primarySwitchSingleParam(0x7d28, (intptr_t)this, (intptr_t)this->sceneName);
    return;
  }

  case 0x7d3c:
    this->ParseSceneTxt();
    return;

  case 0x7d07:
    if (param_1 != 0x0) {
      this->latestUnitToMoveToNewScene = (GameWindowBase*)param_1;
      return;
    }
    this->__InlineQueueEvent(param_2);
    this->__InlineQueueEvent(0);
    this->__InlineQueueEvent(switchParam);
    return;

  case 0x7d1a:
    if (param_1 == 0x0) {
      return;
    }
  case 0x7d2b:
  case 0x7d27:
    this->__InlineQueueEvent(param_2);
    this->__InlineQueueEvent(param_1);
    this->__InlineQueueEvent(switchParam);
    return;

  default:
    WrapperMessageBoxA(s_Error, s_cLOADWLD);
  }
}
