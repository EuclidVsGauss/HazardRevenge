#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassBox.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneClassItem.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardExterns/SceneClassBox.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/ObjectWrapper.hpp"

void SceneClassBox::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param3) {

  (void)param3;

  switch (switchParam) {
  case 0x7d11:
    Case_0x7d11(param2);
    break;

  case 0x7d3b:
    Case_0x7d3b();
    break;

  case 0x7d3c: {
    CoreActClass* pCoreAct;
    int32_t currentFrameCount;
    int32_t totalFrames;
    uint32_t randomFrame;
    SceneClassItem* pSceneItem;

    switch (this->openStatus) {
    case 0:
      break;
    case 1: {
      currentFrameCount = this->counter;
      totalFrames = this->fileObject->GetFrameCountForAction(this->actionIndex);
      this->counter = currentFrameCount + 1;
      if (currentFrameCount < totalFrames + -1) {
        return;
      }
      currentFrameCount = this->fileObject->GetActionIndexByName(Box_s_fopened[this->chestDirectionIndex]);
      this->actionIndex = currentFrameCount;
      this->counter = 0;
      this->openStatus = 2;
      if (this->gameFlag != 0) {
        GameFlags[this->gameFlag] = 1;
      }
      currentFrameCount = this->fileObject->GetActionIndexByName(s__item);
      if (0 <= currentFrameCount) {
        pCoreAct = this->fileObject;
        currentFrameCount = pCoreAct->GetActionIndexByName(s__item);
        currentFrameCount = pCoreAct->GetFrameCountForAction(currentFrameCount);
        if (0 < currentFrameCount) {
          pCoreAct = this->fileObject;
          currentFrameCount = pCoreAct->GetActionIndexByName(s__item);
          currentFrameCount = pCoreAct->GetFrameCountForAction(currentFrameCount);
          randomFrame = PseudoRng() % currentFrameCount;
          pCoreAct = this->fileObject;
          totalFrames = pCoreAct->GetActionIndexByName(s__item);
          if (totalFrames == -1) {
            currentFrameCount = 0;
          }
          else {
            currentFrameCount = pCoreAct->txtContent[totalFrames].ptrFrameStart[randomFrame];
          }
          pSceneItem = new SceneClassItem(this->matrixIndexXTimes16, this->matrixIndexYTimes16, currentFrameCount, 9600);
          this->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(pSceneItem, 0x0);
        }
      }
      pCoreAct = this->fileObject;
      currentFrameCount = pCoreAct->GetActionIndexByName(s__sfx);
      if (currentFrameCount == -1) {
        currentFrameCount = 0;
      }
      else {
        currentFrameCount = *pCoreAct->txtContent[currentFrameCount].ptrFrameStart;
      }

      this->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(currentFrameCount, this);
      return;
    }
    case 2:
      break;

    default:
      return;
    }
    this->counter = this->counter + 1;
  } break;

  case 0x7d04:
    Case_0x7d04(param2);
    break;
  }
}

__forceinline void SceneClassBox::Case_0x7d11(intptr_t param2) {
  uint32_t trackResult;

  this->mainSceneHandler = (SceneHandler*)param2;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)this, 0x0);
  if (this->openStatus != 2) {
    trackResult = this->TrackObjects(0x30);
    this->mainSceneHandler->SetCollisionValueInRectangularRegion(this->matrixIndexXTimes16, this->matrixIndexYTimes16, 2, 2, (int16_t)trackResult);
  }
  else {
    this->mainSceneHandler->SetCollisionValueInRectangularRegion(this->matrixIndexXTimes16, this->matrixIndexYTimes16, 2, 2, 0xffff);
  }
}

__forceinline void SceneClassBox::Case_0x7d3b() {
  int32_t spriteX;
  int32_t spriteY;
  ImageVectorWithHeader* pSolidSprite;
  ImageVectorWithHeader* pShadowSprite;

  spriteX = (this->matrixIndexXTimes16 + 1) * 0x10;
  spriteY = (this->matrixIndexYTimes16 + 1) * 0x10;

  pSolidSprite = __InlineGetSolidSpriteFrameForAction(this->actionIndex, this->fileObject, this->counter);
  this->mainSceneHandler->sceneCamera->DrawSprite(spriteX, spriteY, pSolidSprite, spriteY + 0x1e0);

  pShadowSprite = __InlineGetShadowSpriteFrameForAction(this->actionIndex, this->fileObject, this->counter);
  this->mainSceneHandler->sceneCamera->DrawSprite(spriteX, spriteY, pShadowSprite, spriteY);
}

__forceinline void SceneClassBox::Case_0x7d3c() {
  CoreActClass* pCoreAct;
  int32_t actionIndex;
  int32_t frameCount;
  uint32_t randomFrame;
  SceneClassItem* pSceneItem;

  randomFrame = this->openStatus;
  switch (randomFrame) {
  case 0:
    break;
  case 1: {
    frameCount = this->counter;
    actionIndex = this->fileObject->GetFrameCountForAction(this->actionIndex);
    this->counter = frameCount + 1;
    if (frameCount < actionIndex + -1) {
      return;
    }
    frameCount = this->fileObject->GetActionIndexByName(Box_s_fopened[this->chestDirectionIndex]);
    this->actionIndex = frameCount;
    this->counter = 0;
    this->openStatus = 2;
    if (this->gameFlag != 0) {
      GameFlags[this->gameFlag] = 1;
    }
    frameCount = this->fileObject->GetActionIndexByName(s__item);
    if (0 <= frameCount) {
      pCoreAct = this->fileObject;
      frameCount = pCoreAct->GetActionIndexByName(s__item);
      frameCount = pCoreAct->GetFrameCountForAction(frameCount);
      if (0 < frameCount) {
        pCoreAct = this->fileObject;
        frameCount = pCoreAct->GetActionIndexByName(s__item);
        frameCount = pCoreAct->GetFrameCountForAction(frameCount);
        randomFrame = PseudoRng() % frameCount;
        pCoreAct = this->fileObject;
        actionIndex = pCoreAct->GetActionIndexByName(s__item);
        if (actionIndex == -1) {
          frameCount = 0;
        }
        else {
          frameCount = pCoreAct->txtContent[actionIndex].ptrFrameStart[randomFrame];
        }
        pSceneItem = new SceneClassItem(this->matrixIndexXTimes16, this->matrixIndexYTimes16, frameCount, 9600);
        this->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(pSceneItem, 0x0);
      }
    }
    pCoreAct = this->fileObject;
    frameCount = pCoreAct->GetActionIndexByName(s__sfx);
    if (frameCount == -1) {
      frameCount = 0;
    }
    else {
      frameCount = *pCoreAct->txtContent[frameCount].ptrFrameStart;
    }

    this->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(frameCount, this);
    return;
  }
  case 2:
    break;

  default:
    return;
  }
  this->counter = this->counter + 1;
}

__forceinline void SceneClassBox::Case_0x7d04(intptr_t param2) {
  int32_t openActionIndex;

  if ((this->openStatus == 0) && (ObjectList[param2].sceneClassObjectPointer != nullptr)) {
    this->mainSceneHandler->SetCollisionValueInRectangularRegion(this->matrixIndexXTimes16, this->matrixIndexYTimes16, 2, 2, -1);
    openActionIndex = this->fileObject->GetActionIndexByName(Box_s_fopen[this->chestDirectionIndex]);
    this->actionIndex = openActionIndex;
    this->counter = 0;
    this->openStatus = 1;
  }
}
