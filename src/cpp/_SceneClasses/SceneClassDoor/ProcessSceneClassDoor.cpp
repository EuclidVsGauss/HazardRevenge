#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneClassDoor.hpp"
#include "HazardClasses/SceneClassUser.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardExterns/SceneClassDoor.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"
#include "HazardStructs/ObjectWrapper.hpp"
#include "HazardStructs/UnlockDoorTuple.hpp"

__forceinline void SceneClassDoor::HandleCase_0x7d11(intptr_t param2) {
  this->mainSceneHandler = (SceneHandler*)param2;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0f, (intptr_t)(GameWindowBase*)this, 0x0);
  if (this->currentState == 0) {
    uint32_t doorMovementIndex = this->TrackObjects(0x40);
    this->mainSceneHandler->SetCollisionValueInRectangularRegion(this->matrixIndexXTimes16, this->matrixIndexYTimes16, 2, 2, (int16_t)doorMovementIndex);
    this->actStand = this->actClass->GetActionIndexByName(s_fstand);
    return;
  }
  int32_t baseYIndex = this->matrixIndexYTimes16;
  int32_t baseXIndex = this->matrixIndexXTimes16;
  SceneHandler* sceneHandlerPtr = this->mainSceneHandler;
  for (int32_t rowOffset = 0; rowOffset < 2; rowOffset++) {
    for (int32_t colOffset = 0; colOffset < 2; colOffset++) {
      sceneHandlerPtr->PaddedGridMap_LineOfSight[(baseYIndex + rowOffset) >> 1][(colOffset + baseXIndex) >> 1] = 0;
    }
  }
  this->actStand = this->actClass->GetActionIndexByName(s_fopened);
}

__forceinline void SceneClassDoor::HandleCase_0x7d3b() {
  int32_t drawXPos = (this->matrixIndexXTimes16 + 1) * 0x10;
  int32_t drawYPos = (this->matrixIndexYTimes16 + 1) * 0x10;

  ImageVectorWithHeader* solidFramePtr = __InlineGetSolidSpriteFrameForAction(this->actStand, this->actClass, this->counter);
  this->mainSceneHandler->sceneCamera->DrawSprite(drawXPos, drawYPos, solidFramePtr, drawYPos + 0x1e0);

  ImageVectorWithHeader* shadowFramePtr = __InlineGetShadowSpriteFrameForAction(this->actStand, this->actClass, this->counter);
  this->mainSceneHandler->sceneCamera->DrawSprite(drawXPos, drawYPos, shadowFramePtr, drawYPos);
}

__forceinline void SceneClassDoor::HandleCase_0x7d3c() {
  if (this->currentState != 2) {
    this->counter = this->counter + 1;
    return;
  }
  int32_t currentFrameIndex = this->counter;
  int32_t totalFramesMinus1 = this->actClass->GetFrameCountForAction(this->actStand);
  this->counter = currentFrameIndex + 1;
  if (currentFrameIndex < totalFramesMinus1 + -1) {
    return;
  }
  currentFrameIndex = this->actClass->GetActionIndexByName(s_fopened);
  this->actStand = currentFrameIndex;
  this->counter = 0;
  this->currentState = 1;
  if (GameFlags == nullptr) {
    return;
  }
  GameFlags[this->gameFlag] = 1;
}

__forceinline void SceneClassDoor::HandleCase_0x7d04(intptr_t param2) {
  uint32_t doorIndex;

  switch (this->doorUnlockType) {
  default:
    return;
  case 0x2:
    this->primarySwitchSingleParam(0x7d30, 0x0, 0x0);
    return;
  case 0x1: {
    for (int32_t teamIndex = 0; TeamCharacterList[teamIndex] != nullptr; teamIndex++) {
      if (((ObjectList[param2].sceneClassObjectPointer == TeamCharacterList[teamIndex]->shiftedSceneClassUser0x48) && (TeamCharacterList[teamIndex]->characterId == 4)) && (10 <= TeamCharacterList[teamIndex]->characterBaseStats->CurrentMp)) {
        this->primarySwitchSingleParam(0x7d30, 0x0, 0x0);
        GameWindowBase* activeWindowPtr = TeamCharacterList[teamIndex]->shiftedSceneClassUser0x48;
        int32_t activeXGrid = activeWindowPtr->matrixIndexXTimes16 / 2;
        int32_t doorXGrid = this->matrixIndexXTimes16 / 2;
        if (doorXGrid == activeXGrid) {
          doorXGrid = 0;
        }
        else {
          doorXGrid = (doorXGrid <= activeXGrid) ? -1 : 1;
        }
        int32_t activeYGrid = activeWindowPtr->matrixIndexYTimes16 / 2;
        int32_t doorYGrid = this->matrixIndexYTimes16 / 2;
        if (activeXGrid == activeYGrid) {
          doorYGrid = 0;
        }
        else {
          doorYGrid = (doorYGrid <= activeYGrid) ? -1 : 1;
        }

        for (doorIndex = 0; doorIndex < 8; doorIndex++) {
          if ((doorXGrid == UnlockDoorDirectionalTuple[doorIndex].value1) && (doorYGrid == UnlockDoorDirectionalTuple[doorIndex].value2)) {
            break;
          }
        }
        activeWindowPtr->primarySwitchSingleParam(0x7d38, (doorIndex & 7), 0x0);
        TeamCharacterList[teamIndex]->characterBaseStats->CurrentMp = TeamCharacterList[teamIndex]->characterBaseStats->CurrentMp - 10;
        uint32_t sfxId = __InlineGetSoundEffectIndex(this->actClass, 1);
        this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, sfxId, (intptr_t)this);
        return;
      }
    }
    break;
  }

  case 0x0: {
    for (int32_t itemIndex = 0; itemIndex < 32; itemIndex++) {
      if ((0 < ItemInventory[itemIndex].quantity) && (ItemInventory[itemIndex].typeId == 30)) {
        this->primarySwitchSingleParam(0x7d30, 0x0, 0x0);
        ItemInventory[itemIndex].quantity = ItemInventory[itemIndex].quantity - 1;
        break;
      }
    }
    uint32_t sfxId = __InlineGetSoundEffectIndex(this->actClass, 1);
    this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, sfxId, (intptr_t)this);
    return;
  }
  }
}

__forceinline void SceneClassDoor::HandleCase_0x7d30() {
  this->mainSceneHandler->SetCollisionValueInRectangularRegion(this->matrixIndexXTimes16, this->matrixIndexYTimes16, 2, 2, 0xfffe);
  int32_t baseYIndex = this->matrixIndexYTimes16;
  int32_t baseXIndex = this->matrixIndexXTimes16;
  SceneHandler* sceneHandlerPtr = this->mainSceneHandler;

  for (int32_t rowOffset = 0x0; rowOffset < 2; rowOffset++) {
    for (int32_t colOffset = 0x0; colOffset < 2; colOffset++) {
      sceneHandlerPtr->PaddedGridMap_LineOfSight[(rowOffset + baseYIndex) >> 1][(colOffset + baseXIndex) >> 1] = 0;
    }
  }

  this->mainSceneHandler->primarySwitchSingleParam(0x7d26, 0, 0x0);
  this->actStand = this->actClass->GetActionIndexByName(s_fopen);
  this->counter = 0;
  this->currentState = 2;
  uint32_t sfxId = __InlineGetSoundEffectIndex(this->actClass);
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, sfxId, (intptr_t)this);
}

void SceneClassDoor::primarySwitchSingleParam(int32_t switchParam, intptr_t param2, intptr_t param3) {
  (void)param3;

  switch (switchParam) {
  case 0x7d11:
    HandleCase_0x7d11(param2);
    break;
  case 0x7d3b:
    HandleCase_0x7d3b();
    break;
  case 0x7d3c:
    HandleCase_0x7d3c();
    break;
  case 0x7d04:
    HandleCase_0x7d04(param2);
    break;
  case 0x7d30:
    HandleCase_0x7d30();
    break;
  default:
    break;
  }
}
