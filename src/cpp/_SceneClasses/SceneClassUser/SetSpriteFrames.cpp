#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/SceneClassUser.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void SceneClassUser::SetSpriteFrames(int32_t param_1, uint32_t param_2) {
  int32_t animationIndex;
  CoreActClass* actObject;
  int32_t frameCount;
  ImageVectorWithHeader* solidSpriteFrame;
  ImageVectorWithHeader* shadowSpriteFrame;

  animationIndex = (&this->actStand)[param_1];
  actObject = this->genericAct;
  if (animationIndex >= 0) {
    frameCount = actObject->txtContent[animationIndex].numberFrames;
    if (frameCount > 0) {
      uint16_t frameIndex = param_2;
      int32_t frameOffset = actObject->txtContent[animationIndex].ptrFrameStart[frameIndex % frameCount];
      byte orientation = ((this->orientation - 1) & 7);
      int32_t directionalOffset = (orientation * actObject->numberSprFrames);
      solidSpriteFrame = actObject->solidSpriteMap[directionalOffset + frameOffset];
    }
    else {
      solidSpriteFrame = nullptr;
    }
  }
  else {
    solidSpriteFrame = nullptr;
  }
  this->currentSolidSpriteFrame = solidSpriteFrame;

  animationIndex = (&this->actStand)[param_1];
  if (animationIndex >= 0) {
    frameCount = actObject->txtContent[animationIndex].numberFrames;
    if (0 < frameCount) {
      uint16_t frameIndex = param_2;
      int32_t frameOffset = actObject->txtContent[animationIndex].ptrFrameStart[(frameIndex % frameCount)];
      byte orientation = ((this->orientation - 1) & 7);
      int32_t directionalOffset = (orientation * actObject->numberSprFrames);
      shadowSpriteFrame = actObject->shadowSpriteMap[directionalOffset + frameOffset];
    }
    else {
      shadowSpriteFrame = nullptr;
    }
  }
  else {
    shadowSpriteFrame = nullptr;
  }
  this->currentShadowSpriteFrame = shadowSpriteFrame;
}
