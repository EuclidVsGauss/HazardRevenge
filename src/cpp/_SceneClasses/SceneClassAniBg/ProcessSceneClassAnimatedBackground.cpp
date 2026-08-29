#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassAnimatedBackground.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void SceneClassAnimatedBackground::InitializeObject_0x7d11(intptr_t param2) {
  this->mainSceneHandler = (SceneHandler*)param2;
  this->mainSceneHandler->primarySwitchSingleParam_AddObjectToScene_0x7d0f(this, 0x0);
}

__forceinline void SceneClassAnimatedBackground::RunTick_0x7d3c() {
  this->truncatedRng = this->truncatedRng + 1;
}

__forceinline void SceneClassAnimatedBackground::DrawObject_0x7d3b() {
  int32_t coord2;
  ImageVectorWithHeader* spriteImage;
  ImageVectorWithHeader* shadowSprite;

  spriteImage = this->actObject->__InlineGetSolidSpriteFrameForAction(this->actionIndex, this->truncatedRng);
  this->mainSceneHandler->sceneCamera->DrawSprite(this->matrixIndexXTimes16 << 4, this->matrixIndexYTimes16 << 4, spriteImage, this->coord2WithLayerOffset);

  shadowSprite = this->actObject->__InlineGetShadowSpriteFrameForAction(this->actionIndex, this->truncatedRng);
  coord2 = this->matrixIndexYTimes16 << 4;
  this->mainSceneHandler->sceneCamera->DrawSprite(this->matrixIndexXTimes16 << 4, coord2, shadowSprite, coord2);
}

void SceneClassAnimatedBackground::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param3) {
  (void)param3;

  switch (switchParam) {
  case 0x7d11: {
    this->InitializeObject_0x7d11(param2);
    return;
  }
  case 0x7d3c: {
    this->RunTick_0x7d3c();
    return;
  }
  case 0x7d3b: {
    this->DrawObject_0x7d3b();
    return;
  }
  default:
    return;
  }
}
