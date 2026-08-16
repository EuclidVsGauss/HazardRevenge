#include "HazardClasses/SceneClassCamera.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardGlobals.hpp"

SceneClassCamera::SceneClassCamera(int32_t coord1, int32_t coord2) {

  (void)coord1;
  (void)coord2;

  this->cameraCoordY = 16;
  this->cameraCoordX = 16;
  this->cameraOffsetY = 16;
  this->cameraOffsetX = 16;
  this->status = 0;
}
