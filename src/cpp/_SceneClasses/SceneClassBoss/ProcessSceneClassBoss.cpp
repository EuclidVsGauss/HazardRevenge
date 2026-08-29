#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassBoss.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void SceneClassBoss::InitializeObject_0x7d11(intptr_t param2) {
  this->mainSceneHandler = (SceneHandler*)param2;
  this->mainSceneHandler->primarySwitchSingleParam_AddObjectToScene_0x7d0f(this, 0x1);
}

__forceinline void SceneClassBoss::DrawObject_0x7d3b() {
  this->mainSceneHandler->sceneCamera->DrawSprite(this->coordX, this->coordY, this->bossSprite, this->coordY + 0x3c0);
}

__forceinline void SceneClassBoss::RunTick_0x7d3c() {
  uint16_t frameIndexMod16;
  int32_t switchState;
  int32_t frameCount;
  CoreActClass* coreAct;
  int32_t* actionArrPtr;

  switchState = this->switchTrigger;
  switch (switchState) {
  case 0: {
    if (GameFlags[this->gameFlagindex1] == 1) {
      GameFlags[this->gameFlagindex1] = 0;
      this->spriteFrame = 0;
      this->switchTrigger = 1;
      this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, 0x50, 0x0);
    }
    if (GameFlags[this->gameFlagindex2] != this->actionType) {
      this->actionType = GameFlags[this->gameFlagindex2];
      this->spriteFrame = 0;
      this->switchTrigger = 2;
      this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, 0x51, 0x0);
    }
    frameIndexMod16 = this->spriteFrame;
    switchState = (&this->stand1)[this->actionType];
    this->spriteFrame = this->spriteFrame + 1;
    this->bossSprite = this->combatRelatedAct->__InlineGetSolidSpriteFrameForAction(switchState, frameIndexMod16);
    return;
  }

  case 1: {
    coreAct = this->combatRelatedAct;
    actionArrPtr = &this->attack1 + this->actionType;
    this->bossSprite = coreAct->__InlineGetSolidSpriteFrameForAction((&this->attack1)[this->actionType], this->spriteFrame);
    this->spriteFrame = this->spriteFrame + 1;
    break;
  }

  case 2:
    frameIndexMod16 = this->spriteFrame;
    actionArrPtr = &this->unknown2 + this->actionType;
    coreAct = this->combatRelatedAct;
    this->spriteFrame = this->spriteFrame + 1;
    this->bossSprite = coreAct->__InlineGetSolidSpriteFrameForAction((&this->unknown2)[this->actionType], frameIndexMod16);
    this->spriteFrame = this->spriteFrame + 1;
    break;

  default:
    return;
  }

  frameCount = coreAct->GetFrameCountForAction(*actionArrPtr);
  if (this->spriteFrame < frameCount) {
    return;
  }
  this->switchTrigger = 0;
  this->spriteFrame = 0;
}

void SceneClassBoss::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param3) {
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
    break;
  }
}
