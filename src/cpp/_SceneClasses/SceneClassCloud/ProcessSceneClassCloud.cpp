#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneClassCloud.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void SceneClassCloud::Case_0x7d11(intptr_t param2) {
  this->mainSceneHandler = (SceneHandler*)param2;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)this, 0x1);
}

__forceinline void SceneClassCloud::Case_0x7d3c() {
  float floatDelta;
  int32_t currentFrame;

  this->toFloat_2 += this->addToFloat_2;
  this->toFloat_1 += this->addToFloat_1;

  currentFrame = this->currentFrame + 1;
  if (this->maxFrame <= currentFrame) {
    this->currentFrame = 0;
    floatDelta = (float)this->maxFrame;
    this->toFloat_1 = this->toFloat_1 - (floatDelta * this->addToFloat_1);
    this->toFloat_2 = this->toFloat_2 - (floatDelta * this->addToFloat_2);
  }
}

__forceinline void SceneClassCloud::Case_0x7d3b() {
  SceneClassCameraBase* camera;
  ImageVectorWithHeader* spriteFrame = nullptr;

  spriteFrame = __InlineGetSolidSpriteFrameForAction(this->actObject, this->fileObject, this->currentFrame);

  camera = this->mainSceneHandler->sceneCamera;
  int32_t xOffset = this->toFloat_1;
  int32_t yPos = xOffset;
  int32_t alpha = -960 - xOffset;
  int32_t xPos = this->toFloat_2;
  camera->DrawSprite(xPos, yPos, spriteFrame, alpha);
}

void SceneClassCloud::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t dummy) {

  (void)dummy;

  switch (switchParam) {
  case 0x7d11:
    Case_0x7d11(param2);
    return;

  case 0x7d3c:
    Case_0x7d3c();
    return;

  case 0x7d3b:
    Case_0x7d3b();
    return;
  }
}
