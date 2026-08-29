#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneClassSwitch.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardExterns/SceneClassSwitch.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void SceneClassSwitch::InitializeObject_0x7d11(intptr_t param2) {
  uint32_t frameCountWithPadding;
  this->mainSceneHandler = (SceneHandler*)param2;
  this->mainSceneHandler->primarySwitchSingleParam_AddObjectToScene_0x7d0f(this, 0x0);
  frameCountWithPadding = this->TrackObjects(0x30);
  this->mainSceneHandler->SetCollisionValueInRectangularRegion(this->matrixIndexXTimes16, this->matrixIndexYTimes16, 2, 2, frameCountWithPadding);
}

__forceinline void SceneClassSwitch::DrawObject_0x7d3b() {
  ImageVectorWithHeader* spritePtr;
  ImageVectorWithHeader* shadowSpritePtr;
  int32_t coordX;
  int32_t coordY;

  coordX = (this->matrixIndexXTimes16 + 1) * 0x10;
  coordY = (this->matrixIndexYTimes16 + 1) * 0x10;

  spritePtr = this->actObject->__InlineGetSolidSpriteFrameForAction(this->actionIndex, this->currentFrame);
  this->mainSceneHandler->sceneCamera->DrawSprite(coordX, coordY, spritePtr, coordY + 0x1e0);
  shadowSpritePtr = this->actObject->__InlineGetShadowSpriteFrameForAction(this->actionIndex, this->currentFrame);
  this->mainSceneHandler->sceneCamera->DrawSprite(coordX, coordY, shadowSpritePtr, -coordY + -0x1e0);
}

__forceinline void SceneClassSwitch::RunTick_0x7d3c() {
  int32_t actionIndexCopy;
  int32_t frameCount;

  switch (this->currentState) {
  case 0:
    this->currentFrame = this->currentFrame + 1;
    break;
  case 2:
    if ((this->isPermanent != 0) && (this->currentFrame >= this->isPermanent)) {
      this->currentState = 3;
      actionIndexCopy = this->actObject->GetFrameCountForAction(this->actionIndex);
      this->currentFrame = actionIndexCopy + -1;
      if (this->gameFlagIndex != 0) {
        GameFlags[this->gameFlagIndex] = 0;
      }
    }
    this->currentFrame = this->currentFrame + 1;
    break;
  case 1:
    actionIndexCopy = this->currentFrame;
    frameCount = this->actObject->GetFrameCountForAction(this->actionIndex);
    this->currentFrame = actionIndexCopy + 1;
    if (actionIndexCopy >= frameCount + -1) {
      actionIndexCopy = this->actObject->GetActionIndexByName(Switch1_s_fopened[this->directionIndex]);
      this->actionIndex = actionIndexCopy;
      this->currentState = 2;
      this->currentFrame = 0;
    }
    break;
  case 3:
    this->currentFrame--;
    if (this->currentFrame <= 0) {
      int32_t tmp = this->actObject->GetActionIndexByName(Switch1_s_fstand[this->directionIndex]);
      this->currentState = 0;
      this->currentFrame = 0;
      this->actionIndex = tmp;
    }
    break;
  }
}

__forceinline void SceneClassSwitch::TriggerInteraction_0x7d04() {
  int32_t actionIndexCopy;
  int32_t soundIndex;
  CoreActClass* actObjectCopy;

  actionIndexCopy = this->actObject->GetActionIndexByName(Switch_s_fopen[this->directionIndex]);
  this->actionIndex = actionIndexCopy;
  if (this->currentState == 0) {
    this->currentState = 1;
    this->currentFrame = 0;
    if (this->gameFlagIndex != 0) {
      GameFlags[this->gameFlagIndex] = 1;
    }
  }
  else if (this->isPermanent == 0) {
    this->currentState = 3;
    actionIndexCopy = this->actObject->GetFrameCountForAction(actionIndexCopy);
    this->currentFrame = actionIndexCopy + -1;
    if (this->gameFlagIndex != 0) {
      GameFlags[this->gameFlagIndex] = 0;
    }
  }
  actObjectCopy = this->actObject;
  soundIndex = actObjectCopy->GetActionIndexByName(s__sfx);
  if (soundIndex == -1) {
    soundIndex = 0;
  }
  else {
    soundIndex = *actObjectCopy->txtContent[soundIndex].ptrFrameStart;
  }
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, soundIndex, (intptr_t)this);
}

void SceneClassSwitch::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param3) {
  (void)param3;

  switch (switchParam) {
  case 0x7d11:
    this->InitializeObject_0x7d11(param2);
    break;
  case 0x7d3b:
    this->DrawObject_0x7d3b();
    break;
  case 0x7d3c:
    this->RunTick_0x7d3c();
    break;
  case 0x7d04:
    this->TriggerInteraction_0x7d04();
    break;
  }
}
