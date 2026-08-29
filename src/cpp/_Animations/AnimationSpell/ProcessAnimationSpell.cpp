#include "HazardClasses/AnimationSpell.hpp"
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void AnimationSpell::InitializeObject_0x7d11(intptr_t param_2) {
  CoreActClass* actWithSfx;
  int32_t soundIndex;

  this->mainSceneHandler = (SceneHandler*)param_2;
  this->mainSceneHandler->primarySwitchSingleParam_AddObjectToScene_0x7d0f(this, 0x0);
  actWithSfx = this->actWithSfx;
  soundIndex = actWithSfx->GetActionIndexByName(s__sfx);
  if (soundIndex == -1) {
    soundIndex = 0;
  }
  else {
    soundIndex = *actWithSfx->txtContent[soundIndex].ptrFrameStart;
  }
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, soundIndex, (intptr_t)this);
}

__forceinline void AnimationSpell::DrawObject_0x7d3b() {
  int32_t screenX;
  int32_t screenY;
  ImageVectorWithHeader* spriteFrame;

  screenX = (this->matrixIndexXTimes16 + 1) << 4;
  screenY = (this->matrixIndexYTimes16 + 1) << 4;

  spriteFrame = this->actWithSfx->__InlineGetSolidSpriteFrameForAction(this->stand, this->presumablyCurrentAnimationIndex);

  this->mainSceneHandler->sceneCamera->DrawSprite(screenX, screenY, spriteFrame, -screenY - 481);
}

__forceinline void AnimationSpell::RunTick_0x7d3c() {
  this->presumablyCurrentAnimationIndex++;
  if (this->presumablyCurrentAnimationIndex < this->numberOfFramesForStandAnimation) {
    return;
  }
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
}

void AnimationSpell::primarySwitchSingleParam(int32_t param_1, intptr_t param_2, intptr_t param_3) {
  (void)param_3;

  switch (param_1) {
  case 0x7d11:
    this->InitializeObject_0x7d11(param_2);
    break;

  case 0x7d3b:
    this->DrawObject_0x7d3b();
    break;

  case 0x7d3c:
    this->RunTick_0x7d3c();
    break;
  }
}
