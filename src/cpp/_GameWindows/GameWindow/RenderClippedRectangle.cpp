#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/RenderArrays.hpp"
#include "HazardGlobals.hpp"

void GameWindow::RenderClippedRectangle(int32_t startX, int32_t startY, int16_t* dataBuffer, int16_t width, int16_t height, int32_t layer) {
  int32_t flooredStartX;
  int32_t flooredStartY;
  int16_t* pixelRowPointer;

  flooredStartX = startX < 0 ? 0 : startX;
  flooredStartY = startY < 0 ? 0 : startY;
  int32_t cappedEndX = (this->windowWidth > width + startX) ? width + startX : this->windowWidth;
  int32_t cappedEndY = (this->windowHeight > height + startY) ? height + startY : this->windowHeight;

  if ((cappedEndX <= flooredStartX) || (cappedEndY <= flooredStartY)) {
    return;
  }
  pixelRowPointer = dataBuffer + ((flooredStartY - startY) * width) + (flooredStartX - startX);
  while (flooredStartY < cappedEndY) {
    this->ManageRenderLayers(flooredStartY, flooredStartX, cappedEndX, pixelRowPointer, layer);
    flooredStartY = flooredStartY + 1;
    pixelRowPointer = pixelRowPointer + width;
  }
}
