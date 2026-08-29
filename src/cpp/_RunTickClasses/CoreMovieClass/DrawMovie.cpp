#include <ddraw.h>
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/DirectDrawClass.hpp"
#include "HazardExterns/CoreMovieClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardPatches.hpp"

void DirectDrawClass::DrawMovie(int32_t param1_0, int32_t param2_40, int16_t* array, int32_t width_640, int32_t height_160, byte param_6) {
  uint32_t bytesPerRow;
  HRESULT hResult;
  int32_t heightRemaining;
  byte* destPixel;
  byte* srcPixel;
  RECT destRect;
  DDSURFACEDESC surfaceDesc;

  (void)param_6;

  heightRemaining = (int32_t)(int16_t)height_160;

  destRect.left = param1_0;
  destRect.right = param1_0 + (int16_t)width_640;
  destRect.top = param2_40 * 2;
  destRect.bottom = (heightRemaining + param2_40) * 2;

  hResult = DirectDrawSurface->IsLost();
  if (hResult == DDERR_SURFACELOST) {
    DirectDrawSurface->Restore();
  }
  surfaceDesc.dwSize = 108;
  DirectDrawSurface->Lock(&destRect, &surfaceDesc, 0x21, nullptr);
  if (0 < heightRemaining) {
    bytesPerRow = (int16_t)width_640 * 2;
    destPixel = (byte*)surfaceDesc.lpSurface;
    srcPixel = (byte*)array;
    for (int32_t i = 0; i < heightRemaining; i++) {
      memcpy(destPixel, srcPixel, bytesPerRow);
#if PATCH_FILL_EMPTY_MOVIE_LINES == 1
      memcpy(destPixel + bytesPerRow, srcPixel, bytesPerRow);
#endif
      destPixel += bytesPerRow;
      srcPixel += bytesPerRow;
      destPixel = destPixel + (destRect.right * 2);
    }
  }
  DirectDrawSurface->Unlock(nullptr);
  MovieCallCounter = MovieCallCounter + 1;
}
