#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

ImageVectorWithHeader* __fastcall DecodeShadowSprite(byte* imageVector, int32_t width, int32_t height, int32_t transparentColor, int32_t fillColor, int32_t centerX, int32_t centerY) {
  byte currentPixel;
  byte transparentPixel;
  int16_t pixelCount;
  int16_t fillValue;
  int32_t topTrimRows;
  int32_t bottomTrimRows;
  int32_t xPosition;
  ImageVectorWithHeader* shadowSprite;
  byte* trimmedImageStart;
  uint32_t fillLoopCounter;
  int32_t dataOffset;
  int32_t transparentRunLength;
  byte* rowPtr;
  uint32_t transparentCount;
  int16_t* fillDestinationPtr;
  int32_t verticalOffset;
  int32_t currentY;
  byte* currentRow;

  transparentPixel = (byte)transparentColor;
  topTrimRows = 0;
  if (*imageVector != (byte)transparentColor) {
    do {
      if (width * height <= topTrimRows) {
        break;
      }
      topTrimRows = topTrimRows + 1;
    } while (imageVector[topTrimRows] != (byte)transparentColor);
  }
  topTrimRows = topTrimRows / width;
  dataOffset = width * (height - topTrimRows);
  trimmedImageStart = imageVector + (topTrimRows * width);
  bottomTrimRows = 0;
  if (trimmedImageStart[dataOffset + -1] != (byte)transparentColor) {
    rowPtr = trimmedImageStart + dataOffset + -1;
    do {
      if (dataOffset <= bottomTrimRows) {
        break;
      }
      bottomTrimRows = bottomTrimRows + 1;
      rowPtr = rowPtr + -1;
    } while (*rowPtr != (byte)transparentColor);
  }
  dataOffset = 0;
  bottomTrimRows = (height - topTrimRows) - (bottomTrimRows / width);
  rowPtr = trimmedImageStart;
  verticalOffset = bottomTrimRows;
  if (0 < bottomTrimRows) {
    do {
      xPosition = 0;
      if (0 < width) {
        do {
          currentPixel = rowPtr[xPosition];
          for (; (currentPixel != (byte)transparentColor && (xPosition < width)); xPosition = xPosition + 1) {
            currentPixel = rowPtr[xPosition + 1];
          }
          transparentRunLength = 0;
          currentPixel = rowPtr[xPosition];
          while ((currentPixel == (byte)transparentColor && (xPosition < width))) {
            xPosition = xPosition + 1;
            transparentRunLength = transparentRunLength + 1;
            currentPixel = rowPtr[xPosition];
          }
          dataOffset = dataOffset + 2 + transparentRunLength;
        } while (xPosition < width);
      }
      verticalOffset = verticalOffset + -1;
      rowPtr = rowPtr + width;
    } while (verticalOffset != 0);
  }

  int32_t pointerArraySize = sizeof(int16_t*) * bottomTrimRows;
  int32_t dataSize = (dataOffset + 10) * sizeof(int16_t);

  int32_t headerSize = (4 * sizeof(int32_t)) + sizeof(int16_t**);

  shadowSprite = (ImageVectorWithHeader*)new byte[headerSize + pointerArraySize + dataSize];
  shadowSprite->spriteCoordX = centerX;
  shadowSprite->spriteCoordY = centerY - topTrimRows;
  shadowSprite->spriteWidth1 = width;
  shadowSprite->spriteWidth2 = bottomTrimRows;
  shadowSprite->startOfImageAddress = (int16_t**)shadowSprite->varibleArray;

  byte* dataStart = (byte*)shadowSprite->varibleArray + pointerArraySize;

  dataOffset = 0;
  centerX = 0;
  currentY = 0;
  currentRow = trimmedImageStart;

  if (0 < bottomTrimRows) {
    do {

      shadowSprite->startOfImageAddress[currentY] = (int16_t*)(dataStart + (dataOffset * 2));

      xPosition = 0;
      if (0 < width) {
        do {
          pixelCount = 0;
          currentPixel = currentRow[xPosition];
          while ((currentPixel != transparentPixel && (xPosition < width))) {
            xPosition = xPosition + 1;
            pixelCount = pixelCount + 1;
            currentPixel = currentRow[xPosition];
          }
          transparentCount = 0;
          currentPixel = currentRow[xPosition];
          while ((currentPixel == transparentPixel && (xPosition < width))) {
            xPosition = xPosition + 1;
            transparentCount = transparentCount + 1;
            currentPixel = currentRow[xPosition];
          }

          *(int16_t*)(dataStart + (dataOffset * 2)) = pixelCount;
          *(int16_t*)(dataStart + (dataOffset * 2) + 2) = (int16_t)transparentCount;

          if (0 < (int32_t)transparentCount) {
            fillValue = (int16_t)fillColor;
            fillDestinationPtr = (int16_t*)(dataStart + (dataOffset * 2) + 4);

            for (fillLoopCounter = transparentCount >> 1; fillLoopCounter != 0; fillLoopCounter = fillLoopCounter - 1) {
              *(uint16_t*)fillDestinationPtr = fillValue;
              *(uint16_t*)(fillDestinationPtr + 1) = fillValue;
              fillDestinationPtr = (int16_t*)((intptr_t)fillDestinationPtr + 4);
            }
            for (fillLoopCounter = (uint32_t)((transparentCount & 1) != 0); dataOffset = centerX, fillLoopCounter != 0; fillLoopCounter = fillLoopCounter - 1) {
              *fillDestinationPtr = fillValue;
              fillDestinationPtr = fillDestinationPtr + 1;
            }
          }

          dataOffset = dataOffset + 2 + transparentCount;
          centerX = dataOffset;
        } while (xPosition < width);
      }
      currentY = currentY + 1;
      currentRow = currentRow + width;
    } while (currentY < bottomTrimRows);
  }
  return shadowSprite;
}
