#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/Tilemap.hpp"
#include "HazardStructs/TileColorMaps.hpp"
#include "HazardStructs/TmpObjectHuge.hpp"

void Tilemap::ScrollUpDown(int32_t param_1, int32_t param_2) {
  uint32_t baseTileOffset;
  uint32_t tileIndex;
  int32_t rowBufferOffset;
  int32_t columnOffset;

  uint32_t wrapCount;
  int16_t* sourceTileRow;
  int16_t* destTileRow;
  int32_t copyLoopCounter;
  int16_t* tileDestBuffer;

  int32_t visibleWidthTiles;

  visibleWidthTiles = this->visibleWidthTiles;
  baseTileOffset = ((param_2 * 512) + param_1) * 16;
  if (0 < visibleWidthTiles) {
    columnOffset = param_1 * 2;
    do {
      tileIndex = baseTileOffset & 0x3ffff;
      destTileRow = (int16_t*)(this->uniqueTilesArray + *(int16_t*)((intptr_t)this->tileMatrix[param_2] + columnOffset));
      if (tileIndex < 0x3e000) {
        rowBufferOffset = tileIndex * 2;
        copyLoopCounter = 0x10;
        do {

          memcpy((byte*)this->tileCacheData->start + rowBufferOffset, destTileRow, 32);
          rowBufferOffset = rowBufferOffset + 0x400;
          copyLoopCounter = copyLoopCounter + -1;
          destTileRow = destTileRow + 0x10;
        } while (copyLoopCounter != 0);
      }
      else {
        wrapCount = 0;
        if (tileIndex < 0x40000) {
          wrapCount = (0x401ff - tileIndex) >> 9;
          sourceTileRow = destTileRow;
          do {
            destTileRow = sourceTileRow + 0x10;
            tileDestBuffer = this->tileCacheData->start + tileIndex;
            tileIndex = tileIndex + 0x200;

            memcpy(tileDestBuffer, sourceTileRow, 32);
            sourceTileRow = destTileRow;
          } while ((int32_t)tileIndex < 0x40000);
        }
        tileIndex = tileIndex - 0x40000;
        if (wrapCount < 0x10) {
          rowBufferOffset = 0x10 - wrapCount;
          do {
            sourceTileRow = this->tileCacheData->start + tileIndex;
            tileIndex = tileIndex + 0x200;
            rowBufferOffset = rowBufferOffset + -1;

            memcpy(sourceTileRow, destTileRow, 32);
            destTileRow = destTileRow + 0x10;
          } while (rowBufferOffset != 0);
        }

        memcpy(this->tileCacheData->last_1024b + (tileIndex & 0x1ff), this->tileCacheData->start + (tileIndex & 0x1ff), 32);
      }
      baseTileOffset = baseTileOffset + 0x10;
      visibleWidthTiles = visibleWidthTiles + -1;
      columnOffset = columnOffset + 2;
    } while (visibleWidthTiles != 0);
  }
}
