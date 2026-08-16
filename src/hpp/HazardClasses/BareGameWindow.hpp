#ifndef HAZARD_BAREGAMEWINDOW_HPP
#define HAZARD_BAREGAMEWINDOW_HPP

#include "HazardTypedef.hpp"

struct ImageVectorWithHeader;

class BareGameWindow {

public:
  BareGameWindow() {}

  virtual ~BareGameWindow() {};

  virtual void PrepareRenderArrays() {};

  virtual void Nothing0() {};

  virtual void RenderClippedRectangle(int32_t, int32_t, int16_t*, int16_t, int16_t, int32_t) {};

  virtual void RenderClippedSprite(int32_t, int32_t, ImageVectorWithHeader*, int32_t) {};

  virtual void RenderWithDirectDrawSurface() {};
};

#endif
