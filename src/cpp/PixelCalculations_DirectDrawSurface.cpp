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
  DirectDrawSurface->Lock((RECT*)nullptr, &surfaceDescriptor, 0x11, (HANDLE) nullptr);
  row = 0;
  snapshotRowPtr = (int16_t*)screenSnapshot;
  do {
    extractedR = surfaceDescriptor.lPitch * row;
    row = row + 1;
    srcPixelPtr = (byte*)(extractedR + (intptr_t)surfaceDescriptor.lpSurface);
    memcpy(snapshotRowPtr, srcPixelPtr, 1280);
    snapshotRowPtr = snapshotRowPtr + 0x280;
  } while (row < 480);
  DirectDrawSurface->Unlock(nullptr);
  for (int32_t currentBrightness = maxBrightness; minBrightness <= currentBrightness; currentBrightness = currentBrightness - 1) {
    col = 0;
    snapshotRowPtr = (int16_t*)intensityLut;
    do {
      extractedR = col >> ((byte)RedOffset1 & 0x1f);
      extractedG = col >> ((byte)GreenOffset1 & 0x1f);
      extractedB = col >> ((byte)BlueOffset1 & 0x1f);
      col = col + 1;
      *snapshotRowPtr = (int16_t)(((int32_t)((extractedR << ((byte)InvRedOffset & 0x1f) & 0xff) * currentBrightness) / maxBrightness >> ((byte)InvRedOffset & 0x1f)) << ((byte)RedOffset1 & 0x1f)) + (int16_t)(((int32_t)((extractedG << ((byte)InvGreenOffset & 0x1f) & 0xff) * currentBrightness) / maxBrightness >> ((byte)InvGreenOffset & 0x1f)) << ((byte)GreenOffset1 & 0x1f)) + (int16_t)(((int32_t)((extractedB << ((byte)InvBlueOffset & 0x1f) & 0xff) * currentBrightness) / maxBrightness >> ((byte)InvBlueOffset & 0x1f)) << ((byte)BlueOffset1 & 0x1f));
      snapshotRowPtr = snapshotRowPtr + 1;
    } while (col < 0x10000);
    surfaceLostResult = DirectDrawSurface->IsLost();
    if (surfaceLostResult == -0x7789fe3e) {
      DirectDrawSurface->Restore();
    }
    surfaceDescriptor.dwSize = 108;
    DirectDrawSurface->Lock((RECT*)nullptr, &surfaceDescriptor, 0x21, (HANDLE) nullptr);
    screenRow = 0;
    snapshotRowPtr = (int16_t*)screenSnapshot;
    do {
      col = 640;
      rowEnd = snapshotRowPtr + 640;
      destPixelPtr = (int16_t*)((surfaceDescriptor.lPitch * screenRow) + (intptr_t)surfaceDescriptor.lpSurface);
      do {
        pixelValue = *snapshotRowPtr;
        snapshotRowPtr = snapshotRowPtr + 1;
        col = col + -1;
        *destPixelPtr = intensityLut->pixels_2pow16[pixelValue];
        destPixelPtr = destPixelPtr + 1;
      } while (col != 0);
      screenRow = screenRow + 1;
      snapshotRowPtr = rowEnd;
    } while (screenRow < 0x1e0);
    DirectDrawSurface->Unlock(nullptr);
  }

  delete intensityLut;
  delete screenSnapshot;
}
