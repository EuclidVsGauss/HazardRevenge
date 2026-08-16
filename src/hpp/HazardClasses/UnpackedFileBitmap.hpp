#ifndef HAZARD_UNPACKEDFILEBITMAP_HPP
#define HAZARD_UNPACKEDFILEBITMAP_HPP

#include "HazardStructs/RgbColor.hpp"
#include "HazardTypedef.hpp"

struct RgbColor;

class UnpackedFileBitmap {
public:
  static void __fastcall Calculate2ByteColorMap(RgbColor* colormapAddress, int16_t* color2b, int32_t dummy);
  static UnpackedFileBitmap* __fastcall ParseBmpFile(char* filename);

  int32_t length1;
  int32_t length2;
  RgbColor* rgbColorMapAddress;
  int16_t* shortColorMapAddress;
  byte* imageAddress;
  RgbColor rgbColorMap[256];
  int16_t shortColorMap[256];
  int32_t unused;
  byte startOfImage;
};

#endif
