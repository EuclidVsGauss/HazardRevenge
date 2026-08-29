#ifndef HAZARD_RENDERARRAYS_HPP
#define HAZARD_RENDERARRAYS_HPP

#include "HazardStructs/RenderBufferWrapper.hpp"
#include "HazardStructs/RenderNodeBlock.hpp"
#include "HazardTypedef.hpp"

struct RenderBufferWrapper;
struct RenderListEntry;
struct RenderNodeBlock;
struct ImageVectorWithHeader;

class RenderArrays {
public:
  RenderArrays() {};

  virtual ~RenderArrays();
  void InitializeRenderingArrays(int32_t, int32_t);
  void PrepareNextRenderBuffer();
  void ManageRenderLayers(int32_t runningHeight, int32_t flooredWidth, int32_t cappedWidth, int16_t* runningValue, int32_t layerIndex);
  __forceinline void ClippedRectangleImpl(int32_t startX, int32_t startY, int16_t* dataBuffer, int16_t width, int16_t height, int32_t layer);
  __forceinline void ClippedSpriteImpl(int32_t screenX, int32_t screenY, ImageVectorWithHeader* sprite, int32_t layerIndex);

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
