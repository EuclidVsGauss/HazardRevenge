#include "HazardGlobals.hpp"

void ReleaseDirectDraw() {
  ShowWindow(GameFullscreenWindow, 0);
  DirectDrawSurface->Release();
  DirectDrawObject->RestoreDisplayMode();
  DirectDrawObject->Release();
}
