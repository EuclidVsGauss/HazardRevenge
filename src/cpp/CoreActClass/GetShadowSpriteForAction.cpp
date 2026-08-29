#include "HazardClasses/CoreActClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

ImageVectorWithHeader* CoreActClass::GetShadowSpriteForAction(int32_t actionIndex, uint16_t frameIndex, unsigned char spriteVariant) {
  int32_t totalFrames;
  int32_t baseFrame;
  int32_t shadowSpriteOffset;

  if (actionIndex < 0) {
    return nullptr;
  }

  totalFrames = this->txtContent[actionIndex].numberFrames;
  if (0 < totalFrames) {
    baseFrame = this->txtContent[actionIndex].ptrFrameStart[(frameIndex & 0xffff) % totalFrames];
    shadowSpriteOffset = (spriteVariant & 7) * this->numberSprFrames;
    return this->shadowSpriteMap[baseFrame + shadowSpriteOffset];
  }

  return nullptr;
}
