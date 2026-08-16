#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardExterns/CoreActClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/SpriteMapPair.hpp"

void CoreActClass::LoadActSpriteData(char* sprFilename, int32_t dimension1, int32_t dimension2) {

  byte readByte;
  byte byteToDuplicate;
  UnpackedFileBase* sprFile;
  uint32_t bytesToCopy;
  ImageVectorWithHeader* shadowSprite;
  ImageVectorWithHeader* solidSprite;
  SpriteMapPair* currentEntry;
  byte* packedPixelBuffer;
  uint16_t* colorPixel;
  int32_t colorsCounter;
  int16_t spriteWidth;
  int16_t spriteHeight;
  int16_t numberSprFrames;
  CoreActClass* actObject;
  int16_t tempOffsetX;
  int16_t tempOffsetY;
  int16_t numberColors;
  SpriteMapPair* cachedEntryHead;
  SpriteMapPair* searchPtr;
  int32_t frameIndex;
  int32_t pixelCount;
  int32_t totalPixels;
  uint16_t colorArray[256];

  cachedEntryHead = LoadActHelperSpriteMapPair;
  searchPtr = LoadActHelperSpriteMapPair;
  packedPixelBuffer = (byte*)sprFilename;
  if (LoadActHelperSpriteMapPair != nullptr) {

    while (searchPtr != nullptr) {

      if (strcmp(searchPtr->sprName, sprFilename) == 0) {

        if (searchPtr->scalar > 0) {
          this->solidSpriteMap = searchPtr->imageVectors;
          this->shadowSpriteMap = searchPtr->sprImageArray;
          searchPtr->scalar++;
          return;
        }
        break;
      }
      searchPtr = searchPtr->previous;
    }
  }
  searchPtr = cachedEntryHead;
  actObject = this;
  sprFile = UnpackedFileBase::LoadFileFromArchive(sprFilename, 0x20000);
  sprFile->readFile(&numberSprFrames, 2);
  this->solidSpriteMap = (ImageVectorWithHeader**)new byte[((numberSprFrames * sizeof(int32_t*)) + sizeof(int32_t*))];
  this->shadowSpriteMap = (ImageVectorWithHeader**)new byte[((int32_t)numberSprFrames * sizeof(int32_t*))];
  frameIndex = 0;
  if (0 < numberSprFrames) {
    for (frameIndex = 0; frameIndex < numberSprFrames; frameIndex++) {

      sprFile->readFile(&numberColors, 2);
      if (numberColors != 0) {
        sprFile->readFile(colorArray, (int32_t)numberColors << 1);
        colorsCounter = (int32_t)numberColors;
        if (0 < colorsCounter) {
          colorPixel = colorArray;
          do {
            bytesToCopy = (uint32_t)*colorPixel;
            colorsCounter = colorsCounter + -1;
            *colorPixel = (int16_t)(((int32_t)((bytesToCopy & 0x1f) << 3) >> ((byte)InvBlueOffset & 0x1f)) << ((byte)BlueOffset1 & 0x1f)) + (int16_t)(((int32_t)((int32_t)bytesToCopy >> 3 & 0xfcU) >> ((byte)InvGreenOffset & 0x1f)) << ((byte)GreenOffset1 & 0x1f)) + (int16_t)(((int32_t)((int32_t)bytesToCopy >> 8 & 0xf8U) >> ((byte)InvRedOffset & 0x1f)) << ((byte)RedOffset1 & 0x1f));
            colorPixel = colorPixel + 1;

          } while (colorsCounter != 0);
        }
      }
      sprFile->readFile(&tempOffsetX, 2);
      sprFile->readFile(&tempOffsetY, 2);
      sprFile->readFile(&spriteWidth, 2);
      sprFile->readFile(&spriteHeight, 2);
      if (((int32_t)spriteHeight * (int32_t)spriteWidth) - SizeInMemory_ActString != 0 && (int32_t)SizeInMemory_ActString <= (int32_t)spriteHeight * (int32_t)spriteWidth) {
        if (NestedLoadActHelperConstant != nullptr) {

          delete NestedLoadActHelperConstant;
        }
        SizeInMemory_ActString = (int32_t)spriteHeight * (int32_t)spriteWidth;
        NestedLoadActHelperConstant = new byte[SizeInMemory_ActString * 2];
      }
      totalPixels = (int32_t)spriteHeight * (int32_t)spriteWidth;
      pixelCount = 0;

      packedPixelBuffer = NestedLoadActHelperConstant;
      if (0 < totalPixels) {
        do {
          readByte = sprFile->readByte();

          if (readByte > 128) {
            bytesToCopy = readByte & 127;
            byteToDuplicate = sprFile->readByte();
            memset(packedPixelBuffer + pixelCount, byteToDuplicate, bytesToCopy);
          }
          else {
            bytesToCopy = (uint32_t)readByte;
            sprFile->readFile((packedPixelBuffer + pixelCount), bytesToCopy);
          }
          pixelCount = pixelCount + bytesToCopy;

        } while (pixelCount < totalPixels);
      }
      shadowSprite = DecodeShadowSprite(NestedLoadActHelperConstant, (int32_t)spriteWidth, (int32_t)spriteHeight, 1, 0, tempOffsetX - dimension1, tempOffsetY - dimension2);
      actObject->shadowSpriteMap[frameIndex] = shadowSprite;
      pixelCount = 0;
      packedPixelBuffer = NestedLoadActHelperConstant;
      if (0 < totalPixels) {
        do {
          if (packedPixelBuffer[pixelCount] == 1) {
            packedPixelBuffer[pixelCount] = 0;
            packedPixelBuffer = NestedLoadActHelperConstant;
          }
          pixelCount = pixelCount + 1;

        } while (pixelCount < (int32_t)spriteHeight * (int32_t)spriteWidth);
      }
      solidSprite = DecodeSolidSprite(packedPixelBuffer, (int32_t)spriteWidth, (int32_t)spriteHeight, 0, (int16_t*)colorArray, tempOffsetX - dimension1, tempOffsetY - dimension2);

      actObject->solidSpriteMap[frameIndex] = solidSprite;

      searchPtr = cachedEntryHead;
    }
  }
  this->solidSpriteMap[frameIndex] = nullptr;
  if (sprFile != nullptr) {
    delete sprFile;
  }
  if (searchPtr != nullptr) {
    searchPtr->imageVectors = this->solidSpriteMap;
    searchPtr->sprImageArray = this->shadowSpriteMap;
    searchPtr->scalar = 1;
    return;
  }
  currentEntry = new SpriteMapPair;
  bytesToCopy = strlen(sprFilename);

  memcpy(currentEntry->sprName, sprFilename, bytesToCopy);
  currentEntry->imageVectors = actObject->solidSpriteMap;
  currentEntry->sprImageArray = actObject->shadowSpriteMap;
  currentEntry->scalar = 1;
  currentEntry->previous = LoadActHelperSpriteMapPair;
  LoadActHelperSpriteMapPair = currentEntry;
}
