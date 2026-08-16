#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/Tilemap.hpp"
#include "HazardGlobals.hpp"

void Tilemap::InitialiseTilemap(int32_t mapWidthTiles, int32_t mapHeightTiles) {
  int16_t* tileRow;
  int32_t rowIndex;
  byte* memsetPtr;
  uint32_t rowSizeBytes;

  this->tileMatrix = (int16_t**)new byte[((mapHeightTiles * sizeof(int16_t*)) + sizeof(int16_t*))];
  rowIndex = 0;
  while (rowIndex < mapHeightTiles) {
    rowSizeBytes = mapWidthTiles * 2;
    tileRow = new int16_t[mapWidthTiles];
    this->tileMatrix[rowIndex] = tileRow;
    memsetPtr = (byte*)this->tileMatrix[rowIndex];
    memset(memsetPtr, 0, rowSizeBytes);
    rowIndex = rowIndex + 1;
  };
  this->tileMatrix[rowIndex] = nullptr;
}
