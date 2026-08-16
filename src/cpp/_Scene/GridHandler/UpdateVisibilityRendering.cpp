#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GridHandler.hpp"
#include "HazardGlobals.hpp"

void GridHandler::UpdateVisibilityRendering(uint32_t positionX, uint32_t positionY, SceneClassCameraBase* camera, int32_t mode) {
  byte currentTile;
  int32_t relativeX;
  int32_t runLength;
  SceneClassCameraBase* cameraBase;
  uint32_t cameraY;
  uint32_t cameraBaseY;
  byte* scanPtrA;
  byte* scanPtrB;
  uint32_t tileX;
  uint32_t tileY;

  if (mode != 0) {
    cameraBaseY = positionX & 0xfffffff0;
    tileX = camera->cameraCoordY & 0xfffffff0;
    tileY = camera->cameraCoordX & 0xfffffff0;
    if ((int32_t)tileX < (int32_t)(camera->cameraCoordY + 0x1e0)) {
      do {
        relativeX = tileX - (positionY & 0xfffffff0);
        if ((relativeX < -0x10) || (0x2f < relativeX)) {
          cameraBase = camera;
          cameraY = tileY;
        }
        else {
          if ((int32_t)tileY < (int32_t)(cameraBaseY - 0x10)) {
            camera->DrawRectangle(tileY, tileX, CameraCanvas, (cameraBaseY - tileY) + -0x10, 0x10, DrawLayer::Layer0xFFFF000B);
          }
          cameraBase = camera;
          cameraY = cameraBaseY + 0x30;
        }
        cameraBase->DrawRectangle(cameraY, tileX, CameraCanvas, 0x20f, 0x10, DrawLayer::Layer0xFFFF000B);
        tileX = tileX + 0x10;
      } while ((int32_t)tileX < camera->cameraCoordY + 0x1e0);
      return;
    }
  }
  else {
    tileY = camera->cameraCoordX;
    tileX = camera->cameraCoordY & 0xffffffe0;
    if ((int32_t)tileX < (camera->cameraCoordY + 0x1e0)) {
      do {

        scanPtrA = this->PaddedGridMap_Visibility[tileX >> 5] + (tileY >> 5);
        runLength = 0;
        do {
          if (*scanPtrA == '\0') {
            currentTile = scanPtrA[1];
            relativeX = 0x20;
            scanPtrB = scanPtrA;
            while (true) {
              scanPtrA = scanPtrB + 1;
              runLength = runLength + 0x20;
              if ((currentTile != '\0') || (0x20f < runLength)) {
                break;
              }
              currentTile = scanPtrB[2];
              relativeX = relativeX + 0x20;
              scanPtrB = scanPtrA;
            }
            camera->DrawRectangle((runLength - relativeX) + (tileY & 0xffffffe0), tileX, CameraCanvas, relativeX, 0x20, DrawLayer::Layer0xFFFF000B);
          }
          else {
            currentTile = scanPtrA[1];
            scanPtrB = scanPtrA;
            for (runLength = runLength + 0x10; (scanPtrA = scanPtrB + 1, currentTile != '\0' && (runLength < 0x210)); runLength = runLength + 0x20) {
              currentTile = scanPtrB[2];
              scanPtrB = scanPtrA;
            }
          }
        } while (runLength < 0x1f0);
        tileX = tileX + 0x20;
      } while ((int32_t)tileX < camera->cameraCoordY + 0x1e0);
    }
  }
}
