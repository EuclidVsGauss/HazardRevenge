#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/RenderArrays.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/RenderBufferWrapper.hpp"
#include "HazardStructs/RenderListEntry.hpp"
#include "HazardStructs/RenderNodeBlock.hpp"

void GameWindow::ManageRenderLayers(int32_t runningHeight, int32_t flooredWidth, int32_t cappedWidth, int16_t* runningValue, int32_t layerIndex) {
  uint16_t layerIndexAsU16;
  int16_t leftBoundTemp;
  int16_t rightBoundTemp;
  uint16_t layerIndexAsU16_2;
  int16_t leftBoundTemp2;
  RenderNodeBlock* nextBlockCandidate;
  RenderListEntry* currentShadowEntry;
  int16_t rightBoundCandidate;
  RenderNodeBlock* writeBlockCandidate;

  RenderListEntry* currentSolidEntry;
  RenderListEntry* nextSolidEntry;
  RenderNodeBlock* newBlockCandidate;
  RenderListEntry* rightBoundaryEntry;
  int32_t startX;
  int32_t endX;
  uint32_t shadowLayerIndex;
  uint32_t negLayerIndex;
  RenderListEntry* solidHead;
  RenderListEntry* newEntry;
  RenderListEntry* tailEntry;

  RenderBufferWrapper* bufferWrapper;

  layerIndexAsU16_2 = (uint16_t)layerIndex;
  rightBoundTemp = (int16_t)layerIndex;

  if (layerIndex < 0) {

    bufferWrapper = this->ptrWrapper;
    if (bufferWrapper->entryIndex == 0x10000) {
      if (bufferWrapper->writeBlock->nextBlock == nullptr) {
        nextBlockCandidate = new RenderNodeBlock;
        nextBlockCandidate->nextBlock = nullptr;
        bufferWrapper->writeBlock->nextBlock = nextBlockCandidate;
      }
      writeBlockCandidate = bufferWrapper->writeBlock->nextBlock;
      bufferWrapper->entryIndex = 0;
      bufferWrapper->writeBlock = writeBlockCandidate;
    }
    currentShadowEntry = bufferWrapper->writeBlock->entries + bufferWrapper->entryIndex;
    bufferWrapper->entryIndex = bufferWrapper->entryIndex + 1;
    currentShadowEntry->rightBound = (int16_t)flooredWidth;
    currentShadowEntry->leftBound = (int16_t)cappedWidth;
    currentShadowEntry->layerIndex = (uint16_t)-rightBoundTemp;
    currentShadowEntry->pixelTable = runningValue;

    solidHead = (*this->arrayHeight2_shadows_copyFrom)[runningHeight];
    if (solidHead != nullptr) {
      shadowLayerIndex = (uint32_t)solidHead->layerIndex;
      negLayerIndex = (uint32_t)(-layerIndex);

      if (shadowLayerIndex == negLayerIndex || shadowLayerIndex + layerIndex >= 0) {
        tailEntry = solidHead->next;
        while (tailEntry != nullptr) {
          shadowLayerIndex = (uint32_t)tailEntry->layerIndex;
          if (shadowLayerIndex != negLayerIndex && shadowLayerIndex + layerIndex < 0) {
            break;
          }
          solidHead = tailEntry;
          tailEntry = tailEntry->next;
        }
        currentShadowEntry->next = solidHead->next;
        solidHead->next = currentShadowEntry;
        return;
      }
    }
    currentShadowEntry->next = solidHead;
    (*this->arrayHeight2_shadows_copyFrom)[runningHeight] = currentShadowEntry;
    return;
  }

  solidHead = (*this->arrayHeight1_solids_copyFrom)[runningHeight];
  while (flooredWidth < solidHead->rightBound || solidHead->leftBound <= flooredWidth) {
    solidHead = solidHead->next;
  }

  if (cappedWidth > 0) {
    do {
      layerIndexAsU16 = solidHead->layerIndex;
      currentSolidEntry = solidHead;
      while (layerIndex < (int32_t)layerIndexAsU16 && currentSolidEntry->leftBound < cappedWidth) {
        currentSolidEntry = currentSolidEntry->next;
        layerIndexAsU16 = currentSolidEntry->layerIndex;
      }

      if (layerIndex < (int32_t)currentSolidEntry->layerIndex) {
        break;
      }

      leftBoundTemp = currentSolidEntry->leftBound;
      solidHead = currentSolidEntry;
      while (leftBoundTemp < cappedWidth && (int32_t)solidHead->layerIndex <= layerIndex) {
        solidHead = solidHead->next;
        leftBoundTemp = solidHead->leftBound;
      }

      leftBoundTemp = currentSolidEntry->rightBound;
      startX = (int32_t)leftBoundTemp;
      if (leftBoundTemp < flooredWidth) {
        startX = flooredWidth;
      }
      leftBoundTemp2 = (int16_t)startX;

      startX = (int32_t)leftBoundTemp2;
      if (layerIndex < (int32_t)solidHead->layerIndex) {
        rightBoundCandidate = solidHead->rightBound;
      }
      else {
        rightBoundCandidate = solidHead->leftBound;
        if (cappedWidth < solidHead->leftBound) {
          rightBoundCandidate = (int16_t)cappedWidth;
        }
      }
      endX = (int32_t)rightBoundCandidate;

      if (currentSolidEntry == solidHead) {

        if (currentSolidEntry->leftBound == endX) {
          newEntry = currentSolidEntry->next;
        }
        else {
          bufferWrapper = this->ptrWrapper;
          if (bufferWrapper->entryIndex == 0x10000) {
            if (bufferWrapper->writeBlock->nextBlock == nullptr) {
              writeBlockCandidate = new RenderNodeBlock;
              writeBlockCandidate->nextBlock = nullptr;
              bufferWrapper->writeBlock->nextBlock = writeBlockCandidate;
            }
            writeBlockCandidate = bufferWrapper->writeBlock->nextBlock;
            bufferWrapper->entryIndex = 0;
            bufferWrapper->writeBlock = writeBlockCandidate;
          }
          newEntry = bufferWrapper->writeBlock->entries + bufferWrapper->entryIndex;
          bufferWrapper->entryIndex = bufferWrapper->entryIndex + 1;
          newEntry->rightBound = rightBoundCandidate;
          newEntry->leftBound = currentSolidEntry->leftBound;
          newEntry->pixelTable = currentSolidEntry->pixelTable + (endX - currentSolidEntry->rightBound);
          newEntry->layerIndex = currentSolidEntry->layerIndex;
          newEntry->next = currentSolidEntry->next;
        }

        if (currentSolidEntry->rightBound != startX) {
          currentSolidEntry->leftBound = leftBoundTemp2;
          bufferWrapper = this->ptrWrapper;
          if (bufferWrapper->entryIndex == 0x10000) {
            if (bufferWrapper->writeBlock->nextBlock == nullptr) {
              writeBlockCandidate = new RenderNodeBlock;
              writeBlockCandidate->nextBlock = nullptr;
              bufferWrapper->writeBlock->nextBlock = writeBlockCandidate;
            }
            writeBlockCandidate = bufferWrapper->writeBlock->nextBlock;
            bufferWrapper->entryIndex = 0;
            bufferWrapper->writeBlock = writeBlockCandidate;
          }
          nextSolidEntry = bufferWrapper->writeBlock->entries + bufferWrapper->entryIndex;
          bufferWrapper->entryIndex = bufferWrapper->entryIndex + 1;
          currentSolidEntry->next = nextSolidEntry;
          currentSolidEntry = nextSolidEntry;
        }

        currentSolidEntry->rightBound = leftBoundTemp2;
        currentSolidEntry->leftBound = rightBoundCandidate;
        currentSolidEntry->layerIndex = layerIndexAsU16_2;
        currentSolidEntry->next = newEntry;
        currentSolidEntry->pixelTable = runningValue + (startX - flooredWidth);
      }
      else {

        if (leftBoundTemp != startX) {
          currentSolidEntry->leftBound = leftBoundTemp2;
          bufferWrapper = this->ptrWrapper;
          if (bufferWrapper->entryIndex == 0x10000) {
            if (bufferWrapper->writeBlock->nextBlock == nullptr) {
              newBlockCandidate = new RenderNodeBlock;
              newBlockCandidate->nextBlock = nullptr;
              bufferWrapper->writeBlock->nextBlock = newBlockCandidate;
            }
            writeBlockCandidate = bufferWrapper->writeBlock->nextBlock;
            bufferWrapper->entryIndex = 0;
            bufferWrapper->writeBlock = writeBlockCandidate;
          }
          rightBoundaryEntry = bufferWrapper->writeBlock->entries + bufferWrapper->entryIndex;
          bufferWrapper->entryIndex = bufferWrapper->entryIndex + 1;
          currentSolidEntry->next = rightBoundaryEntry;
          currentSolidEntry = rightBoundaryEntry;
        }

        currentSolidEntry->rightBound = leftBoundTemp2;
        currentSolidEntry->leftBound = rightBoundCandidate;
        currentSolidEntry->layerIndex = layerIndexAsU16_2;
        currentSolidEntry->pixelTable = runningValue + (startX - flooredWidth);

        if (solidHead->leftBound == endX) {
          currentSolidEntry->next = solidHead->next;
        }
        else {
          currentSolidEntry->next = solidHead;
          leftBoundTemp = solidHead->rightBound;
          solidHead->rightBound = rightBoundCandidate;
          solidHead->pixelTable = solidHead->pixelTable + (endX - leftBoundTemp);
        }
      }
    } while (endX < cappedWidth);
  }
}
