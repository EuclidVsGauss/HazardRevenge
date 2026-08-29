#ifndef HAZARD_LINKEDWRAPPER_HPP
#define HAZARD_LINKEDWRAPPER_HPP

#include "HazardStructs/RenderNodeBlock.hpp"
#include "HazardTypedef.hpp"

struct RenderBufferWrapper {
  RenderNodeBlock* currentBlock;
  RenderNodeBlock* writeBlock;
  int32_t entryIndex;

  RenderBufferWrapper() {
    RenderNodeBlock* newBlock;

    newBlock = new RenderNodeBlock();
    newBlock->nextBlock = (RenderNodeBlock*)nullptr;
    this->currentBlock = newBlock;
    this->entryIndex = 0;
  }

  ~RenderBufferWrapper() {
    RenderNodeBlock* currentChunk = this->currentBlock;
    while (currentChunk != nullptr) {
      this->writeBlock = currentChunk;
      this->currentBlock = currentChunk->nextBlock;

      delete this->writeBlock;
      currentChunk = this->currentBlock;
    }
  }
};
typedef struct RenderBufferWrapper RenderBufferWrapper, *PRenderBufferWrapper;

#endif
