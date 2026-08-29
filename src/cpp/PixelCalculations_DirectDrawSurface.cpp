#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/PixelArray1_131072.hpp"
#include "HazardStructs/PixelArray2_614400.hpp"

void __fastcall PixelCalculations_DirectDrawSurface(int32_t maxBrightness, int32_t minBrightness) {
  uint16_t pixelValue;
  PixelArray1_131072* intensityLut;
  PixelArray2_614400* screenSnapshot;
  int32_t row;
  int32_t extractedR;
  int32_t extractedG;
  int32_t extractedB;
  HRESULT surfaceLostResult;
  byte* srcPixelPtr;
  int32_t col;
  int16_t* rowEnd;
  int16_t* destPixelPtr;
  int32_t screenRow;
  DDSURFACEDESC surfaceDescriptor;
  int16_t* snapshotRowPtr;

  intensityLut = new PixelArray1_131072();
  screenSnapshot = new PixelArray2_614400();
  surfaceDescriptor.dwSize = 108;
  DirectDrawSurface->Lock(nullptr, &surfaceDescriptor, 0x11, nullptr);
  row = 0;
  snapshotRowPtr = (int16_t*)screenSnapshot;
  do {
    extractedR = surfaceDescriptor.lPitch * row;
    row = row + 1;
    srcPixelPtr = (extractedR + (byte*)surfaceDescriptor.lpSurface);
    memcpy(snapshotRowPtr, srcPixelPtr, 1280);
    snapshotRowPtr = snapshotRowPtr + 0x280;
  } while (row < 480);
  DirectDrawSurface->Unlock(nullptr);
  for (int32_t currentBrightness = maxBrightness; currentBrightness >= minBrightness; currentBrightness = currentBrightness - 1) {
    snapshotRowPtr = (int16_t*)intensityLut;
    for (col = 0; col < 0x10000; col++) {
      extractedR = col >> RedOffset1;
      extractedG = col >> GreenOffset1;
      extractedB = col >> BlueOffset1;
      *snapshotRowPtr = (int16_t)((((extractedB << InvBlueOffset & 0xff) * currentBrightness) / maxBrightness >> InvBlueOffset) << BlueOffset1) + ((((extractedG << InvGreenOffset & 0xff) * currentBrightness) / maxBrightness >> InvGreenOffset) << GreenOffset1) + ((((extractedR << InvRedOffset & 0xff) * currentBrightness) / maxBrightness >> InvRedOffset) << RedOffset1);
      snapshotRowPtr = snapshotRowPtr + 1;
    }
    surfaceLostResult = DirectDrawSurface->IsLost();
    if (surfaceLostResult == -0x7789fe3e) {
      DirectDrawSurface->Restore();
    }
    surfaceDescriptor.dwSize = 108;
    DirectDrawSurface->Lock(nullptr, &surfaceDescriptor, 0x21, nullptr);
    snapshotRowPtr = (int16_t*)screenSnapshot;
    for (screenRow = 0; screenRow < 0x1e0; screenRow++) {
      rowEnd = snapshotRowPtr + 640;
      destPixelPtr = (int16_t*)((surfaceDescriptor.lPitch * screenRow) + (intptr_t)surfaceDescriptor.lpSurface);
      for (col = 640; col != 0; col = col + -1) {
        pixelValue = *snapshotRowPtr;
        snapshotRowPtr = snapshotRowPtr + 1;
        *destPixelPtr = intensityLut->pixels_2pow16[pixelValue];
        destPixelPtr = destPixelPtr + 1;
      }
      snapshotRowPtr = rowEnd;
    }
    DirectDrawSurface->Unlock(nullptr);
  }

  delete intensityLut;
  delete screenSnapshot;
}
