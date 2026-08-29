#ifndef HAZARD_TMPBACKGROUNDSPRITEINSTANCE_HPP
#define HAZARD_TMPBACKGROUNDSPRITEINSTANCE_HPP

#include "HazardTypedef.hpp"

struct ImageVectorWithHeader;

struct TmpBackgroundSpriteInstance {
  int32_t coordX;
  int32_t coordY;
  int32_t overlayIndex;
  ImageVectorWithHeader* backgroundSprites;
  ImageVectorWithHeader* backgroundShadowSprites;
  TmpBackgroundSpriteInstance* overlayedObject;
};
typedef struct TmpBackgroundSpriteInstance TmpBackgroundSpriteInstance, *PTmpBackgroundSpriteInstance;

#endif
