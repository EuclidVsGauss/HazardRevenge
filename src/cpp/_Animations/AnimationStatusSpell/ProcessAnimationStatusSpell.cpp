#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void AnimationStatusSpell::Case_0x7d11(intptr_t param_2) {
  CoreActClass* this_00;
  int32_t actionIndex;

  this->mainSceneHandler = (SceneHandler*)param_2;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)this, 0x0);
  this_00 = this->coreActClass;
  actionIndex = this_00->GetActionIndexByName(s__sfx);
  if (actionIndex == -1) {
    actionIndex = 0;
  }
  else {
    actionIndex = *this_00->txtContent[actionIndex].ptrFrameStart;
  }
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, actionIndex, (intptr_t)this);
}

__forceinline void AnimationStatusSpell::Case_0x7d3b() {
  ImageVectorWithHeader* pSprite;

  int32_t coordY;
  int32_t coordX;

  coordX = this->matrixIndexXTimes16;
  coordY = this->matrixIndexYTimes16;
  for (int32_t loopY = 0; loopY < 2; loopY++) {
    int32_t tempX = coordX;
    for (int32_t loopX = 0; loopX < 2; loopX++) {
      if (this->mainSceneHandler->PaddedGridMap_Visibility[coordY >> 1][tempX >> 1] != 0) {
        int32_t finalCoordX = (this->matrixIndexXTimes16 + 1) << 4;
        int32_t finalCoordY = (this->matrixIndexYTimes16 + 1) << 4;

        pSprite = __InlineGetSolidSpriteFrameForAction(this->actionIndex, this->coreActClass, this->currentFrameIndex);

        this->mainSceneHandler->sceneCamera->DrawSprite(finalCoordX, finalCoordY, pSprite, -finalCoordY - 481);
        return;
      }
      tempX++;
    }
    coordY++;
  }
}

__forceinline void AnimationStatusSpell::Case_0x7d3c() {
  int32_t repeatCounter;

  int32_t nextFrameIndex = this->currentFrameIndex + 1;
  int32_t frameCount = this->actionFrameCount;
  if (nextFrameIndex >= frameCount) {
    repeatCounter = this->repeatCounter;

    this->repeatCounter = repeatCounter - 1;
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
    this->Case_0x7d11(param_2);
    break;

  case 0x7d3b:
    this->Case_0x7d3b();
    return;

  case 0x7d3c:
    this->Case_0x7d3c();
    return;

    break;
  }
}
