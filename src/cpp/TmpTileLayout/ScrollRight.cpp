#include "HazardClasses/Tilemap.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/TmpObjectHuge.hpp"

void Tilemap::ScrollRight(int32_t param_1, uint8_t* param_2) {

  uint32_t blockOffset;
  uint32_t firstBlockIndex;

  int32_t loopCounter;

  if (param_1 < 0x3e000) {
    int32_t byteOffset = param_1 * 2;
    uint8_t* src = param_2;

    for (loopCounter = 0x10; loopCounter != 0; loopCounter--) {
      uint8_t* dest = (uint8_t*)(this->tileCacheData->start) + byteOffset;
      memcpy(dest, src, 32);
      byteOffset += 0x400;
      src += 0x20;
    }
    return;
  }

  firstBlockIndex = 0;
  if (param_1 < 0x40000) {
    firstBlockIndex = (0x401ffU - param_1) >> 9;
    uint8_t* src = param_2;
    int32_t offset = param_1;

    do {
      uint8_t* dest = (uint8_t*)(this->tileCacheData->start) + (offset * 2);
      memcpy(dest, src, 32);
      offset += 0x200;
      src += 0x20;
    } while (offset < 0x40000);

    param_1 = offset;
  }

  blockOffset = param_1 - 0x40000;

  if (firstBlockIndex < 0x10) {
    int32_t remaining = 0x10 - firstBlockIndex;
    uint8_t* src = param_2;
    int32_t offset = blockOffset;

    do {
      uint8_t* dest = (uint8_t*)(this->tileCacheData->start) + (offset * 2);
      memcpy(dest, src, 32);
      offset += 0x200;
      src += 0x20;
      remaining--;
    } while (remaining != 0);

    blockOffset = offset;
  }

  int32_t finalOffset = (blockOffset & 0x1ff) * 2;
  uint8_t* src = (uint8_t*)(this->tileCacheData->start) + finalOffset;
  uint8_t* dst = (uint8_t*)(this->tileCacheData->last_1024b) + finalOffset;
  memcpy(dst, src, 32);
}
