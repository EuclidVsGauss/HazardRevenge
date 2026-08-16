#include "HazardClasses/SceneClassMap.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/TileColorMaps.hpp"
#include "HazardStructs/TmpBackgroundSpriteInstance.hpp"

SceneClassMap::~SceneClassMap() {
  int32_t spriteIndex;

  delete this->instancesOfBackgroundSprites;
  delete[] this->uniqueTileColorMaps;

  for (spriteIndex = 0; locationOfBackgroundSprites[spriteIndex] != nullptr; spriteIndex++) {
    delete locationOfBackgroundSprites[spriteIndex];
  }
  delete this->locationOfBackgroundSprites;

  for (spriteIndex = 0; this->loadedBackgroundSprites[spriteIndex] != nullptr; spriteIndex++) {
    delete this->loadedBackgroundSprites[spriteIndex];
    if (this->loadedBackgroundShadowSprites[spriteIndex] != nullptr) {
      delete this->loadedBackgroundShadowSprites[spriteIndex];
    }
  }
  delete this->loadedBackgroundSprites;
  delete this->loadedBackgroundShadowSprites;
}
