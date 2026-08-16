#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/RenderArrays.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindow::RenderClippedSprite(int32_t screenX, int32_t screenY, ImageVectorWithHeader* sprite, int32_t layerIndex) {
  int16_t* rowDataPtr;
  int32_t relY;
  int32_t clampedSrcX;
  int32_t clampedDestX;
  int32_t srcOffsetX;
  int32_t windowW;
  int32_t transparentRunLength;
  int32_t destXEnd;
  int32_t maxClipY;
  int32_t maxClipX;

  if (sprite != nullptr) {
    srcOffsetX = screenX - sprite->spriteCoordX;
    relY = screenY - sprite->spriteCoordY;
    windowW = this->windowWidth;
    maxClipX = sprite->spriteWidth1 + srcOffsetX;
    int32_t currentY = (relY < 0) ? 0 : relY;
    int32_t startSrcX = (srcOffsetX < 0) ? 0 : srcOffsetX;

    if (windowW <= maxClipX) {
      maxClipX = windowW;
    }
    windowW = this->windowHeight;
    maxClipY = sprite->spriteWidth2 + relY;
    if (windowW <= maxClipY) {
      maxClipY = windowW;
    }

    if ((startSrcX < maxClipX) && (currentY < maxClipY)) {
      int32_t drawY = currentY;
      do {
        rowDataPtr = sprite->startOfImageAddress[drawY - relY];
        destXEnd = srcOffsetX;
        while (destXEnd < maxClipX) {
          transparentRunLength = (int32_t)rowDataPtr[1];
          destXEnd = destXEnd + rowDataPtr[0] + transparentRunLength;
          if (rowDataPtr[1] != 0) {
            clampedSrcX = (destXEnd - transparentRunLength) & ((destXEnd - transparentRunLength < 1) - 1);

            clampedDestX = this->windowWidth;
            if (destXEnd <= clampedDestX) {
              clampedDestX = destXEnd;
            }
            if (clampedSrcX < clampedDestX) {
              this->ManageRenderLayers(currentY, clampedSrcX, clampedDestX, rowDataPtr + (transparentRunLength - destXEnd) + clampedSrcX + 2, layerIndex);
            }
            rowDataPtr = rowDataPtr + transparentRunLength + 2;
          }
        }
        currentY = currentY + 1;
        drawY = drawY + 1;
      } while (currentY < maxClipY);
    }
  }
}
