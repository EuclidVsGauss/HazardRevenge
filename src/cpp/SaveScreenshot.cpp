#include <stdio.h>
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ParseBmpHelper.hpp"

void __fastcall SaveScreenshot(char* saveFilePath) {
  FILE* saveFileHandle;
  int32_t pixelIndex;
  int32_t pixel;
  DDSURFACEDESC surfaceDescriptor;

  ParseBmpHelper bmpInfoHeader = {
      40, 640, 480, 1, 24, 0, 0, 0, 0, 0, 0};

  struct {
    uint8_t bfType[2];
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
  } bmpFileHeader = {
      {'B', 'M'}, 0x36, 0, 0, 0x36};

  if (DirectDrawSurface != nullptr) {
    saveFileHandle = fopen(saveFilePath, s_wb);
    fwrite(&bmpFileHeader, 1, 14, saveFileHandle);
    fwrite(&bmpInfoHeader, 1, 40, saveFileHandle);

    surfaceDescriptor.dwSize = 108;
    DirectDrawSurface->Lock(nullptr, &surfaceDescriptor, 17, nullptr);

    pixelIndex = 0;
    do {
      pixel = (int32_t)*(int16_t*)(surfaceDescriptor.lPitch + ((pixelIndex % 640) * 2));
      fputc((pixel >> ((byte)BlueOffset1)) << InvBlueOffset, saveFileHandle);
      fputc((pixel >> ((byte)GreenOffset1)) << InvGreenOffset, saveFileHandle);
      fputc((pixel >> ((byte)RedOffset1)) << InvRedOffset, saveFileHandle);
      pixelIndex = pixelIndex + 1;
    } while (pixelIndex < 307200);

    DirectDrawSurface->Unlock(nullptr);
    fclose(saveFileHandle);
  }
}
