#include "HazardClasses/Tilemap.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/TmpObjectHuge.hpp"

Tilemap::~Tilemap() {

  int32_t tileIndex;

  delete this->tileCacheData;
  for (tileIndex = 0; this->tileMatrix[tileIndex] != nullptr; tileIndex = tileIndex + 1) {
    delete this->tileMatrix[tileIndex];
  }
  delete this->tileMatrix;
}
