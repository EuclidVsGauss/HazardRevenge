#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneClassMoveTile.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

__forceinline void SceneClassMoveTile::Case_0x7d11(intptr_t param2) {
  this->mainSceneHandler = (SceneHandler*)param2;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)this, 0x0);
}

__forceinline void SceneClassMoveTile::Case_0x7d3b() {
  int32_t coordinateY;
  int32_t layerIndex;
  ImageVectorWithHeader* solidSprite;
  ImageVectorWithHeader* shadowSprite;

  coordinateY = this->moveTileCoord2 + 0x10;
  layerIndex = __InlineMinimum(coordinateY, 1);
  solidSprite = __InlineGetSolidSpriteFrameForAction(this->StandFrameObject, this->actObject, this->counter);
  this->mainSceneHandler->sceneCamera->DrawSprite(this->moveTileCoord1 + 0x10, coordinateY, solidSprite, layerIndex);

  shadowSprite = __InlineGetShadowSpriteFrameForAction(this->StandFrameObject, this->actObject, this->counter);
  this->mainSceneHandler->sceneCamera->DrawSprite(this->moveTileCoord1 + 0x10, this->moveTileCoord2 + 0x10, shadowSprite, -(moveTileCoord2 + 0x10));
}

__forceinline void SceneClassMoveTile::Case_0x7d3c() {
  SceneHandler* handlerPtr;
  int32_t loopX;
  int32_t sfxIndex;
  int32_t gridCoordsX;
  int32_t gridCoordsY;
  int32_t loopY;

  this->counter = this->counter + 1;
  switch (this->switchParameter) {
  case 0:
    if ((GameFlags[this->gameFlagPartialTrigger1] == 0) || (GameFlags[this->gameFlagPartialTrigger2] == 0)) {
      if (this->gameFlagFullTrigger == 0) {
        return;
      }
      if (GameFlags[this->gameFlagFullTrigger] == 0) {
        return;
      }
    }
    this->switchParameter = 1;
    sfxIndex = __InlineGetSoundEffectIndex(this->actObject);
    this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, sfxIndex, 0x0);
    break;
  case 1:
    gridCoordsX = this->coord1Related;
    if (this->moveTileCoord1 != gridCoordsX << 4) {
      this->moveTileCoord1 += (this->tmpCoord1 > this->coord1Related) ? 1 : -1;
    }
    gridCoordsY = this->coord2Related;
    if (this->moveTileCoord2 != gridCoordsY << 4) {
      this->moveTileCoord2 += (this->tmpCoord2 > this->coord2Related) ? 1 : -1;
    }
    if ((this->moveTileCoord1 == gridCoordsX << 4) && (this->moveTileCoord2 == gridCoordsY << 4)) {
      handlerPtr = this->mainSceneHandler;
      for (loopY = 0; loopY < 2; loopY++) {
        for (loopX = 0; loopX < 2; loopX = loopX + 1) {
          handlerPtr->PaddedGridMap_TileAttributes[gridCoordsY + loopY][gridCoordsX + loopX] = 0;
          handlerPtr->PaddedGridMap_Collision[gridCoordsY + loopY][gridCoordsX + loopX] = -2;
        }
      }

      handlerPtr = this->mainSceneHandler;
      gridCoordsY = this->coord2Related;
      gridCoordsX = this->coord1Related;
      for (loopY = 0; loopY < 2; loopY++) {
        for (loopX = 0; loopX < 2; loopX++) {
          handlerPtr->PaddedGridMap_LineOfSight[(loopY + gridCoordsY) >> 1][(loopX + gridCoordsX) >> 1] = 0;
        }
      }
      this->mainSceneHandler->primarySwitchSingleParam(0x7d26, 0x0, 0x0);
      this->switchParameter = 2;
    }
    this->UpdateObjectOnGrid(this->moveTileCoord1, this->moveTileCoord2);
    return;
  case 2:
    if ((GameFlags[this->gameFlagPartialTrigger1] != 0) && (GameFlags[this->gameFlagPartialTrigger2] != 0)) {
      return;
    }
    if (GameFlags[this->gameFlagFullTrigger] != (this->gameFlagFullTrigger == 0)) {
      return;
    }
    handlerPtr = this->mainSceneHandler;
    gridCoordsX = this->coord1Related;
    if (__InlineHasUnoccupiedTileExcludingTypeInRectangularRegion(handlerPtr, gridCoordsX, this->coord2Related, 2, 2, -1)) {
      return;
    }
    this->switchParameter = 3;

    gridCoordsY = this->coord2Related;
    for (loopY = 0; loopY < 2; loopY++) {
      for (loopX = 0; loopX < 2; loopX++) {
        handlerPtr->PaddedGridMap_TileAttributes[gridCoordsY + loopY][loopX + gridCoordsX] = 5;
        handlerPtr->PaddedGridMap_Collision[gridCoordsY + loopY][gridCoordsX + loopX] = -1;
      }
    }

    gridCoordsY = this->coord2Related;
    gridCoordsX = this->coord1Related;
    for (loopY = 0; loopY < 2; loopY = loopY + 1) {
      for (loopX = 0; loopX < 2; loopX = loopX + 1) {
        handlerPtr->PaddedGridMap_LineOfSight[(loopY + gridCoordsY) >> 1][(loopX + gridCoordsX) >> 1] = 1;
      }
    }
    this->mainSceneHandler->primarySwitchSingleParam(0x7d26, 0x0, 0x0);
    sfxIndex = __InlineGetSoundEffectIndex(this->actObject, 1);
    this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, sfxIndex, 0x0);
    break;

  case 3:
    gridCoordsX = this->tmpCoord1 << 4;
    if (this->moveTileCoord1 != gridCoordsX) {
      this->moveTileCoord1 += (this->tmpCoord1 < this->coord1Related) ? 1 : -1;
    }
    gridCoordsY = this->tmpCoord2 << 4;
    if (this->moveTileCoord2 != gridCoordsY) {
      this->moveTileCoord2 += (this->tmpCoord2 < this->coord2Related) ? 1 : -1;
    }
    if (this->moveTileCoord1 == gridCoordsX) {
      if (this->moveTileCoord2 == gridCoordsY) {
        this->switchParameter = 0;
        return;
      }
      return;
    }
    return;
  default:
    return;
  }
}

void SceneClassMoveTile::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param3) {
  (void)param3;

  switch (switchParam) {
  case 0x7d11:
    this->Case_0x7d11(param2);
    break;
  case 0x7d3b:
    this->Case_0x7d3b();
    break;
  case 0x7d3c:
    this->Case_0x7d3c();
    break;
  default:
    break;
  }
}
