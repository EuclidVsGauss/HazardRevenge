#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardGlobals.hpp"

int16_t* __fastcall Create16BitImageFromPalette(byte* startingAddress, int32_t length1, int32_t length2, int16_t* colorMap) {
  int16_t* imageBuffer;
  int32_t pixelIndex;
  int32_t imageSize;

  imageSize = length1 * length2;
  imageBuffer = (int16_t*)new byte[(imageSize * 2)];

  if (0 < imageSize) {
    for (pixelIndex = 0; pixelIndex < imageSize; pixelIndex++) {
      imageBuffer[pixelIndex] = colorMap[startingAddress[pixelIndex]];
    }
  }
  return imageBuffer;
}
