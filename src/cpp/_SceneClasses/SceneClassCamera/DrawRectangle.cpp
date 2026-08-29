#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/SceneClassCamera.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardGlobals.hpp"

void SceneClassCamera::DrawRectangle(int32_t startX, int32_t startY, int16_t* dataBuffer, int32_t width, int32_t height, int32_t layer) {
  GameWindowRightSide->RenderClippedRectangle(startX - this->cameraCoordX, startY - this->cameraCoordY, dataBuffer, width, height, layer);
}
