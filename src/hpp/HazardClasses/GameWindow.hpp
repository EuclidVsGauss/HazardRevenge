#ifndef HAZARD_GAMEWINDOW_HPP
#define HAZARD_GAMEWINDOW_HPP

#include "HazardClasses/BareGameWindow.hpp"
#include "HazardClasses/RenderArrays.hpp"
#include "HazardTypedef.hpp"

class BareGameWindow;
class RenderArrays;
struct ImageVectorWithHeader;

class GameWindow : public BareGameWindow, public RenderArrays {

public:
  GameWindow(int32_t, int32_t, int32_t, int32_t);
  virtual ~GameWindow();
  virtual void PrepareRenderArrays() override;

  virtual void Nothing0() override {}

  virtual void RenderClippedRectangle(int32_t startX, int32_t startY, int16_t* dataBuffer, int16_t width, int16_t height, int32_t layer) override;
  virtual void RenderClippedSprite(int32_t coord1, int32_t coord2, ImageVectorWithHeader* sprite, int32_t layerIndex) override;
  virtual void RenderWithDirectDrawSurface() override;

  void ManageRenderLayers(int32_t runningHeight, int32_t flooredWidth, int32_t cappedWidth, int16_t* runningValue, int32_t layerIndex);

  int32_t copyOrigin1;
  int32_t copyOrigin2;
  int32_t unused1;
  int32_t copyWindowWidth;
  int32_t copyWindowHeight;
  int32_t unused2;
};

#endif
