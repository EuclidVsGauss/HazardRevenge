#include "HazardClasses/Tilemap.hpp"
#include "HazardStructs/TileColorMaps.hpp"
#include "HazardStructs/TmpObjectHuge.hpp"

void Tilemap::ScrollLeft(int32_t param_1, int32_t param_2) {
  int16_t** tileMatrixRowPtr;
  uint32_t tileDataOffset;
  uint32_t wrappedDataOffset;
  int32_t dataCopyOffset;
  intptr_t matrixRowOffset;

  uint32_t loopCounter;
  int16_t* sourceTileDataPtr;
  int16_t* destTileCachePtr;
  int32_t innerLoopCounter;
  int16_t* copySourcePtr;
  int16_t* copyDestPtr;
  int32_t rowCounter;

  tileDataOffset = ((param_2 * 512) + param_1) * 16;

  matrixRowOffset = param_2 * sizeof(int16_t*);
  for (rowCounter = this->visibleHeightTiles; rowCounter != 0; rowCounter = rowCounter + -1) {

    tileMatrixRowPtr = (int16_t**)((intptr_t)this->tileMatrix + matrixRowOffset);
    matrixRowOffset = matrixRowOffset + sizeof(int16_t*);
    wrappedDataOffset = tileDataOffset & 0x3ffff;
    int16_t tile_index = (*tileMatrixRowPtr)[param_1];
    if (tile_index < 0) {
      tile_index = 0;
    }
    sourceTileDataPtr = (int16_t*)&this->uniqueTilesArray[tile_index];
    if (wrappedDataOffset < 0x3e000) {
      dataCopyOffset = wrappedDataOffset;
      for (innerLoopCounter = 0x10; innerLoopCounter != 0; innerLoopCounter = innerLoopCounter + -1) {
        copyDestPtr = (this->tileCacheData->start + dataCopyOffset);
        dataCopyOffset = dataCopyOffset + 0x200;
        copySourcePtr = sourceTileDataPtr;

        memcpy(copyDestPtr, copySourcePtr, 4 * 8);
        sourceTileDataPtr = sourceTileDataPtr + 0x10;
      }
    }
    else {
      loopCounter = 0;
      if (wrappedDataOffset < 0x40000) {
        loopCounter = (0x401ff - wrappedDataOffset) >> 9;
        copySourcePtr = sourceTileDataPtr;
        do {
          sourceTileDataPtr = copySourcePtr + 0x10;
          destTileCachePtr = this->tileCacheData->start + wrappedDataOffset;
          wrappedDataOffset = wrappedDataOffset + 0x200;

          memcpy(destTileCachePtr, copySourcePtr, 4 * 8);
          copySourcePtr = sourceTileDataPtr;
        } while ((int32_t)wrappedDataOffset < 0x40000);
      }
      wrappedDataOffset = wrappedDataOffset - 0x40000;
      if (loopCounter < 0x10) {
        innerLoopCounter = 0x10 - loopCounter;
        do {
          copySourcePtr = this->tileCacheData->start + wrappedDataOffset;
          wrappedDataOffset = wrappedDataOffset + 0x200;
          innerLoopCounter = innerLoopCounter + -1;

          memcpy(copySourcePtr, sourceTileDataPtr, 4 * 8);
          sourceTileDataPtr = sourceTileDataPtr + 0x10;
        } while (innerLoopCounter != 0);
      }
      sourceTileDataPtr = this->tileCacheData->start + (wrappedDataOffset & 0x1ff);
      copySourcePtr = this->tileCacheData->last_1024b + (wrappedDataOffset & 0x1ff);

      memcpy(copySourcePtr, sourceTileDataPtr, 4 * 8);
    }
    tileDataOffset = tileDataOffset + 0x2000;
  }
}
