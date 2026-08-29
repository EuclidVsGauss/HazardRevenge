#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/Tilemap.hpp"
#include "HazardStructs/TileColorMaps.hpp"
#include "HazardStructs/TmpObjectHuge.hpp"

void Tilemap::ScrollUpDown(int32_t param_1, int32_t param_2) {
  int32_t y = param_2;
  int32_t x = param_1;
  uint32_t baseTileOffset = ((y * 512) + x) * 16;
  int32_t columnOffset = x;
  for (int32_t rowCounter = this->visibleWidthTiles; rowCounter > 0; rowCounter--) {
    int16_t* sourceTileDataPtr = (int16_t*)(this->uniqueTilesArray + this->tileMatrix[param_2][columnOffset]);
    int32_t wrappedDataOffset = baseTileOffset & 0x3ffff;
    columnOffset += 1;

    if (wrappedDataOffset < 0x3e000) {
      for (int32_t loopCounter = 0x10; loopCounter != 0; loopCounter--) {
        memcpy(&this->tileCacheData->start[wrappedDataOffset], sourceTileDataPtr, 32);
        wrappedDataOffset += 0x200;
        sourceTileDataPtr += 0x10;
      }
    }
    else {
      int32_t firstBlockIndex = 0;
      if (wrappedDataOffset < 0x40000) {
        firstBlockIndex = (0x401ffU - wrappedDataOffset) >> 9;
        for (; wrappedDataOffset < 0x40000; wrappedDataOffset += 0x200) {
          memcpy(&this->tileCacheData->start[wrappedDataOffset], sourceTileDataPtr, 32);
          sourceTileDataPtr += 0x10;
        }
      }

      wrappedDataOffset -= 0x40000;
      if (firstBlockIndex < 0x10) {
        int32_t count = 0x10 - firstBlockIndex;
        do {
          memcpy(&this->tileCacheData->start[wrappedDataOffset], sourceTileDataPtr, 32);
          wrappedDataOffset += 0x200;
          sourceTileDataPtr += 0x10;
          count--;
        } while (count != 0);
      }

      int32_t finalOffset = wrappedDataOffset & 0x1ff;
      memcpy(&this->tileCacheData->last_1024b[finalOffset], &this->tileCacheData->start[finalOffset], 32);
    }

    baseTileOffset += 0x10;
  }
}
