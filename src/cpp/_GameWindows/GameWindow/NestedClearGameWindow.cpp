#include "HazardClasses/RenderArrays.hpp"
#include "HazardStructs/RenderBufferWrapper.hpp"
#include "HazardStructs/RenderNodeBlock.hpp"

RenderArrays::~RenderArrays() {
  RenderNodeBlock* currentChunk;

  delete[] (this->arrayHeight1_solids_copyFrom);
  delete[] (this->arrayHeight2_shadows_copyFrom);
  delete[] (this->arrayHeight1_copyTo);
  delete[] (this->arrayHeight2_copyTo);
  currentChunk = (this->wrapper2).currentBlock;
  while (currentChunk != nullptr) {
    (this->wrapper2).writeBlock = currentChunk;
    (this->wrapper2).currentBlock = currentChunk->nextBlock;

    delete (this->wrapper2).writeBlock;
    currentChunk = (this->wrapper2).currentBlock;
  }
  currentChunk = (this->wrapper1).currentBlock;
  while (currentChunk != nullptr) {
    (this->wrapper1).writeBlock = currentChunk;
    (this->wrapper1).currentBlock = currentChunk->nextBlock;

    delete currentChunk;
    currentChunk = (this->wrapper1).currentBlock;
  }
}
