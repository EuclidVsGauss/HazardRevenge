#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneClassItem.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ItemReferenceStruct.hpp"
#include "HazardStructs/ObjectWrapper.hpp"

__forceinline void SceneClassItem::Case_0x7d11(intptr_t param2) {
  int32_t rowIndex;
  int32_t randomHorizontalPosition;
  int32_t randomVerticalPosition;
  int32_t verticalIterator;
  int16_t* collisionValuePointer;
  int16_t** gridRowPointer;
  int16_t** alternateGridRowPointer;
  int32_t searchRadius;
  int32_t horizontalClampedPosition;
  int32_t retryCount;

  this->mainSceneHandler = (SceneHandler*)param2;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)this, 0x0);
  retryCount = 0;
  searchRadius = 0x4;

label_retry_item_placement:
  rowIndex = this->mainSceneHandler->mapWidth;
  randomHorizontalPosition = ((rowIndex + (rowIndex >> 0x1f & 0xfU)) >> 4) - 4;
  rowIndex = (searchRadius + (searchRadius >> 0x1f & 7U)) >> 3;
  horizontalClampedPosition = PseudoRng();
  horizontalClampedPosition = ((((horizontalClampedPosition % searchRadius) + (horizontalClampedPosition % searchRadius >> 0x1f & 3U)) >> 2) - rowIndex) + this->matrixIndexXTimes16;
  if (randomHorizontalPosition < horizontalClampedPosition) {
    horizontalClampedPosition = randomHorizontalPosition;
  }
  horizontalClampedPosition = ((horizontalClampedPosition < 1) - 1) & horizontalClampedPosition;
  verticalIterator = this->mainSceneHandler->mapHeight;
  randomVerticalPosition = ((verticalIterator + (verticalIterator >> 0x1f & 0xfU)) >> 4) - 4;
  randomHorizontalPosition = PseudoRng();
  randomHorizontalPosition = ((((randomHorizontalPosition % searchRadius) + (randomHorizontalPosition % searchRadius >> 0x1f & 3U)) >> 2) - rowIndex) + this->matrixIndexYTimes16;
  if (randomVerticalPosition < randomHorizontalPosition) {
    randomHorizontalPosition = randomVerticalPosition;
  }
  randomHorizontalPosition = randomHorizontalPosition & ((randomHorizontalPosition < 1) - 1);
  rowIndex = 0;
  alternateGridRowPointer = this->mainSceneHandler->PaddedGridMap_Collision + randomHorizontalPosition;
  gridRowPointer = alternateGridRowPointer;

  do {
    verticalIterator = 0;
    collisionValuePointer = (*gridRowPointer + horizontalClampedPosition);
    do {
      if (*collisionValuePointer == -1) {
        goto label_increase_search_radius;
      }
      verticalIterator = verticalIterator + 1;
      collisionValuePointer = collisionValuePointer + 1;
    } while (verticalIterator < 2);
    rowIndex = rowIndex + 1;
    gridRowPointer = gridRowPointer + 1;
  } while (rowIndex < 2);
  rowIndex = 0;

  do {
    verticalIterator = 0;
    collisionValuePointer = (*alternateGridRowPointer + horizontalClampedPosition);
    do {
      if (*collisionValuePointer > -1) {
        goto label_increase_search_radius;
      }
      verticalIterator = verticalIterator + 1;
      collisionValuePointer = collisionValuePointer + 1;
    } while (verticalIterator < 2);
    rowIndex = rowIndex + 1;
    alternateGridRowPointer = alternateGridRowPointer + 1;
  } while (rowIndex < 2);

  if (retryCount < 3) {
    this->UpdateObjectOnGrid(horizontalClampedPosition << 4, randomHorizontalPosition << 4);
    randomVerticalPosition = this->TrackObjects(0x30);
    this->mainSceneHandler->SetCollisionValueInRectangularRegion(horizontalClampedPosition, randomHorizontalPosition, 2, 2, (int16_t)randomVerticalPosition);
    this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, 0x3c, (intptr_t)this);
    return;
  }
  goto label_cancel_item_placement;

label_increase_search_radius:
  if (0x7f < searchRadius) {
    searchRadius = 0x9;
    retryCount = retryCount + 1;
  }
  searchRadius = searchRadius + 1;
  if (2 < retryCount) {
  label_cancel_item_placement:
    this->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(this, 0x0);
    return;
  }
  goto label_retry_item_placement;
}

__forceinline void SceneClassItem::Case_0x7d3b() {
  SceneClassCameraBase* cameraObject;
  int32_t spriteOffsetY;
  int32_t spriteYPosition;

  if (this->init0 < 2) {
    spriteOffsetY = 0x10;
    if (this->init0_2 <= 0x10) {
      spriteOffsetY = (int32_t)this->init0_2;
    }
    cameraObject = this->mainSceneHandler->sceneCamera;
    spriteYPosition = this->matrixIndexYTimes16;
    cameraObject->DrawSprite((this->matrixIndexXTimes16 + 1) * 0x10, (spriteYPosition * 0x10) + spriteOffsetY, this->init0_3, ((int16_t)spriteYPosition + 0x1f) * 0x10);
    return;
  }
  if (((int32_t)((int32_t)this->init0_2 + ((int32_t)this->init0_2 >> 0x1f & 7U)) >> 3 & 1U) == 0) {
    cameraObject = this->mainSceneHandler->sceneCamera;
    spriteOffsetY = this->matrixIndexYTimes16;
    cameraObject->DrawSprite((this->matrixIndexXTimes16 + 1) * 0x10, (spriteOffsetY + 1) * 0x10, this->init0_3, ((int16_t)spriteOffsetY * -0x10) + -0x1f0);
    return;
  }
}

__forceinline void SceneClassItem::Case_0x7d3c() {
  int16_t stateValue;

  stateValue = this->init0;
  switch (stateValue) {
  case 2:
    this->mainSceneHandler->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(this, 0x0);
    return;
  case 1:
    stateValue = this->init0_2;
    this->init0_2 = stateValue + 1;
    if (this->size_9600 + 0x10 <= stateValue) {
      this->mainSceneHandler->SetCollisionValueInRectangularRegion(this->matrixIndexXTimes16, this->matrixIndexYTimes16, 2, 2, 0xfffe);
      this->init0_2 = 0x10;
      this->init0 = 2;
      return;
    }
    break;
  case 0:
    stateValue = this->init0_2;
    this->init0_2 = stateValue + 1;
    if (0xf < stateValue) {
      this->init0 = 1;
      return;
    }
  }
}

__forceinline void SceneClassItem::Case_0x7d3e() {
  this->mainSceneHandler->primarySwitchSingleParam(0x7d35, (intptr_t)ItemStruct12k->itemArray[this->itemIndex].name, 0x1);
}

__forceinline void SceneClassItem::Case_0x7d04(intptr_t param2) {
  GameWindowBase* windowObject;

  if ((this->init0 < 2) && (windowObject = ObjectList[param2].sceneClassObjectPointer, windowObject != nullptr)) {
    windowObject->primarySwitchSingleParam(0x7d05, (int32_t)this->itemIndex, 0);
    this->mainSceneHandler->SetCollisionValueInRectangularRegion(this->matrixIndexXTimes16, this->matrixIndexYTimes16, 2, 2, 0xfffe);
    this->init0_2 = 0x10;
    this->init0 = 2;
  }
}

void SceneClassItem::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param3) {

  (void)param3;

  switch (switchParam) {
  case 0x7d11:
    Case_0x7d11(param2);
    break;

  case 0x7d3b:
    Case_0x7d3b();
    break;

  case 0x7d3c:
    Case_0x7d3c();
    break;

  case 0x7d3e:
    Case_0x7d3e();
    break;

  case 0x7d04:
    Case_0x7d04(param2);
    break;
  }
}
