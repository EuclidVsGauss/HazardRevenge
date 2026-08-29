#include "HazardClasses/Tilemap.hpp"
#include "HazardStructs/TileColorMaps.hpp"
#include "HazardStructs/TmpObjectHuge.hpp"

void Tilemap::ScrollLeft(int32_t param_1, int32_t param_2) {
  int32_t y = param_2;
  int32_t x = param_1;
  int32_t h = this->visibleHeightTiles;

  int32_t tileDataOffset = ((y * 512) + x) * 16;
  intptr_t matrixRowOffset = y;
  for (int32_t rowCounter = 0; rowCounter < h; rowCounter++) {
    int32_t wrappedDataOffset = tileDataOffset & 0x3ffff;
    int16_t tile_index = this->tileMatrix[matrixRowOffset][x];
    int16_t* sourceTileDataPtr = (int16_t*)&this->uniqueTilesArray[tile_index];
    matrixRowOffset++;

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

    tileDataOffset += 0x2000;
  }
}
