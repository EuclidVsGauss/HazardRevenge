#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassBoss.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void Case_0x7d11(SceneClassBoss* thisPtr, intptr_t param2) {
  thisPtr->mainSceneHandler = (SceneHandler*)param2;
  thisPtr->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)thisPtr, 0x1);
}

__forceinline void Case_0x7d3b(SceneClassBoss* thisPtr) {
  thisPtr->mainSceneHandler->sceneCamera->DrawSprite(thisPtr->coordX, thisPtr->coordY, thisPtr->bossSprite, (int16_t)thisPtr->coordY + 0x3c0);
}

__forceinline void Case_0x7d3c(SceneClassBoss* thisPtr) {
  uint16_t frameIndexMod16;
  int32_t frameCount;
  ActContent* actContent;
  int32_t switchState;
  CoreActClass* coreAct;
  int32_t* actionArrPtr;

  switchState = thisPtr->switchTrigger;
  switch (switchState) {
  case 0: {
    if (GameFlags[thisPtr->gameFlagindex1] == 1) {
      GameFlags[thisPtr->gameFlagindex1] = 0;
      thisPtr->spriteFrame = 0;
      thisPtr->switchTrigger = 1;
      thisPtr->mainSceneHandler->primarySwitchSingleParam(0x7d0a, 0x50, 0x0);
    }
    if (GameFlags[thisPtr->gameFlagindex2] != thisPtr->actionType) {
      thisPtr->actionType = GameFlags[thisPtr->gameFlagindex2];
      thisPtr->spriteFrame = 0;
      thisPtr->switchTrigger = 2;
      thisPtr->mainSceneHandler->primarySwitchSingleParam(0x7d0a, 0x51, 0x0);
    }
    frameIndexMod16 = *(uint16_t*)&thisPtr->spriteFrame;
    switchState = (&thisPtr->stand1)[thisPtr->actionType];
    thisPtr->spriteFrame = thisPtr->spriteFrame + 1;
    if (-1 < switchState) {
      actContent = thisPtr->combatRelatedAct->txtContent;
      frameCount = actContent[switchState].numberFrames;
      if (0 < frameCount) {
        thisPtr->bossSprite = thisPtr->combatRelatedAct->solidSpriteMap[actContent[switchState].ptrFrameStart[(frameIndexMod16 % frameCount)]];
        return;
      }
    }
    thisPtr->bossSprite = nullptr;
    return;
  }
  case 1: {
    coreAct = thisPtr->combatRelatedAct;
    actionArrPtr = &thisPtr->attack1 + thisPtr->actionType;
    thisPtr->bossSprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction((&thisPtr->attack1)[thisPtr->actionType], thisPtr->combatRelatedAct, thisPtr->spriteFrame);
    thisPtr->spriteFrame = thisPtr->spriteFrame + 1;
    switchState = coreAct->GetFrameCountForAction(*actionArrPtr);
    if (thisPtr->spriteFrame < switchState) {
      return;
    }
    thisPtr->switchTrigger = 0;
    thisPtr->spriteFrame = 0;
    return;
  }

  case 2:
    frameIndexMod16 = *(uint16_t*)&thisPtr->spriteFrame;
    actionArrPtr = &thisPtr->unused2 + thisPtr->actionType;
    coreAct = thisPtr->combatRelatedAct;
    thisPtr->spriteFrame = thisPtr->spriteFrame + 1;

    thisPtr->bossSprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction((&thisPtr->unused2)[thisPtr->actionType], thisPtr->combatRelatedAct, frameIndexMod16);
    thisPtr->spriteFrame = thisPtr->spriteFrame + 1;
    switchState = coreAct->GetFrameCountForAction(*actionArrPtr);
    if (thisPtr->spriteFrame < switchState) {
      return;
    }
    thisPtr->switchTrigger = 0;
    thisPtr->spriteFrame = 0;
    return;

  default:
    return;
  }
}

void SceneClassBoss::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param3) {
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
    break;
  }
}
