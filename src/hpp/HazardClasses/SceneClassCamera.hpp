#ifndef HAZARD_SCENECLASSCAMERA_HPP
#define HAZARD_SCENECLASSCAMERA_HPP

#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardTypedef.hpp"

struct ImageVectorWithHeader;

class SceneClassCamera : public SceneClassCameraBase {

public:
  SceneClassCamera(int32_t, int32_t);
  virtual ~SceneClassCamera();
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;
  virtual void DrawRectangle(int32_t startX, int32_t startY, int16_t* dataBuffer, int32_t width, int32_t height, int32_t layer) override;
  virtual void DrawSprite(int32_t param_1, int32_t param_2, ImageVectorWithHeader* param_3, int32_t layerIndex) override;

private:
  __forceinline void Case_0x7d11(intptr_t param_2);
  __forceinline void Case_0x7d3c();
  __forceinline void Case_0x7d00(int32_t param2AsInt, int32_t param3AsInt);
  __forceinline void Case_0x7d21(int32_t param2AsInt, int32_t param3AsInt);
};

#endif
