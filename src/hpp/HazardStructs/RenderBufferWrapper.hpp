#ifndef HAZARD_LINKEDWRAPPER_HPP
#define HAZARD_LINKEDWRAPPER_HPP

#include "HazardTypedef.hpp"

struct RenderNodeBlock;

struct RenderBufferWrapper {
  RenderNodeBlock* currentBlock;
  RenderNodeBlock* writeBlock;
  int32_t entryIndex;
};
typedef struct RenderBufferWrapper RenderBufferWrapper, *PRenderBufferWrapper;

#endif
