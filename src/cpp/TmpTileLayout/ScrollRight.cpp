#include "HazardClasses/Tilemap.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/TmpObjectHuge.hpp"

void Tilemap::ScrollRight(int32_t param_1, uint8_t* param_2) {
  if (param_1 < 0x3e000) {
    uint8_t* src = param_2;
    for (int32_t loopCounter = 0x10; loopCounter != 0; loopCounter--) {
      memcpy(&this->tileCacheData->start[param_1], src, 32);
      param_1 += 0x200;
      src += 0x20;
    }
    return;
  }

  int32_t firstBlockIndex = 0;
  uint8_t* src;
  if (param_1 < 0x40000) {
    firstBlockIndex = (0x401ffU - param_1) >> 9;
    src = param_2;
    for (; param_1 < 0x40000; param_1 += 0x200) {
      memcpy(&this->tileCacheData->start[param_1], src, 32);
      src += 0x20;
    }
  }

  param_1 -= 0x40000;
  if (firstBlockIndex < 0x10) {
    int32_t count = 0x10 - firstBlockIndex;
    do {
      memcpy(&this->tileCacheData->start[param_1], src, 32);
      param_1 += 0x200;
      src += 0x20;
      count--;
    } while (count != 0);
  }

  int32_t finalOffset = param_1 & 0x1ff;
  memcpy(&this->tileCacheData->last_1024b[finalOffset], &this->tileCacheData->start[finalOffset], 32);
}
