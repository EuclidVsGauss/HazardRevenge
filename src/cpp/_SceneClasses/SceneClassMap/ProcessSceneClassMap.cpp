#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneClassMap.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/Tilemap.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/TileColorMaps.hpp"
#include "HazardStructs/TmpBackgroundSpriteInstance.hpp"
#include "HazardStructs/TmpObjectHuge.hpp"

__forceinline void SceneClassMap::Case_0x7d11(intptr_t param_2) {
  this->mainSceneHandler = (SceneHandler*)param_2;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)this, 0x1);
}

__forceinline void SceneClassMap::Case_0x7d3b() {
  Tilemap* currentTilemap;
  SceneClassCameraBase* currentCamera;
  int32_t cameraCoord1;
  TmpBackgroundSpriteInstance* currentSprite;
  int32_t cameraCoord2;
  uint32_t scrollRightOffset;
  int32_t cameraCoord1Shifted;
  uint32_t loopVariableForY;
  int32_t cameraCoord2Shifted;
  int32_t currentRowIndex;
  uint32_t cacheOffsetForScrollUpDown;
  int32_t tileCountAlongY;

  currentTilemap = &this->tileLayout;
  currentCamera = this->mainSceneHandler->sceneCamera;

  cameraCoord2 = currentCamera->cameraCoordY;
  cameraCoord1 = currentCamera->cameraCoordX;
  cameraCoord2Shifted = cameraCoord2 >> 4;
  cameraCoord1Shifted = cameraCoord1 >> 4;
  this->tileLayout.tileCacheIndex = (cameraCoord2 * 0x200) + -0x200 + cameraCoord1;

  currentRowIndex = this->tileLayout.currentRowIndex;
  cameraCoord2 = (cameraCoord1Shifted - (this->tileLayout).visibleWidthTiles) + -1;
  if (cameraCoord2 < currentRowIndex) {
    cameraCoord2 = currentRowIndex;
  }
  this->tileLayout.currentRowIndex = cameraCoord2;

  while (cameraCoord2 < cameraCoord1Shifted) {
    currentRowIndex = (this->tileLayout).currentColumnIndex;
    cameraCoord2 = (this->tileLayout).visibleWidthTiles + (this->tileLayout).currentRowIndex;
    tileCountAlongY = (this->tileLayout).visibleHeightTiles;
    cacheOffsetForScrollUpDown = ((currentRowIndex * 0x200) + cameraCoord2) * 0x10;
    if (0 < tileCountAlongY) {

      do {
        currentTilemap->ScrollRight(cacheOffsetForScrollUpDown & 0x3ffff, (uint8_t*)&this->tileLayout.uniqueTilesArray[this->tileLayout.tileMatrix[currentRowIndex][cameraCoord2]]);
        cacheOffsetForScrollUpDown = cacheOffsetForScrollUpDown + 0x2000;
        tileCountAlongY = tileCountAlongY - 1;
        currentRowIndex = currentRowIndex + 1;
      } while (tileCountAlongY != 0x0);
    }
    cameraCoord2 = (this->tileLayout).currentRowIndex + 1;
    (this->tileLayout).currentRowIndex = cameraCoord2;
  }

  currentRowIndex = (this->tileLayout).currentRowIndex;
  cameraCoord2 = (this->tileLayout).visibleWidthTiles + cameraCoord1Shifted;
  if (currentRowIndex < cameraCoord2) {
    cameraCoord2 = currentRowIndex;
  }
  (this->tileLayout).currentRowIndex = cameraCoord2;
  while (cameraCoord1Shifted < cameraCoord2) {
    currentTilemap->ScrollLeft((this->tileLayout).currentRowIndex + -1, (this->tileLayout).currentColumnIndex);
    cameraCoord2 = (this->tileLayout).currentRowIndex + -1;
    (this->tileLayout).currentRowIndex = cameraCoord2;
  }

  currentRowIndex = (this->tileLayout).currentColumnIndex;
  cameraCoord2 = (cameraCoord2Shifted - (this->tileLayout).visibleHeightTiles) + -1;
  if (cameraCoord2 < currentRowIndex) {
    cameraCoord2 = currentRowIndex;
  }
  (this->tileLayout).currentColumnIndex = cameraCoord2;
  while (cameraCoord2 < cameraCoord2Shifted) {
    currentTilemap->ScrollUpDown((this->tileLayout).currentRowIndex, (this->tileLayout).currentColumnIndex + (this->tileLayout).visibleHeightTiles);
    cameraCoord2 = (this->tileLayout).currentColumnIndex + 1;
    (this->tileLayout).currentColumnIndex = cameraCoord2;
  }

  currentRowIndex = (this->tileLayout).currentColumnIndex;
  cameraCoord2 = (this->tileLayout).visibleHeightTiles + cameraCoord2Shifted;
  if (currentRowIndex < cameraCoord2) {
    cameraCoord2 = currentRowIndex;
  }
  (this->tileLayout).currentColumnIndex = cameraCoord2;
  while (cameraCoord2Shifted < cameraCoord2) {
    currentTilemap->ScrollUpDown((this->tileLayout).currentRowIndex, (this->tileLayout).currentColumnIndex + -1);
    cameraCoord2 = (this->tileLayout).currentColumnIndex + -1;
    (this->tileLayout).currentColumnIndex = cameraCoord2;
  }

  cacheOffsetForScrollUpDown = 0;
  do {
    scrollRightOffset = (this->tileLayout).tileCacheIndex + 0x200;
    (this->tileLayout).tileCacheIndex = scrollRightOffset;
    GameWindowRightSide->RenderClippedRectangle(0, cacheOffsetForScrollUpDown, ((this->tileLayout).tileCacheData)->start + (scrollRightOffset & 0x3ffff), 0x1ef, 1, 0);
    cacheOffsetForScrollUpDown = cacheOffsetForScrollUpDown + 1;
  } while ((int32_t)cacheOffsetForScrollUpDown < 0x1e0);

  currentCamera = this->mainSceneHandler->sceneCamera;
  cameraCoord2 = currentCamera->cameraCoordX;
  currentRowIndex = currentCamera->cameraCoordY;
  scrollRightOffset = (((int32_t)(cameraCoord2 - 0x100) < 1) - 1) & (cameraCoord2 - 0x100);
  cacheOffsetForScrollUpDown = currentRowIndex - 0x100;
  cacheOffsetForScrollUpDown = (((int32_t)cacheOffsetForScrollUpDown < 1) - 1) & cacheOffsetForScrollUpDown;
  if ((int32_t)cacheOffsetForScrollUpDown <= currentRowIndex + 0x360) {
    do {
      if ((int32_t)scrollRightOffset <= cameraCoord2 + 0x36f) {
        loopVariableForY = scrollRightOffset;
        do {
          for (currentSprite = (this->locationOfBackgroundSprites[(int32_t)cacheOffsetForScrollUpDown >> 8][(int32_t)loopVariableForY >> 8]); currentSprite != nullptr; currentSprite = currentSprite->overlayedObject) {
            currentCamera = this->mainSceneHandler->sceneCamera;

            currentCamera->DrawSprite(currentSprite->coordX, currentSprite->coordY, currentSprite->backgroundSprites, currentSprite->overlayIndex);
            if (currentSprite->backgroundShadowSprites != nullptr) {
              currentCamera = this->mainSceneHandler->sceneCamera;
              currentCamera->DrawSprite(currentSprite->coordX, currentSprite->coordY, currentSprite->backgroundShadowSprites, -currentSprite->coordY);
            }
          }
          loopVariableForY = loopVariableForY + 0x100;
          cameraCoord2 = this->mainSceneHandler->sceneCamera->cameraCoordX;
        } while ((int32_t)loopVariableForY <= cameraCoord2 + 0x36f);
      }
      cacheOffsetForScrollUpDown = cacheOffsetForScrollUpDown + 0x100;
    } while ((int32_t)cacheOffsetForScrollUpDown <= this->mainSceneHandler->sceneCamera->cameraCoordY + 0x360);
    return;
  }
}

void SceneClassMap::primarySwitchSingleParam(int32_t param_1, intptr_t param_2, intptr_t param_3) {

  (void)param_3;

  switch (param_1) {
  case 0x7d11:
    Case_0x7d11(param_2);
    break;
  case 0x7d3b:
    Case_0x7d3b();
    break;
  }
}
