#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/SceneClassCamera.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void SceneClassCamera::DrawSprite(int32_t screenX, int32_t screenY, ImageVectorWithHeader* sprite, int32_t layerIndex) {
  GameWindowRightSide->RenderClippedSprite(screenX - this->cameraCoordX, screenY - this->cameraCoordY, sprite, layerIndex);
}
