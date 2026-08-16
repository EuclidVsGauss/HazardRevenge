#include "HazardPatches.hpp"
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/DirectDrawClass.hpp"
#include "HazardExterns/CoreMovieClass.hpp"
#include "HazardGlobals.hpp"

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
  if (hResult == 0x887601c2) {
    DirectDrawSurface->Restore();
  }
  surfaceDesc.dwSize = 108;
  DirectDrawSurface->Lock(&destRect, &surfaceDesc, 0x21, (HANDLE) nullptr);
  if (0 < heightRemaining) {
    bytesPerRow = (int16_t)width_640 * 2;
    destPixel = (byte*)surfaceDesc.lpSurface;
    srcPixel = (byte*)array;

    do {
      memcpy(destPixel, srcPixel, bytesPerRow);
#if PATCH_FILL_EMPTY_MOVIE_LINES == 1
      memcpy(destPixel + bytesPerRow, srcPixel, bytesPerRow);
#endif
      destPixel += bytesPerRow;
      srcPixel += bytesPerRow;

      destPixel = destPixel + (destRect.right * 2);
      heightRemaining = heightRemaining + -1;
    } while (heightRemaining != 0);
  }
  DirectDrawSurface->Unlock(nullptr);
  MovieCallCounter = MovieCallCounter + 1;
}
