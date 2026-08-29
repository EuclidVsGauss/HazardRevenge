#ifndef HAZARD_SCENECLASSCAMERABASE_HPP
#define HAZARD_SCENECLASSCAMERABASE_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

struct ImageVectorWithHeader;

class SceneClassCameraBase : public GameWindowBase {

public:
  virtual ~SceneClassCameraBase() {}

  virtual void primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) override;

  virtual void DrawRectangle(int32_t, int32_t, int16_t*, int32_t, int32_t, int32_t) {}

  virtual void DrawSprite(int32_t, int32_t, ImageVectorWithHeader*, int32_t) {}

  int32_t cameraCoordX;
  int32_t cameraCoordY;
  int32_t cameraOffsetX;
  int32_t cameraOffsetY;
  byte status;
  byte unused[3];
};

#endif
