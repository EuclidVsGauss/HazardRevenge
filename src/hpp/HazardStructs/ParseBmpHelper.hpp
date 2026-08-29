#ifndef HAZARD_PARSEBMPHELPER_HPP
#define HAZARD_PARSEBMPHELPER_HPP
#include "HazardTypedef.hpp"

struct ParseBmpHelper {
  int32_t bitmapSize;
  int32_t bitmapWidth;
  int32_t bitmapHeight;
  uint16_t bitmapPlanes;
  int16_t bitmapBitCount;
  uint32_t bitmapCompression;
  uint32_t bitmapSizeImage;
  int32_t bitmapXPelsPerMeter;
  int32_t bitmapYPelsPerMeter;
  int32_t bitmapClrUsed;
  int32_t bitmapClrImportant;
};
typedef struct ParseBmpHelper ParseBmpHelper, *PParseBmpHelper;

#endif
