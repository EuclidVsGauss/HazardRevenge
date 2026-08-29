#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/Tilemap.hpp"
#include "HazardStructs/TileColorMaps.hpp"
#include "HazardStructs/TmpObjectHuge.hpp"

void Tilemap::BuildTileCache(uint32_t tileWidthPixels, int32_t tileLengthPixels) {
  TmpObjectHuge* hugeTmpObject;
  int32_t heightTiles;
  int32_t cacheOffset;
  int32_t tileCacheOffset;
  int32_t remainingTiles;
  int16_t* sourceTilePtr;
  int16_t* currentTilePtr;
  int32_t loopCounter;
  int16_t* destinationTilePtr;
  byte* cacheDestionationPtr;
  uint32_t currentRowOffset;
  int32_t remainingWidthTiles;

  hugeTmpObject = this->tileCacheData;
  if (hugeTmpObject == nullptr) {
    hugeTmpObject = new TmpObjectHuge;
  }
  this->tileCacheData = hugeTmpObject;
  this->tileCacheIndex = 0;
  this->currentRowIndex = 0;
  this->currentColumnIndex = 0;
  this->visibleWidthTiles = (((int32_t)tileWidthPixels + 15) / 16) + 1;
  this->visibleHeightTiles = ((tileLengthPixels + 15) / 16) + 1;

  currentRowOffset = 0;
  for (int32_t heightIndex = 0; heightIndex < this->visibleHeightTiles; heightIndex++) {
    tileWidthPixels = currentRowOffset;
    heightTiles = 0;
    for (remainingWidthTiles = this->visibleWidthTiles; 0 < remainingWidthTiles; remainingWidthTiles--) {
      cacheOffset = tileWidthPixels & 0x3ffff;

      currentTilePtr = (int16_t*)(this->uniqueTilesArray + this->tileMatrix[heightIndex][heightTiles]);
      if (cacheOffset < 0x3e000) {
        tileCacheOffset = cacheOffset * 2;
        loopCounter = 16;
        do {
          cacheDestionationPtr = (byte*)((intptr_t)this->tileCacheData->start + tileCacheOffset);
          tileCacheOffset = tileCacheOffset + 1024;
          loopCounter = loopCounter + -1;

          memcpy(cacheDestionationPtr, currentTilePtr, 32);
          currentTilePtr = currentTilePtr + 0x10;
        } while (loopCounter != 0);
      }
      else {
        remainingTiles = 0;
        if (cacheOffset < 0x40000) {
          remainingTiles = (int32_t)((uint32_t)(0x401ff - cacheOffset) >> 9);
          sourceTilePtr = currentTilePtr;
          do {
            currentTilePtr = sourceTilePtr + 0x10;
            destinationTilePtr = this->tileCacheData->start + cacheOffset;
            cacheOffset = cacheOffset + 0x200;

            memcpy(destinationTilePtr, sourceTilePtr, 32);
            sourceTilePtr = currentTilePtr;
          } while (cacheOffset < 0x40000);
        }
        cacheOffset = cacheOffset - 0x40000;
        if (remainingTiles < 0x10) {
          tileCacheOffset = 0x10 - remainingTiles;
          do {
            sourceTilePtr = this->tileCacheData->start + cacheOffset;
            cacheOffset = cacheOffset + 0x200;
            tileCacheOffset = tileCacheOffset + -1;
            destinationTilePtr = currentTilePtr;

            memcpy(sourceTilePtr, destinationTilePtr, 32);
            currentTilePtr = currentTilePtr + 0x10;
          } while (tileCacheOffset != 0);
        }
        currentTilePtr = this->tileCacheData->start + (cacheOffset & 0x1ff);
        sourceTilePtr = this->tileCacheData->last_1024b + (cacheOffset & 0x1ff);

        memcpy(sourceTilePtr, currentTilePtr, 32);
      }
      tileWidthPixels = tileWidthPixels + 16;

      heightTiles = heightTiles + 1;
    }

    currentRowOffset = currentRowOffset + 0x2000;
  }
}
