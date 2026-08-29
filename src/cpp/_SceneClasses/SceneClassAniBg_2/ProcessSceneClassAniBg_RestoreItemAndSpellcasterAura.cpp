#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassAniBg_RestoreItemAndSpellcasterAura.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void SceneClassAniBg_RestoreItemAndSpellcasterAura::InitializeObject_0x7d11(intptr_t param2) {
  this->mainSceneHandler = (SceneHandler*)param2;
  this->mainSceneHandler->primarySwitchSingleParam_AddObjectToScene_0x7d0f(this, 0x0);
}

__forceinline void SceneClassAniBg_RestoreItemAndSpellcasterAura::DrawObject_0x7d3b() {
  int32_t spriteOffset = this->actOffsetStand;
  int32_t drawX = (this->matrixIndexXTimes16 + 1) * 0x10;
  int32_t drawY = (this->matrixIndexYTimes16 + 1) * 0x10;
  CoreActClass* actObj = this->actObject;
  ImageVectorWithHeader* spriteImage;
  if (spriteOffset >= 0) {
    int32_t frameIndex = actObj->txtContent[spriteOffset].numberFrames;
    if (frameIndex > 0) {
      uint16_t frameCount = this->truncatedRng;
      spriteImage = actObj->solidSpriteMap[actObj->txtContent[spriteOffset].ptrFrameStart[frameCount % frameIndex]];
    }
    else {
      spriteImage = nullptr;
    }
  }
  else {
    spriteImage = nullptr;
  }
  this->mainSceneHandler->sceneCamera->DrawSprite(drawX, drawY, spriteImage, -drawY + -0x1e1);
}

__forceinline void SceneClassAniBg_RestoreItemAndSpellcasterAura::RunTick_0x7d3c() {
  this->truncatedRng++;
  if (this->truncatedRng < this->frame_or_actValueStand) {
    return;
  }
  SceneHandler* sceneHandler = this->mainSceneHandler;
  sceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
}

void SceneClassAniBg_RestoreItemAndSpellcasterAura::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param3) {
  (void)param3;

  switch (switchParam) {
  case 0x7d11:
    this->InitializeObject_0x7d11(param2);
    return;

  case 0x7d3b:
    this->DrawObject_0x7d3b();
    return;

  case 0x7d3c:
    this->RunTick_0x7d3c();
    return;

  default:
    return;
  }
}
