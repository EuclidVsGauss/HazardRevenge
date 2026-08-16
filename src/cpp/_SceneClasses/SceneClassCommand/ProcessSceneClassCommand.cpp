#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneClassCommand.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/CursorSprite.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardEnums/MapType.hpp"
#include "HazardExterns/SceneClassCommand.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/ObjectWrapper.hpp"

const int32_t ScreenScroll_LowerBoundary_4 = 4;
const int32_t ScreenScroll_UpperBoundaryX_636 = 636;
const int32_t ScreenScroll_UpperBoundaryY_476 = 476;
const int32_t Sidebar_Width_145 = 145;

__forceinline void SceneClassCommand::Case_0x7d11(intptr_t param_2) {
  this->mainSceneHandler = (SceneHandler*)param_2;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)this, 0x1);
  this->mainSceneHandler->primarySwitchSingleParam_0x7d29(1, this);
}

__forceinline void SceneClassCommand::DrawSelectionRectangle_0x7d3b() {
  if (this->flag != 1) {
    return;
  }
  int32_t currentDragCoordX = this->currentDragCoordX;
  int32_t initialDragCoordX = this->initialDragCoordX;
  int32_t lowerCoordX = __InlineMinimum(initialDragCoordX, currentDragCoordX);
  int32_t upperCoordX = __InlineMaximum(initialDragCoordX, currentDragCoordX);

  int32_t currentDragCoordY = this->currentDragCoordY;
  int32_t initialDragCoordY = this->initialDragCoordY;
  int32_t lowerCoordY = __InlineMinimum(initialDragCoordY, currentDragCoordY);
  int32_t upperCoordY = __InlineMaximum(initialDragCoordY, currentDragCoordY);

  int32_t horizontalLineWidth = (upperCoordX - lowerCoordX) + 4;
  int32_t length1 = __InlineMinimum(horizontalLineWidth, 640);
  this->mainSceneHandler->sceneCamera->DrawRectangle(lowerCoordX, lowerCoordY, CursorSpriteRelated, length1, 3, DrawLayer::Layer0xFFFF0005);
  int32_t length2 = __InlineMinimum(horizontalLineWidth, 640);
  this->mainSceneHandler->sceneCamera->DrawRectangle(lowerCoordX, upperCoordY, CursorSpriteRelated, length2, 3, DrawLayer::Layer0xFFFF0005);

  int32_t verticalLineHeight = (upperCoordY - lowerCoordY) + 4;
  int32_t height1 = __InlineMinimum(verticalLineHeight, 640);
  this->mainSceneHandler->sceneCamera->DrawRectangle(lowerCoordX, lowerCoordY, CursorSpriteRelated, 3, height1, DrawLayer::Layer0xFFFF0005);
  int32_t height2 = __InlineMinimum(verticalLineHeight, 640);
  this->mainSceneHandler->sceneCamera->DrawRectangle(upperCoordX, lowerCoordY, CursorSpriteRelated, 3, height2, DrawLayer::Layer0xFFFF0005);
}

__forceinline void SceneClassCommand::Case_0x7d0e(intptr_t param_2) {
  ActiveCharacter** ppActiveChar;
  int16_t collisionMapValue;
  SceneClassCameraBase* pCamera;
  SceneHandler* pSceneHandler;
  GameWindowBase** ppGameWindow;
  int32_t loopCounterY;
  int32_t cappedCoordX;
  int32_t scrollY;
  int32_t cappedCoordY;
  int32_t adjustedCoordX;
  int16_t** pCollisionGrid;
  int16_t* pCollisionRow;
  uint32_t mouseClickState;
  uint32_t clampedXMin;
  int32_t finalCappedCoordY;
  int32_t collisionIndex;
  int16_t* pCollisionRowTemp;
  GameWindowBase* pGameWindow;
  ObjectWrapper* paObjectWrapper;
  int32_t loopShiftedOffset;
  int32_t scrollX;
  ActiveCharacter** ppActiveCharIter;
  CursorSpriteEnum gridRow;
  int32_t objectIndex;
  GameWindowBase* pSceneObject;
  int32_t directionIndex;
  int32_t reducedCoordY;
  int32_t gridRowParam;
  int32_t coordinatePair[2];
  int32_t adjustedCoordY;

  int32_t param2AsInt = param_2;

  pCamera = this->mainSceneHandler->sceneCamera;
  if (pCamera != nullptr) {
    if (InputStates128[72] != '\0') {
      scrollX = -10;
    }
    else {
      scrollX = InputStates128[80] ? 10 : 0;
    }
    if (InputStates128[75] != '\0') {
      scrollY = -10;
    }
    else {
      scrollY = InputStates128[77] ? 10 : 0;
    }
    pCamera->primarySwitchSingleParam_0x7d00(scrollY, scrollX);
    if (CursorYCoord < ScreenScroll_LowerBoundary_4) {
      scrollX = -10;
    }
    else {
      scrollX = (((CursorYCoord < ScreenScroll_UpperBoundaryY_476) - 1) & 10);
    }
    if (CursorXCoord < ScreenScroll_LowerBoundary_4) {
      scrollY = -10;
    }
    else {
      scrollY = (((CursorXCoord < ScreenScroll_UpperBoundaryX_636) - 1) & 10);
    }
    this->mainSceneHandler->sceneCamera->primarySwitchSingleParam_0x7d00(scrollY, scrollX);
  }

  if (((InputStates128[57] != '\0') && (pSceneHandler = this->mainSceneHandler, pSceneHandler->mapType != MapType::World)) && (pSceneHandler->primarySwitchSingleParam(0x7d1a, (intptr_t)(GameWindowBase*)nullptr, 0x0), TeamCharacterList[0] != nullptr)) {
    ppActiveCharIter = TeamCharacterList;
    do {
      pSceneHandler = this->mainSceneHandler;
      if ((*ppActiveCharIter)->shiftedSceneClassUser0x48->mainSceneHandler == pSceneHandler) {
        pSceneHandler->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((GameWindowBase*)(*ppActiveCharIter)->shiftedSceneClassUser0x48, 0x0);
      }
      ppActiveChar = ppActiveCharIter + 1;
      ppActiveCharIter = ppActiveCharIter + 1;
    } while (*ppActiveChar != nullptr);
  }

  if (((InputStates128[60] & 17) == 1) && ((InputStates128[59] & 17) == 16)) {
    WrapperMessageBoxA(this->mainSceneHandler->sceneName, s_MAPNAME);
  }
  if (param2AsInt == 0x0) {
    this->flag = 2;
    this->initMinus1 = -1;
    return;
  }
  pSceneHandler = this->mainSceneHandler;
  pCamera = pSceneHandler->sceneCamera;
  int32_t mapWidthMinusBoundary = pSceneHandler->mapWidth + -0x10;
  cappedCoordX = pCamera->cameraCoordX + ((((int32_t)(CursorXCoord - (uint32_t)Sidebar_Width_145) < 1) - 1) & (CursorXCoord - Sidebar_Width_145));
  if (mapWidthMinusBoundary < cappedCoordX) {
    cappedCoordX = mapWidthMinusBoundary;
  }

  int32_t mapHeightMinusBoundary = pSceneHandler->mapHeight + -0x10;
  cappedCoordY = pCamera->cameraCoordY + CursorYCoord;
  if (mapHeightMinusBoundary < cappedCoordY) {
    cappedCoordY = mapHeightMinusBoundary;
  }
  adjustedCoordX = cappedCoordX + (cappedCoordX >> 0x1f & 0xfU);
  adjustedCoordY = cappedCoordY + (cappedCoordY >> 0x1f & 0xfU);
  int32_t reducedCoordX = adjustedCoordX >> 4;
  reducedCoordY = adjustedCoordY >> 4;

  if ((pSceneHandler->isViewportEnabled == 0) || (pSceneHandler->PaddedGridMap_Visibility[adjustedCoordY >> 5][adjustedCoordX >> 5] != 0)) {
    pCollisionGrid = pSceneHandler->PaddedGridMap_Collision;
    pCollisionRowTemp = pCollisionGrid[reducedCoordY];
    collisionMapValue = pCollisionRowTemp[reducedCoordX];
    objectIndex = (int32_t)collisionMapValue;
    if (objectIndex >= 0) {
    label_process_scene_object:
      pSceneObject = ObjectList[objectIndex].sceneClassObjectPointer;
      if (pSceneObject != nullptr) {
        gridRow = reducedCoordY;
        switch (ObjectList[objectIndex].scriptUserFlags & 0x70) {
        case 0:
          gridRow = CursorSprite::Attack;
          break;
        case 0x10:
          gridRow = CursorSprite::Select;
          break;
        case 0x20:
          gridRow = CursorSprite::GetTalk;
          break;
        case 0x30:
          pSceneObject->mainSceneHandler->primarySwitchSingleParam(0x7d3e, 0, 0);
          gridRow = CursorSprite::OpenPickup;
          break;
        case 0x40:
          gridRow = CursorSprite::Talk_unconfirmed;
          break;
        case 0x50:
          gridRow = CursorSprite::Warp;
        }
        goto label_set_cursor_sprite;
      }
    }
    else {

      objectIndex = __InlineHasUnoccupiedTileExcludingTypeInRectangularRegion(pSceneHandler, reducedCoordX, (cappedCoordY + 8 + ((cappedCoordY + 8) >> 0x1f & 0xfU)) >> 4, 1, 2, -1);
      if (objectIndex > -1) {
        goto label_process_scene_object;
      }

      objectIndex = __InlineHasUnoccupiedTileExcludingTypeInRectangularRegion(pSceneHandler, (int32_t)(cappedCoordX + -8 + ((cappedCoordX + -8) >> 0x1f & 0xfU)) >> 4, reducedCoordY, 1, 1, -1);
      if (objectIndex > -1) {
        goto label_process_scene_object;
      }

      objectIndex = __InlineHasUnoccupiedTileExcludingTypeInRectangularRegion(pSceneHandler, reducedCoordX, reducedCoordY, 1, 1, -1);
      if (objectIndex > -1) {
        goto label_process_scene_object;
      }

      objectIndex = 0xffffffff;
    }
    if (collisionMapValue == -2) {
      for (directionIndex = 0; directionIndex < 4; directionIndex = directionIndex + 1) {
        for (loopShiftedOffset = 0; loopShiftedOffset < 4; loopShiftedOffset = loopShiftedOffset + 1) {
          if (pCollisionGrid[(loopShiftedOffset >> 1) + (int32_t)DirectionalLookupTable[(2 * directionIndex) + 1] + reducedCoordY][(loopShiftedOffset & 1) + (int32_t)DirectionalLookupTable[2 * directionIndex] + reducedCoordX] != -2) {
            break;
          }
        }
        if (loopShiftedOffset == 4) {
          reducedCoordX = reducedCoordX + DirectionalLookupTable[directionIndex * 2];
          reducedCoordY = reducedCoordY + DirectionalLookupTable[(directionIndex * 2) + 1];
          break;
        }
      }
      gridRow = (3 < directionIndex) + 1;
    }
    else {
      gridRow = 2;
    }
  }
  else {
    gridRow = 7;
    objectIndex = reducedCoordY;
  }
label_set_cursor_sprite:

  this->mainSceneHandler->primarySwitchSingleParam_0x7d17(gridRow, 0x0);
  mouseClickState = MouseButtonClick & 0x11;
  if (mouseClickState == 1) {
    this->initialDragCoordX = cappedCoordX;
    this->initialDragCoordY = cappedCoordY;
    goto label_reset_drag_flag;
  }
  if (mouseClickState != 0x10) {
    if (mouseClickState != 0x11) {
      goto label_process_right_click;
    }
    if (this->flag == 0) {
      adjustedCoordX = this->initialDragCoordX - cappedCoordX;
      if (adjustedCoordX < 0) {
        adjustedCoordX = -adjustedCoordX;
      }
      if (adjustedCoordX < 0x20) {
        adjustedCoordX = this->initialDragCoordY - cappedCoordY;
        if (adjustedCoordX < 0) {
          adjustedCoordX = -adjustedCoordX;
        }
        if (adjustedCoordX < 0x20) {
          goto label_update_drag_selection;
        }
      }
      this->flag = 1;
    }
  label_update_drag_selection:
    if (this->flag == 1) {

      this->mainSceneHandler->primarySwitchSingleParam_0x7d17(5, 0x0);
      this->currentDragCoordX = cappedCoordX;
      this->currentDragCoordY = cappedCoordY;
    }
    goto label_process_right_click;
  }
  if (this->flag != 0) {
    goto label_clamp_drag_coordinates;
  }

  switch (gridRow) {
  case 1:
    pGameWindow = *this->mainSceneHandler->selectedUnits32;
    if (pGameWindow != nullptr) {
      cappedCoordX = 0;
      do {
        pGameWindow->primarySwitchSingleParam((-(uint32_t)(InputStates128[29] != '\0') & 0x40) + 0x7d00, reducedCoordX, reducedCoordY);
        cappedCoordX = cappedCoordX + 1;
        pGameWindow = *(this->mainSceneHandler->selectedUnits32 + cappedCoordX);
      } while (pGameWindow != nullptr);
    }
    break;
  case 3:
    this->mainSceneHandler->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((GameWindowBase*)nullptr, 0x0);
    pSceneObject = ObjectList[objectIndex].sceneClassObjectPointer;
    this->mainSceneHandler->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a(pSceneObject, 0x0);
    break;
  case 10:
  case 0xb:
    pGameWindow = *this->mainSceneHandler->selectedUnits32;
    if (pGameWindow != nullptr) {
      cappedCoordX = 0;
      do {
        pGameWindow->primarySwitchSingleParam(0x7d04, objectIndex, 0x0);
        cappedCoordX = cappedCoordX + 1;
        pGameWindow = *(this->mainSceneHandler->selectedUnits32 + cappedCoordX);
      } while (pGameWindow != nullptr);
    }
    break;
  case 9:
    pGameWindow = *this->mainSceneHandler->selectedUnits32;
    if (pGameWindow != nullptr) {
      cappedCoordX = 0;
      do {
        pGameWindow->primarySwitchSingleParam(0x7d18, objectIndex, SCCommandRelated);
        cappedCoordX = cappedCoordX + 1;
        pGameWindow = *(this->mainSceneHandler->selectedUnits32 + cappedCoordX);
      } while (pGameWindow != nullptr);
    }
    SCCommandRelated = ((SCCommandRelated + 1) & 0xff);
    break;
  case 0xc:
    gridRowParam = reducedCoordX;
    coordinatePair[0] = gridRowParam;
    coordinatePair[1] = reducedCoordY;

    pGameWindow = *this->mainSceneHandler->selectedUnits32;
    if (pGameWindow != nullptr) {
      cappedCoordX = 0;
      do {

        pGameWindow->primarySwitchSingleParam_0x7d15(coordinatePair, objectIndex);
        cappedCoordX = cappedCoordX + 1;
        pGameWindow = *(this->mainSceneHandler->selectedUnits32 + cappedCoordX);
      } while (pGameWindow != nullptr);
    }
    break;
  case 4:
    pGameWindow = *this->mainSceneHandler->selectedUnits32;
    if (pGameWindow != nullptr) {
      cappedCoordX = 0;
      do {
        pGameWindow->primarySwitchSingleParam(0x7d02, objectIndex, 0x0);
        cappedCoordX = cappedCoordX + 1;
        pGameWindow = *(this->mainSceneHandler->selectedUnits32 + cappedCoordX);
      } while (pGameWindow != nullptr);
    }
    break;
  case 7:
    this->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x1b, nullptr);
    break;
  }
label_clamp_drag_coordinates:
  if (this->flag == 1) {
    int32_t currentDragCoordXcopy = this->currentDragCoordX;
    int32_t initialDragCoordXcopy = this->initialDragCoordX;
    int32_t minDragCoordX = currentDragCoordXcopy;
    if (initialDragCoordXcopy <= currentDragCoordXcopy) {
      minDragCoordX = initialDragCoordXcopy;
    }
    minDragCoordX = minDragCoordX & ((minDragCoordX < 1) - 1);
    cappedCoordX = (int32_t)(minDragCoordX + (minDragCoordX >> 0x1f & 0xfU)) >> 4;
    if (currentDragCoordXcopy <= initialDragCoordXcopy) {
      currentDragCoordXcopy = initialDragCoordXcopy;
    }
    pSceneHandler = this->mainSceneHandler;
    clampedXMin = pSceneHandler->mapWidth;
    if (currentDragCoordXcopy <= (int32_t)clampedXMin) {
      clampedXMin = currentDragCoordXcopy;
    }
    int32_t finalCappedCoordX = (int32_t)(clampedXMin + ((int32_t)clampedXMin >> 0x1f & 0xfU)) >> 4;

    int32_t currentDragCoordYcopy = this->currentDragCoordY;
    int32_t initialDragCoordYcopy = this->initialDragCoordY;
    int32_t minDragCoordY = currentDragCoordYcopy;
    if (initialDragCoordYcopy <= currentDragCoordYcopy) {
      minDragCoordY = initialDragCoordYcopy;
    }
    minDragCoordY = ((minDragCoordY < 1) - 1) & minDragCoordY;
    int32_t tmpY = (int32_t)(minDragCoordY + (minDragCoordY >> 0x1f & 0xfU)) >> 4;
    if (currentDragCoordYcopy <= initialDragCoordYcopy) {
      currentDragCoordYcopy = initialDragCoordYcopy;
    }
    minDragCoordY = pSceneHandler->mapHeight;
    if (currentDragCoordYcopy <= minDragCoordY) {
      minDragCoordY = currentDragCoordYcopy;
    }
    finalCappedCoordY = (int32_t)(minDragCoordY + (minDragCoordY >> 0x1f & 0xfU)) >> 4;

    directionIndex = 0;
    if (tmpY <= finalCappedCoordY) {
      for (adjustedCoordY = tmpY; adjustedCoordY <= finalCappedCoordY; adjustedCoordY++) {
        if (cappedCoordX <= finalCappedCoordX) {
          pCollisionRow = pSceneHandler->PaddedGridMap_Collision[adjustedCoordY] + cappedCoordX;
          for (loopCounterY = (finalCappedCoordX - cappedCoordX) + 1; loopCounterY != 0; loopCounterY = loopCounterY + -1) {
            collisionIndex = (int32_t)*pCollisionRow;
            if (
                ((-1 < collisionIndex) && ((*(byte*)&ObjectList[collisionIndex].scriptUserFlags & 0x80) != 0)) &&
                (ObjectList[collisionIndex].sceneClassObjectPointer != nullptr)) {
              directionIndex = directionIndex + 1;
            }
            pCollisionRow = pCollisionRow + 1;
          }
        }
      }
      if (directionIndex != 0) {
        pSceneHandler->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((GameWindowBase*)nullptr, 0x0);
        adjustedCoordY = cappedCoordX;
        paObjectWrapper = ObjectList;
        do {
          for (; adjustedCoordY <= finalCappedCoordX; adjustedCoordY = adjustedCoordY + 1) {
            pSceneHandler = this->mainSceneHandler;
            loopCounterY = (int32_t)pSceneHandler->PaddedGridMap_Collision[tmpY][adjustedCoordY];

            if (((-1 < loopCounterY) && ((*(byte*)&paObjectWrapper[loopCounterY].scriptUserFlags & 0x80) != 0)) && (pSceneObject = paObjectWrapper[loopCounterY].sceneClassObjectPointer, pSceneObject != nullptr)) {
              pSceneHandler->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a(pSceneObject, 0x0);
              paObjectWrapper = ObjectList;
            }
          }
          tmpY = tmpY + 1;
          adjustedCoordY = cappedCoordX;
        } while (tmpY <= finalCappedCoordY);
      }
    }
  }
label_reset_drag_flag:
  this->flag = 0;

label_process_right_click:
  mouseClickState = MouseButtonClick & 0x22;
  switch (mouseClickState) {
  case 0x22: {
    ppGameWindow = this->mainSceneHandler->selectedUnits32;
    pGameWindow = *ppGameWindow;
    if ((pGameWindow != nullptr) && (ppGameWindow[1] == nullptr)) {
      pGameWindow->primarySwitchSingleParam(0x7d3f, (reducedCoordX + 2), reducedCoordY);
      return;
    }
  } break;
  case 0x20: {
    ppGameWindow = this->mainSceneHandler->selectedUnits32;
    pGameWindow = *ppGameWindow;
    if ((pGameWindow != nullptr) && (ppGameWindow[1] == nullptr)) {
      pGameWindow->primarySwitchSingleParam(0x7d3f, 0x1, 0x0);
      return;
    }
  } break;
  case 0x2: {
    ppGameWindow = this->mainSceneHandler->selectedUnits32;
    pGameWindow = *ppGameWindow;
    if ((pGameWindow != nullptr) && (ppGameWindow[1] == nullptr)) {
      pGameWindow->primarySwitchSingleParam(0x7d3f, 0x0, 0x0);
    }
  }
  }
}

void SceneClassCommand::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {
  (void)param_3;

  switch (switchParam) {
  case 0x7d11:
    Case_0x7d11(param_2);
    return;

  case 0x7d3b:
    DrawSelectionRectangle_0x7d3b();
    return;

  case 0x7d0e:
    Case_0x7d0e(param_2);
    return;
  }
}
