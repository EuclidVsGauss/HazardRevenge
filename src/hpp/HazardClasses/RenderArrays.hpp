#ifndef HAZARD_RENDERARRAYS_HPP
#define HAZARD_RENDERARRAYS_HPP

#include "HazardStructs/RenderBufferWrapper.hpp"
#include "HazardStructs/RenderNodeBlock.hpp"
#include "HazardTypedef.hpp"

struct RenderBufferWrapper;
struct RenderListEntry;
struct RenderNodeBlock;

class RenderArrays {
public:
  RenderArrays(int32_t windowWidth, int32_t windowHeight) {
    RenderNodeBlock* struct1MB_a;
    RenderNodeBlock* struct1MB_b;

    struct1MB_a = new RenderNodeBlock();
    struct1MB_a->nextBlock = (RenderNodeBlock*)nullptr;
    this->wrapper1.currentBlock = struct1MB_a;
    this->wrapper1.entryIndex = 0;
    struct1MB_b = new RenderNodeBlock();
    struct1MB_b->nextBlock = (RenderNodeBlock*)nullptr;
    this->wrapper2.currentBlock = struct1MB_b;
    this->wrapper2.entryIndex = 0;

    this->InitializeRenderingArrays(windowWidth, windowHeight);
  };

  virtual ~RenderArrays();
  void InitializeRenderingArrays(int32_t, int32_t);
  void PrepareNextRenderBuffer();

  RenderListEntry* (*arrayHeight1_solids_copyFrom)[480];
  RenderListEntry* (*arrayHeight2_shadows_copyFrom)[480];
  RenderListEntry* (*arrayHeight1_copyTo)[480];
  RenderListEntry* (*arrayHeight2_copyTo)[480];
  int32_t windowWidth;
  int32_t windowHeight;
  RenderBufferWrapper* ptrWrapper;
  RenderBufferWrapper wrapper1;
  RenderBufferWrapper wrapper2;
};

#endif
