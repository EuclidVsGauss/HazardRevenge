#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void AnimationStatusSpell::InitializeObject_0x7d11(intptr_t param_2) {
  this->mainSceneHandler = (SceneHandler*)param_2;
  this->mainSceneHandler->primarySwitchSingleParam_AddObjectToScene_0x7d0f(this, 0x0);
  int32_t sfxIndex = __InlineGetSoundEffectIndex(this->coreActClass);
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, sfxIndex, (intptr_t)this);
}

__forceinline void AnimationStatusSpell::DrawObject_0x7d3b() {
  int32_t coordX = this->matrixIndexXTimes16;
  int32_t coordY = this->matrixIndexYTimes16;
  byte** visibilityGrid = this->mainSceneHandler->PaddedGridMap_Visibility;
  for (int32_t loopY = 0; loopY < 2; loopY++) {
    int32_t tempX = coordX;
    for (int32_t loopX = 0; loopX < 2; loopX++) {
      if (visibilityGrid[coordY >> 1][tempX >> 1] != 0) {
        int32_t finalCoordX = (this->matrixIndexXTimes16 + 1) << 4;
        int32_t finalCoordY = (this->matrixIndexYTimes16 + 1) << 4;
        ImageVectorWithHeader* pSprite = this->coreActClass->__InlineGetSolidSpriteFrameForAction(this->actionIndex, this->currentFrameIndex);
        this->mainSceneHandler->sceneCamera->DrawSprite(finalCoordX, finalCoordY, pSprite, -finalCoordY - 481);
        return;
      }
      tempX++;
    }
    coordY++;
  }
}

__forceinline void AnimationStatusSpell::RunTick_0x7d3c() {
  int32_t nextFrameIndex = this->currentFrameIndex + 1;
  if (nextFrameIndex >= this->actionFrameCount) {
    int32_t repeatCounter = this->repeatCounter;
    this->repeatCounter--;
    if (repeatCounter > 0) {
      return;
    }
    this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
    return;
  }
  this->currentFrameIndex = nextFrameIndex;
}

void AnimationStatusSpell::primarySwitchSingleParam(int32_t param_1, intptr_t param_2, intptr_t param_3) {
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

  default:
    break;
  }
}
