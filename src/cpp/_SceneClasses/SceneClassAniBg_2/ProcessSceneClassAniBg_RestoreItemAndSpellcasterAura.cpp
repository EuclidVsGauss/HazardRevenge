#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassAniBg_RestoreItemAndSpellcasterAura.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void Case_0x7d11(SceneClassAniBg_RestoreItemAndSpellcasterAura* self, intptr_t param2) {
  self->mainSceneHandler = (SceneHandler*)param2;
  self->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)self, 0x0);
}

__forceinline void Case_0x7d3b(SceneClassAniBg_RestoreItemAndSpellcasterAura* self) {
  int32_t spriteOffset = self->actOffsetStand;
  int32_t drawX = (self->matrixIndexXTimes16 + 1) * 0x10;
  int32_t drawY = (self->matrixIndexYTimes16 + 1) * 0x10;
  CoreActClass* actObj = self->actObject;
  ImageVectorWithHeader* spriteImage;
  if (spriteOffset >= 0) {
    int32_t frameIndex = actObj->txtContent[spriteOffset].numberFrames;
    if (frameIndex > 0) {
      uint16_t frameCount = self->truncatedRng;
      spriteImage = actObj->solidSpriteMap[actObj->txtContent[spriteOffset].ptrFrameStart[frameCount % frameIndex]];
    }
    else {
      spriteImage = nullptr;
    }
  }
  else {
    spriteImage = nullptr;
  }
  self->mainSceneHandler->sceneCamera->DrawSprite(drawX, drawY, spriteImage, -drawY + -0x1e1);
}

__forceinline void Case_0x7d3c(SceneClassAniBg_RestoreItemAndSpellcasterAura* self) {
  self->truncatedRng++;
  if (self->truncatedRng < self->frame_or_actValueStand) {
    return;
  }
  SceneHandler* sceneHandler = self->mainSceneHandler;
  sceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)self, 0x0);
}

void SceneClassAniBg_RestoreItemAndSpellcasterAura::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param3) {
  (void)param3;

  switch (switchParam) {
  case 0x7d11:
    Case_0x7d11(this, param2);
    return;

  case 0x7d3b:
    Case_0x7d3b(this);
    return;

  case 0x7d3c:
    Case_0x7d3c(this);
    return;

  default:
    return;
  }
}
