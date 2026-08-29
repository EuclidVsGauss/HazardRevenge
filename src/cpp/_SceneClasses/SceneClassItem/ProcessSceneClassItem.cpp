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

__forceinline void SceneClassItem::InitializeObject_0x7d11(intptr_t param2) {
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
  int32_t collisionValue;

  this->mainSceneHandler = (SceneHandler*)param2;
  this->mainSceneHandler->primarySwitchSingleParam_AddObjectToScene_0x7d0f(this, 0x0);
  retryCount = 0;
  searchRadius = 0x4;

  for (;;) {
    randomHorizontalPosition = (this->mainSceneHandler->mapWidth / 16) - 4;
    rowIndex = searchRadius / 8;
    horizontalClampedPosition = PseudoRng();
    horizontalClampedPosition = ((horizontalClampedPosition % searchRadius) / 4) - rowIndex + this->matrixIndexXTimes16;
    if (horizontalClampedPosition > randomHorizontalPosition) {
      horizontalClampedPosition = randomHorizontalPosition;
    }
    horizontalClampedPosition = ((horizontalClampedPosition <= 0) - 1) & horizontalClampedPosition;
    randomVerticalPosition = (this->mainSceneHandler->mapHeight / 16) - 4;
    randomHorizontalPosition = PseudoRng();
    randomHorizontalPosition = ((randomHorizontalPosition % searchRadius) / 4) - rowIndex + this->matrixIndexYTimes16;
    if (randomHorizontalPosition > randomVerticalPosition) {
      randomHorizontalPosition = randomVerticalPosition;
    }
    randomHorizontalPosition = randomHorizontalPosition & ((randomHorizontalPosition <= 0) - 1);
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
        collisionValue = *collisionValuePointer;
        if ((collisionValue >= 0) && (collisionValue != -1)) {
          goto label_increase_search_radius;
        }
        verticalIterator = verticalIterator + 1;
        collisionValuePointer = collisionValuePointer + 1;
      } while (verticalIterator < 2);
      rowIndex = rowIndex + 1;
      alternateGridRowPointer = alternateGridRowPointer + 1;
    } while (rowIndex < 2);
    break;

  label_increase_search_radius:
    if (searchRadius >= 0x80) {
      searchRadius = 0x9;
      retryCount = retryCount + 1;
    }
    searchRadius = searchRadius + 1;
    if (retryCount >= 3) {
      break;
    }
  }

  if (retryCount >= 3) {
    this->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(this, 0x0);
    return;
  }
  this->UpdateObjectOnGrid(horizontalClampedPosition << 4, randomHorizontalPosition << 4);
  randomVerticalPosition = this->TrackObjects(0x30);
  this->mainSceneHandler->SetCollisionValueInRectangularRegion(horizontalClampedPosition, randomHorizontalPosition, 2, 2, (int16_t)randomVerticalPosition);
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, 0x3c, (intptr_t)this);
}

__forceinline void SceneClassItem::DrawObject_0x7d3b() {
  SceneClassCameraBase* cameraObject;
  int32_t spriteOffsetY;
  int32_t spriteYPosition;

  if (this->init0 < 2) {
    spriteOffsetY = (this->init0_2 > 0x10) ? 0x10 : this->init0_2;
    cameraObject = this->mainSceneHandler->sceneCamera;
    spriteYPosition = this->matrixIndexYTimes16;
    cameraObject->DrawSprite((this->matrixIndexXTimes16 + 1) * 0x10, (spriteYPosition * 0x10) + spriteOffsetY, this->init0_3, (spriteYPosition + 0x1f) * 0x10);
    return;
  }
  if (((this->init0_2 / 8) & 1) == 0) {
    cameraObject = this->mainSceneHandler->sceneCamera;
    spriteOffsetY = this->matrixIndexYTimes16;
    cameraObject->DrawSprite((this->matrixIndexXTimes16 + 1) * 0x10, (spriteOffsetY + 1) * 0x10, this->init0_3, -0x1f0 - (spriteOffsetY << 4));
    return;
  }
}

__forceinline void SceneClassItem::RunTick_0x7d3c() {
  int16_t stateValue;

  stateValue = this->init0;
  switch (stateValue) {
  case 2:
    stateValue = this->init0_2;
    this->init0_2 = stateValue + 1;
    if (stateValue >= 0x20) {
      this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
      return;
    }
    break;
  case 1:
    stateValue = this->init0_2;
    this->init0_2 = stateValue + 1;
    if (stateValue >= this->size_9600 + 0x10) {
      this->mainSceneHandler->SetCollisionValueInRectangularRegion(this->matrixIndexXTimes16, this->matrixIndexYTimes16, 2, 2, 0xfffe);
      this->init0_2 = 0x10;
      this->init0 = 2;
      return;
    }
    break;
  case 0:
    stateValue = this->init0_2;
    this->init0_2 = stateValue + 1;
    if (stateValue >= 0x10) {
      this->init0 = 1;
      return;
    }
  }
}

__forceinline void SceneClassItem::ShowItemNameTooltip_0x7d3e() {
  this->mainSceneHandler->primarySwitchSingleParam(0x7d35, (intptr_t)ItemStruct12k->itemArray[this->itemIndex].name, 0x1);
}

__forceinline void SceneClassItem::TriggerInteraction_0x7d04(intptr_t param2) {
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
    this->InitializeObject_0x7d11(param2);
    break;

  case 0x7d3b:
    this->DrawObject_0x7d3b();
    break;

  case 0x7d3c:
    this->RunTick_0x7d3c();
    break;

  case 0x7d3e:
    this->ShowItemNameTooltip_0x7d3e();
    break;

  case 0x7d04:
    this->TriggerInteraction_0x7d04(param2);
    break;
  }
}
