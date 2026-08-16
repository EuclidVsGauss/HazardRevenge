#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/AnimationSummon.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void AnimationSummon::Case_0x7d11(intptr_t param_2) {
  CoreActClass* this_00;
  int32_t actionIndex;

  this->mainSceneHandler = (SceneHandler*)param_2;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)this, 0x1);
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

__forceinline void AnimationSummon::Case_0x7d3b() {
  ImageVectorWithHeader* solidSpriteFrame;

  solidSpriteFrame = __InlineGetSolidSpriteFrameForAction(this->firstStandActIndex, this->coreActClass, this->currentStandIndex);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, solidSpriteFrame, DrawLayer::Layer0xFFFF0003);
}

__forceinline void AnimationSummon::Case_0x7d3c() {
  this->currentStandIndex = this->currentStandIndex + 2;
  if (this->currentStandIndex + 1 < this->maxStandActIndex) {
    return;
  }
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
}

void AnimationSummon::primarySwitchSingleParam(int32_t param_1, intptr_t param_2, intptr_t param_3) {
  (void)param_3;

  switch (param_1) {
  case 0x7d11:
    this->Case_0x7d11(param_2);
    break;

  case 0x7d3b:
    this->Case_0x7d3b();
    break;

  case 0x7d3c:
    this->Case_0x7d3c();
    break;
  }
}
