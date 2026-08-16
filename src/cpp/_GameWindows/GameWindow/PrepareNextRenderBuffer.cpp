#include "HazardClasses/RenderArrays.hpp"
#include "HazardExterns/GameWindow.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/RenderBufferWrapper.hpp"
#include "HazardStructs/RenderListEntry.hpp"
#include "HazardStructs/RenderNodeBlock.hpp"
#include "HazardStructs/Size2D.hpp"

void RenderArrays::PrepareNextRenderBuffer() {
  RenderNodeBlock* newLargeBlock;
  RenderBufferWrapper* newWrapper;
  RenderNodeBlock* allocatedBlock;
  int32_t heightIndex;
  Size2D screenDimensions = {0, 0};
  int16_t zeroSize;
  RenderListEntry* currentWidthList;
  RenderBufferWrapper* wrapper;

  screenDimensions.defaultRightBound = (int16_t)this->windowWidth;
  heightIndex = 0;
  zeroSize = 0;
  if (0 < this->windowHeight) {
    do {
      (*this->arrayHeight1_copyTo)[heightIndex] = (*this->arrayHeight1_solids_copyFrom)[heightIndex];
      (*this->arrayHeight2_copyTo)[heightIndex] = (*this->arrayHeight2_shadows_copyFrom)[heightIndex];
      heightIndex = heightIndex + 1;
    } while (heightIndex < this->windowHeight);
  }
  newWrapper = &this->wrapper1;
  if (this->ptrWrapper == newWrapper) {
    newWrapper = &this->wrapper2;
  }
  this->ptrWrapper = newWrapper;
  newWrapper->writeBlock = newWrapper->currentBlock;
  newWrapper->entryIndex = 0;
  heightIndex = 0;
  if (0 < this->windowHeight) {
    do {
      wrapper = this->ptrWrapper;
      if (wrapper->entryIndex == 0x10000) {
        if (wrapper->writeBlock->nextBlock == nullptr) {
          allocatedBlock = new RenderNodeBlock;
          allocatedBlock->nextBlock = nullptr;
          wrapper->writeBlock->nextBlock = allocatedBlock;
        }
        newLargeBlock = wrapper->writeBlock->nextBlock;
        wrapper->entryIndex = 0;
        wrapper->writeBlock = newLargeBlock;
      }
      (*this->arrayHeight1_solids_copyFrom)[heightIndex] = (wrapper->writeBlock->entries + wrapper->entryIndex);
      wrapper->entryIndex = wrapper->entryIndex + 1;
      (*this->arrayHeight2_shadows_copyFrom)[heightIndex] = nullptr;
      currentWidthList = (*this->arrayHeight1_solids_copyFrom)[heightIndex];
      currentWidthList->rightBound = screenDimensions.defaultLeftBound;
      currentWidthList->leftBound = screenDimensions.defaultRightBound;
      currentWidthList->pixelTable = (int16_t*)&GlobalStructColors2048;
      heightIndex = heightIndex + 1;
      currentWidthList->layerIndex = zeroSize;
      currentWidthList->next = nullptr;
    } while (heightIndex < this->windowHeight);
  }
}
