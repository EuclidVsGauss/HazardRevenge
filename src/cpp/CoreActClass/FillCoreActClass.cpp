#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardExterns/CoreActClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ActSummary.hpp"

CoreActClass::CoreActClass(char* actStringFilename) {
  ActContent* currentActContent;
  int32_t* frameIndexPointer;
  int32_t totalAnimationFrames;
  UnpackedFileBase* unpackedActFile;
  int32_t endOfSection;
  ActContent* allocatedActArray;
  ActSummary* newActCacheEntry;
  size_t filenameLength;
  size_t sprFilenameLength;
  int32_t* frameStartPointer;
  ActSummary* cacheEntryToPopulate;
  int32_t actionLineCounter;
  int32_t spriteDimensionY;
  int32_t spriteDimensionX;
  uint32_t savedFilePosition;
  void* animationArray;
  char spriteFilename[24];
  char sectionBuffer[32];

  ActSummary* currentCacheEntry = LatestLoadedAct;
  if (LatestLoadedAct) {
    while (currentCacheEntry) {
      if (strcmp(currentCacheEntry->actFilename, actStringFilename) == 0) {
        this->txtContent = currentCacheEntry->ptrTxtContent;
        this->numberSprFrames = currentCacheEntry->numberSprFrames;
        this->numberActLines = currentCacheEntry->numberActLines;
        this->LoadActSpriteData(currentCacheEntry->sprFilename, currentCacheEntry->actDimension1, currentCacheEntry->actDimension2);
        return;
      }
      currentCacheEntry = currentCacheEntry->formerLoadMainMenuOrAct;
    }
  }

  unpackedActFile = UnpackedFileBase::LoadFileFromArchive(actStringFilename, 0x20000);
  if (unpackedActFile != nullptr) {
    ReadInterpolatableString(unpackedActFile, s__s__d__d__d, spriteFilename, &spriteDimensionX, &spriteDimensionY, &this->numberSprFrames);
    savedFilePosition = unpackedActFile->getFilePointer();
    this->numberActLines = 0;
    totalAnimationFrames = 0;
    while (true) {
      ReadInterpolatableString(unpackedActFile, InterpolatableString, sectionBuffer);
      endOfSection = strcmp(sectionBuffer, s_end);
      if (endOfSection == 0) {
        unpackedActFile->setFilePointer(savedFilePosition, 0);
        animationArray = new byte[(totalAnimationFrames + 1) * sizeof(int32_t*)];
        allocatedActArray = (ActContent*)new byte[(this->numberActLines * sizeof(ActContent))];
        this->txtContent = allocatedActArray;
        totalAnimationFrames = 0;

        for (actionLineCounter = 0; actionLineCounter < this->numberActLines; actionLineCounter++) {
          currentActContent = this->txtContent + actionLineCounter;
          *(int32_t*)currentActContent->actionName = 0;
          *(int32_t*)(currentActContent->actionName + 4) = 0;
          *(int32_t*)(currentActContent->actionName + 8) = 0;
          *(int32_t*)(currentActContent->actionName + 0xc) = 0;
          ReadInterpolatableString(unpackedActFile, InterpolatableString, this->txtContent + actionLineCounter);
          frameStartPointer = &((int32_t*)animationArray)[totalAnimationFrames];
          this->txtContent[actionLineCounter].ptrFrameStart = frameStartPointer;
          this->txtContent[actionLineCounter].numberFrames = 0;
          while (unpackedActFile->readByte() != '\n') {
            ReadInterpolatableString(unpackedActFile, s__d, frameStartPointer);
            frameIndexPointer = &this->txtContent[actionLineCounter].numberFrames;
            frameStartPointer = frameStartPointer + 1;
            totalAnimationFrames = totalAnimationFrames + 1;
            *frameIndexPointer = *frameIndexPointer + 1;
          }
          if (this->txtContent[actionLineCounter].numberFrames == 0) {
            WrapperMessageBoxA(this->txtContent[actionLineCounter].actionName, actStringFilename);
          }
        }
        UnpackedFileBase::CloseUnpackedFile(unpackedActFile);
        break;
      }

      while (unpackedActFile->readByte() != '\n') {
        ReadInterpolatableString(unpackedActFile, s__d, &actionLineCounter);
        totalAnimationFrames = totalAnimationFrames + 1;
      }
      this->numberActLines = this->numberActLines + 1;
    }
  }

  newActCacheEntry = (ActSummary*)new byte[sizeof(ActSummary)];
  newActCacheEntry->formerLoadMainMenuOrAct = LatestLoadedAct;
  filenameLength = strlen(actStringFilename) + 1;
  cacheEntryToPopulate = newActCacheEntry;
  LatestLoadedAct = newActCacheEntry;
  memcpy(cacheEntryToPopulate->actFilename, actStringFilename, filenameLength);
  sprFilenameLength = strlen(spriteFilename) + 1;
  memcpy(newActCacheEntry->sprFilename, spriteFilename, sprFilenameLength);

  newActCacheEntry->actDimension1 = spriteDimensionX;
  newActCacheEntry->actDimension2 = spriteDimensionY;
  newActCacheEntry->numberSprFrames = this->numberSprFrames;
  newActCacheEntry->numberActLines = this->numberActLines;
  newActCacheEntry->ptrTxtContent = this->txtContent;
  this->LoadActSpriteData(spriteFilename, spriteDimensionX, spriteDimensionY);
}
