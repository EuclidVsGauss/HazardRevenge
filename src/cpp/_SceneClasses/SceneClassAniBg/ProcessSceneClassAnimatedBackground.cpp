#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassAnimatedBackground.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void Case_0x7d11(SceneClassAnimatedBackground* self, intptr_t param2) {
  self->mainSceneHandler = (SceneHandler*)param2;
  self->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)self, 0x0);
}

__forceinline void Case_0x7d3c(SceneClassAnimatedBackground* self) {
  self->truncatedRng = self->truncatedRng + 1;
}

__forceinline void Case_0x7d3b(SceneClassAnimatedBackground* self) {
  int32_t coord2;
  ImageVectorWithHeader* spriteImage;
  ImageVectorWithHeader* shadowSprite;

  spriteImage = GameWindowBase::__InlineGetSolidSpriteFrameForAction(self->actionIndex, self->actObject, self->truncatedRng);
  self->mainSceneHandler->sceneCamera->DrawSprite(self->matrixIndexXTimes16 << 4, self->matrixIndexYTimes16 << 4, spriteImage, self->coord2WithLayerOffset);

  shadowSprite = GameWindowBase::__InlineGetShadowSpriteFrameForAction(self->actionIndex, self->actObject, self->truncatedRng);
  coord2 = self->matrixIndexYTimes16 << 4;
  self->mainSceneHandler->sceneCamera->DrawSprite(self->matrixIndexXTimes16 << 4, coord2, shadowSprite, coord2);
}

void SceneClassAnimatedBackground::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param3) {
  (void)param3;

  switch (switchParam) {
  case 0x7d11: {
    Case_0x7d11(this, param2);
    return;
  }
  case 0x7d3c: {
    Case_0x7d3c(this);
    return;
  }
  case 0x7d3b: {
    Case_0x7d3b(this);
    return;
  }
  default:
    return;
  }
}
