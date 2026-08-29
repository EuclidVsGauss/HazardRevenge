#include "HazardClasses/UnpackedFileBitmap.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/RgbColor.hpp"

void __fastcall UnpackedFileBitmap::Calculate2ByteColorMap(RgbColor* colormapAddress, int16_t* color2b, int32_t unused) {
  int32_t counter;
  int16_t* currentColor2b;
  signed char blue, green, red;
  int16_t colorValue;

  (void)unused;

  currentColor2b = color2b;
  for (counter = 0; counter < 256; counter++) {
    green = colormapAddress->green >> InvGreenOffset;
    colorValue = (int16_t)green << GreenOffset1;

    blue = colormapAddress->blue >> InvBlueOffset;
    colorValue += (int16_t)blue << BlueOffset1;

    red = colormapAddress->red >> InvRedOffset;
    colorValue += (int16_t)red << RedOffset1;

    *currentColor2b = colorValue;

    currentColor2b++;
    colormapAddress++;
  }
}
