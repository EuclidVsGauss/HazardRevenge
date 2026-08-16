#include "HazardClasses/AnimationSpell.hpp"
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void Case_0x7d11(AnimationSpell* spell, intptr_t param_2) {
  CoreActClass* actWithSfx;
  int32_t soundIndex;

  spell->mainSceneHandler = (SceneHandler*)param_2;
  spell->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)spell, 0x0);
  actWithSfx = spell->actWithSfx;
  soundIndex = actWithSfx->GetActionIndexByName(s__sfx);
  if (soundIndex == -1) {
    soundIndex = 0;
  }
  else {
    soundIndex = *actWithSfx->txtContent[soundIndex].ptrFrameStart;
  }
  spell->mainSceneHandler->primarySwitchSingleParam(0x7d0a, soundIndex, (intptr_t)spell);
}

__forceinline void Case_0x7d3b(AnimationSpell* spell) {
  int32_t screenX;
  int32_t screenY;
  ImageVectorWithHeader* spriteFrame;

  screenX = (spell->matrixIndexXTimes16 + 1) << 4;
  screenY = (spell->matrixIndexYTimes16 + 1) << 4;

  spriteFrame = AnimationSpell::__InlineGetSolidSpriteFrameForAction(spell->stand, spell->actWithSfx, spell->presumablyCurrentAnimationIndex);

  spell->mainSceneHandler->sceneCamera->DrawSprite(screenX, screenY, spriteFrame, -screenY - 481);
}

__forceinline void Case_0x7d3c(AnimationSpell* spell) {
  spell->presumablyCurrentAnimationIndex++;
  if (spell->presumablyCurrentAnimationIndex < spell->numberOfFramesForStandAnimation) {
    return;
  }
  spell->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)spell, 0x0);
}

void AnimationSpell::primarySwitchSingleParam(int32_t param_1, intptr_t param_2, intptr_t param_3) {
  (void)param_3;

  switch (param_1) {
  case 0x7d11:
    Case_0x7d11(this, param_2);
    break;

  case 0x7d3b:
    Case_0x7d3b(this);
    break;

  case 0x7d3c:
    Case_0x7d3c(this);
    break;
  }
}
