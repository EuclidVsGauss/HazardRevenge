#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

ImageVectorWithHeader* __fastcall DecodeSolidSprite(byte* startOfImage, int32_t length1, int32_t length2, int32_t null, int16_t* shortColorMapAddress, int32_t halfLength1, int32_t halfLength2) {
  byte currentByte;
  int32_t totalSize;
  ImageVectorWithHeader* result;
  int32_t position1;
  int32_t position2;
  byte* currentPtr;
  int32_t count1;
  byte* nextPtr;
  int32_t count2;
  int16_t* colorPtr;
  int32_t rowCount;
  int32_t tempOffset;
  int32_t tempIndex;
  int32_t loopIndex;
  byte* rowPointer;

  totalSize = 0;
  if (*startOfImage == (byte)null) {
    do {
      if (length1 * length2 <= totalSize) {
        break;
      }
      loopIndex = totalSize + 1;
      totalSize = totalSize + 1;
    } while (startOfImage[loopIndex] == (byte)null);
  }
  totalSize = totalSize / length1;
  position2 = length1 * (length2 - totalSize);
  nextPtr = startOfImage + (totalSize * length1);

  loopIndex = 0;
  if (nextPtr[position2 + -1] == (byte)null) {
    currentPtr = nextPtr + position2 + -1;
    do {
      if (position2 <= loopIndex) {
        break;
      }
      loopIndex = loopIndex + 1;
      currentPtr = currentPtr + -1;
    } while (*currentPtr == (byte)null);
  }
  rowCount = 0;
  loopIndex = (length2 - totalSize) - (loopIndex / length1);
  currentPtr = nextPtr;
  tempOffset = loopIndex;
  if (0 < loopIndex) {
    do {
      position2 = 0;
      if (0 < length1) {
        do {
          currentByte = currentPtr[position2];
          for (; (currentByte == (byte)null && (position2 < length1)); position2 = position2 + 1) {
            currentByte = currentPtr[position2 + 1];
          }
          count1 = 0;
          currentByte = currentPtr[position2];

          while (position2 < length1 && currentByte != (byte)null) {
            count1++;
            if (++position2 < length1) {
              currentByte = currentPtr[position2];
            }
            else {
              break;
            }
          }
          rowCount = rowCount + 2 + count1;
        } while (position2 < length1);
      }
      tempOffset = tempOffset + -1;
      currentPtr = currentPtr + length1;
    } while (tempOffset != 0);
  }

  int32_t pointerArraySize = sizeof(int16_t*) * loopIndex;
  int32_t dataSize = (rowCount + 10) * sizeof(int16_t);

  int32_t headerSize = (4 * sizeof(int32_t)) + sizeof(int16_t**);

  result = (ImageVectorWithHeader*)new byte[headerSize + pointerArraySize + dataSize];
  result->spriteCoordX = halfLength1;
  result->spriteCoordY = halfLength2 - totalSize;
  result->spriteWidth1 = length1;
  result->spriteWidth2 = loopIndex;
  result->startOfImageAddress = (int16_t**)result->varibleArray;

  byte* dataStart = (byte*)result->varibleArray + pointerArraySize;

  rowCount = 0;
  tempIndex = 0;
  rowPointer = nextPtr;

  if (0 < loopIndex) {
    do {

      result->startOfImageAddress[tempIndex] = (int16_t*)(dataStart + (rowCount * 2));

      position2 = 0;
      if (0 < length1) {
        do {
          currentByte = rowPointer[position2];
          halfLength2 = 0;
          for (; (currentByte == (byte)null && (position2 < length1)); position2 = position2 + 1) {
            currentByte = rowPointer[position2 + 1];
            halfLength2 = (int16_t)halfLength2 + 1;
          }

          currentByte = rowPointer[position2];
          count1 = 0;
          while (position2 < length1 && currentByte != (byte)null) {
            count1++;
            if (++position2 < length1) {
              currentByte = rowPointer[position2];
            }
            else {
              break;
            }
          }

          *(int16_t*)(dataStart + (rowCount * 2)) = (int16_t)halfLength2;
          *(int16_t*)(dataStart + (rowCount * 2) + 2) = (int16_t)count1;

          count2 = 0;
          if (0 < count1) {
            colorPtr = (int16_t*)(dataStart + (rowCount * 2) + 4);
            do {
              position1 = count2 - count1;
              count2 = count2 + 1;
              *colorPtr = shortColorMapAddress[rowPointer[position1 + position2]];
              colorPtr = colorPtr + 1;
            } while (count2 < count1);
          }
          rowCount = rowCount + 2 + count1;
        } while (position2 < length1);
      }
      tempIndex = tempIndex + 1;
      rowPointer = rowPointer + length1;
    } while (tempIndex < loopIndex);
  }
  return result;
}
