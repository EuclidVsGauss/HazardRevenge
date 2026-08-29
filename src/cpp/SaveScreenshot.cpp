#include <stdio.h>
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ParseBmpHelper.hpp"

#pragma pack(push, 1)

struct BmpFileHeader {
  uint8_t bfType[2];
  uint32_t bfSize;
  uint16_t bfReserved1;
  uint16_t bfReserved2;
  uint32_t bfOffBits;
};

#pragma pack(pop)

void __fastcall SaveScreenshot(char* saveFilePath) {
  FILE* saveFileHandle;
  int32_t pixelIndex;
  int32_t pixel;
  DDSURFACEDESC surfaceDescriptor;

  ParseBmpHelper bmpInfoHeader = {
      40, 640, 480, 1, 24, 0, 0, 0, 0, 0, 0};

  BmpFileHeader bmpFileHeader = {
      {'B', 'M'}, 0xe, 0, 0, 0x36};

  if (DirectDrawSurface != nullptr) {
    saveFileHandle = fopen(saveFilePath, s_wb);
    fwrite(&bmpFileHeader, 1, 14, saveFileHandle);
    fwrite(&bmpInfoHeader, 1, 40, saveFileHandle);

    surfaceDescriptor.dwSize = 108;
    DirectDrawSurface->Lock(nullptr, &surfaceDescriptor, 17, nullptr);

    byte* surfaceBase = (byte*)surfaceDescriptor.lpSurface;
    for (pixelIndex = 0; pixelIndex < 307200; pixelIndex = pixelIndex + 1) {
      pixel = (int32_t)*(int16_t*)(surfaceBase + ((0x1df - (pixelIndex / 0x280)) * surfaceDescriptor.lPitch) + ((pixelIndex % 640) * 2));
      fputc((pixel >> ((byte)BlueOffset1)) << InvBlueOffset, saveFileHandle);
      fputc((pixel >> ((byte)GreenOffset1)) << InvGreenOffset, saveFileHandle);
      fputc((pixel >> ((byte)RedOffset1)) << InvRedOffset, saveFileHandle);
    }

    DirectDrawSurface->Unlock(nullptr);
    fclose(saveFileHandle);
  }
}
