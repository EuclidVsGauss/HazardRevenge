#include "HazardClasses/CoreActClass.hpp"
#include "HazardExterns/CoreActClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/SpriteMapPair.hpp"

CoreActClass::~CoreActClass() {

  SpriteMapPair* actFileEntry;

  actFileEntry = LoadActHelperSpriteMapPair;
  while (actFileEntry != nullptr) {
    if (actFileEntry->imageVectors == this->solidSpriteMap) {
      break;
    }
    actFileEntry = actFileEntry->previous;
  }

  if (((this->solidSpriteMap != nullptr) && (actFileEntry != nullptr)) && (actFileEntry->scalar--, actFileEntry->scalar <= 0)) {
    for (int32_t i = 0; this->solidSpriteMap[i] != nullptr; i++) {
      delete this->solidSpriteMap[i];
      delete this->shadowSpriteMap[i];
    }
    delete[] this->solidSpriteMap;
    delete[] this->shadowSpriteMap;
    actFileEntry->imageVectors = nullptr;
    actFileEntry->sprImageArray = nullptr;
  }
}
