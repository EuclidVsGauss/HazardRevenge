#include <stdio.h>
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/AnimationSummon.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSpellcast.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardExterns/GameWindowSpellcast.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/CharacterEquipment.hpp"
#include "HazardStructs/InventoryItemAccessory.hpp"
#include "HazardStructs/InventoryItemArmor.hpp"
#include "HazardStructs/InventoryItemSpell.hpp"
#include "HazardStructs/InventoryItemWeapon.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"
#include "HazardStructs/ObjectWrapper.hpp"
#include "HazardStructs/WindowReference.hpp"

const int32_t ScreenScroll_LowerBoundary_15 = 15;
const int32_t ScreenScroll_UpperBoundaryX_625 = 625;
const int32_t ScreenScroll_UpperBoundaryY_465 = 465;
const int32_t Sidebar_BoundaryX_145 = 145;

__forceinline void Case_0x7d11(GameWindowSpellcast* this_ptr, intptr_t param_2) {
  GameWindowBase* sceneClassUser;
  ActiveCharacter* activeCharacter;
  int32_t index;
  ActiveCharacter** actCharPtr;
  int32_t currentMp;
  int32_t mpEquipmentBonus;
  InventoryItemSpell* spellItemPtr;

  sceneClassUser = this_ptr->sceneClassUser;
  this_ptr->mainSceneHandler = (SceneHandler*)param_2;
  mpEquipmentBonus = 0;
  index = 0;
  this_ptr->coord1 = sceneClassUser->matrixIndexXTimes16;
  this_ptr->coord2 = sceneClassUser->matrixIndexYTimes16;
  if (TeamCharacterList[0] != nullptr) {
    actCharPtr = TeamCharacterList;
    activeCharacter = TeamCharacterList[0];
    do {
      if (activeCharacter->shiftedSceneClassUser0x48 == sceneClassUser) {
        break;
      }
      activeCharacter = actCharPtr[1];
      actCharPtr = actCharPtr + 1;
      index = index + 1;
    } while (activeCharacter != nullptr);
  }
  activeCharacter = TeamCharacterList[index];
  if (activeCharacter != nullptr) {
    if (0 < (activeCharacter->charEquip).equipmentWeapon.quantity) {
      mpEquipmentBonus = (activeCharacter->charEquip).equipmentWeapon.mp;
    }
    if (0 < (activeCharacter->charEquip).equipmentArmor.quantity) {
      mpEquipmentBonus = mpEquipmentBonus + (activeCharacter->charEquip).equipmentArmor.mp;
    }
    if (0 < (activeCharacter->charEquip).equipmentAccessory1.quantity) {
      mpEquipmentBonus = mpEquipmentBonus + (activeCharacter->charEquip).equipmentAccessory1.mp;
    }
    if (0 < (activeCharacter->charEquip).equipmentAccessory2.quantity) {
      mpEquipmentBonus = mpEquipmentBonus + (activeCharacter->charEquip).equipmentAccessory2.mp;
    }
  }
  if (sceneClassUser->mainSceneHandler->isMagicEnabled != 0) {
    spellItemPtr = this_ptr->spellItem;
    currentMp = activeCharacter->characterBaseStats->CurrentMp;
    if (((mpEquipmentBonus + currentMp) >= MpCostRelated_UnconfirmedLength[spellItemPtr->spellLevel + (spellItemPtr->spellTypeAsMpCostIndex * 6)]) && (spellItemPtr->spellType != 3 || (currentMp >= activeCharacter->characterBaseStats->MaxMp))) {
      this_ptr->mainSceneHandler->primarySwitchSingleParam_0x7d14(4, 0);
      this_ptr->primarySwitchSingleParam(0x7d16, 0x0, 0x0);
      return;
    }
  }
  this_ptr->mainSceneHandler->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(this_ptr, 0);
  this_ptr->mainSceneHandler->primarySwitchSingleParam(0x7d0a, 26, 0x0);
}

__forceinline void Case_0x7d3b(GameWindowSpellcast* this_ptr) {
  GameWindowBase* sceneClassUser;
  SceneHandler* sceneHandler;

  sceneClassUser = this_ptr->sceneClassUser;
  sceneHandler = sceneClassUser->mainSceneHandler;
  sceneHandler->UpdateVisibilityRendering(sceneClassUser->matrixIndexXTimes16 << 4, sceneClassUser->matrixIndexYTimes16 << 4, sceneHandler->sceneCamera, (this_ptr->spellItem->spellType == 2));
}

__forceinline void Case_0x7d16(GameWindowSpellcast* this_ptr, intptr_t param_2) {
  WindowReference windowReference;

  windowReference.coords[0] = 0;
  windowReference.coords[1] = 0;
  windowReference.coords[2] = 640;
  windowReference.coords[3] = 480;
  windowReference.windowAddress = (intptr_t)this_ptr;
  if (param_2 != 0x0) {
    windowReference.coords[2] = 0;
  }
  this_ptr->mainSceneHandler->primarySwitchSingleParam_SetWindow_0x7d16(6, &windowReference);
}

__forceinline void Case_0x7d0e(GameWindowSpellcast* this_ptr, intptr_t param_2) {
  GameWindowBase* sceneClassUserPtr;
  SceneHandler* mainHandlerPtr;
  SceneClassCameraBase* cameraPtr;
  bool isTargetMagic;
  int32_t coordDiv2;
  int32_t verticalScrollInput;
  int32_t verticalScrollBoundary;
  int32_t horizontalScrollInput;
  int32_t horizontalScrollBoundary;
  int32_t collidedObjectIndex;
  InventoryItemSpell* spellItemLocal;
  bool isSpellTargetable;

  if (param_2 == 0x0) {
    return;
  }
  if (this_ptr->isActiveFlag != 0) {
    return;
  }
  if (InputStates128[75] != '\0') {
    horizontalScrollInput = -3;
  }
  else {
    horizontalScrollInput = -(uint32_t)(InputStates128[77] != '\0') & 3;
  }
  if (CursorXCoord < ScreenScroll_LowerBoundary_15) {
    verticalScrollBoundary = -3;
  }
  else {
    verticalScrollBoundary = ((CursorXCoord < ScreenScroll_UpperBoundaryX_625) - 1) & 3;
  }
  if (InputStates128[72] != '\0') {
    horizontalScrollBoundary = -10;
  }
  else {
    horizontalScrollBoundary = -(uint32_t)(InputStates128[80] != '\0') & 3;
  }
  if (CursorYCoord < ScreenScroll_LowerBoundary_15) {
    verticalScrollInput = -10;
  }
  else {
    verticalScrollInput = ((CursorYCoord < ScreenScroll_UpperBoundaryY_465) - 1) & 3;
  }
  cameraPtr = this_ptr->sceneClassUser->mainSceneHandler->sceneCamera;
  cameraPtr->primarySwitchSingleParam_0x7d00((verticalScrollBoundary + horizontalScrollInput), (verticalScrollInput + horizontalScrollBoundary));
  sceneClassUserPtr = this_ptr->sceneClassUser;
  collidedObjectIndex = ((sceneClassUserPtr->mainSceneHandler)->sceneCamera)->cameraCoordX + -0x91 + CursorXCoord;
  this_ptr->coord1 = (int32_t)(collidedObjectIndex + (collidedObjectIndex >> 0x1f & 0xfU)) >> 4;
  collidedObjectIndex = ((sceneClassUserPtr->mainSceneHandler)->sceneCamera)->cameraCoordY + CursorYCoord;
  collidedObjectIndex = collidedObjectIndex + (collidedObjectIndex >> 0x1f & 0xfU);
  coordDiv2 = collidedObjectIndex >> 4;
  this_ptr->coord2 = coordDiv2;
  if (CursorXCoord < Sidebar_BoundaryX_145) {
    isSpellTargetable = false;
  label_invalid_spell_target:
    isTargetMagic = false;
  }
  else {
    mainHandlerPtr = sceneClassUserPtr->mainSceneHandler;
    isSpellTargetable = mainHandlerPtr->PaddedGridMap_Visibility[collidedObjectIndex >> 5][this_ptr->coord1 >> 1] != 0;
    if ((((!isSpellTargetable) || (collidedObjectIndex = (int32_t)mainHandlerPtr->PaddedGridMap_Collision[coordDiv2][this_ptr->coord1], collidedObjectIndex < 0)) || (horizontalScrollBoundary = ObjectList[collidedObjectIndex].scriptUserFlags & 3, horizontalScrollBoundary == 0)) || ((horizontalScrollBoundary != 1 || (spellItemLocal = this_ptr->spellItem, spellItemLocal->spellEffect == 6)) && (horizontalScrollBoundary != 2 || (spellItemLocal = this_ptr->spellItem, spellItemLocal->spellEffect != 6)))) {
      goto label_invalid_spell_target;
    }
    isTargetMagic = true;
    this_ptr->coord1 = ObjectList[collidedObjectIndex].sceneClassObjectPointer->matrixIndexXTimes16;
    this_ptr->coord2 = ObjectList[collidedObjectIndex].sceneClassObjectPointer->matrixIndexYTimes16;
    if (spellItemLocal->spellType == 2) {
      collidedObjectIndex = sceneClassUserPtr->matrixIndexXTimes16 - this_ptr->coord1;
      if (collidedObjectIndex < 0) {
        collidedObjectIndex = -collidedObjectIndex;
      }
      if (collidedObjectIndex < 3) {
        collidedObjectIndex = sceneClassUserPtr->matrixIndexYTimes16 - this_ptr->coord2;
        if (collidedObjectIndex < 0) {
          collidedObjectIndex = -collidedObjectIndex;
        }
        if (collidedObjectIndex < 3) {
          goto label_valid_spell_target;
        }
      }
      goto label_invalid_spell_target;
    }
  }
label_valid_spell_target:
  if (this_ptr->spellItem->spellType == 3) {
    isTargetMagic = true;
    isSpellTargetable = true;
  }
  this_ptr->mainSceneHandler->primarySwitchSingleParam(0x7d17, (int32_t)(-(uint32_t)isSpellTargetable & 8), !isTargetMagic);
  if (((MouseButtonClick & 0x22) == 2) && isTargetMagic) {
    this_ptr->primarySwitchSingleParam_0x7d22(0x0, 0x0);
  }
  if ((MouseButtonClick & 0x11) == 1) {
    this_ptr->mainSceneHandler->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(this_ptr, 0x0);
  }
}

void GameWindowSpellcast::primarySwitchSingleParam(int32_t param_1, intptr_t param_2, intptr_t param_3) {

  (void)param_3;

  switch (param_1) {
  case 0x7d11:
    Case_0x7d11(this, param_2);
    break;

  case 0x7d3b:
    Case_0x7d3b(this);
    break;

  case 0x7d3c:
    this->CreateSpellAnimationObject();

  case 0x7d16:
    Case_0x7d16(this, param_2);
    break;

  case 0x7d22: {
    SceneHandler* sceneHandler;
    SceneClassCameraBase* cameraBase;
    NumericalCharacterStats* numericalStats;
    int32_t spellRangeOrLevel;
    int32_t spellTypeLocal;
    int32_t matrixIndexDiv2;
    InventoryItemSpell* spellItemPtr;
    int32_t orientationIndex;
    AnimationSummon* summonAnimation;
    char animationString[20];

    spellRangeOrLevel = 0;
    if (this->isActiveFlag == 0) {

      this->primarySwitchSingleParam_SetWindow_0x7d16(0x1, nullptr);
      this->isActiveFlag = 1;

      sprintf(this->spellAnimationAct, s__d_act, this->spellItem->actAnimationNumber);
      cameraBase = this->sceneClassUser->mainSceneHandler->sceneCamera;
      cameraBase->primarySwitchSingleParam(0x7d21, (this->coord1 << 4), (this->coord2 << 4));
      this->sceneClassUser->primarySwitchSingleParam(0x7d1e, this->spellItem->experienceAwardedPerCast, 0x0);
      spellItemPtr = this->spellItem;
      spellTypeLocal = spellItemPtr->spellType;
      switch (spellTypeLocal) {
      case 1: {
        numericalStats = this->characterInventory->characterBaseStats;
        numericalStats->CurrentMp = numericalStats->CurrentMp - MpCostRelated_UnconfirmedLength[spellItemPtr->spellLevel + (spellItemPtr->spellTypeAsMpCostIndex * 6)];
        spellRangeOrLevel = this->spellItem->spellLevel;
        this->incrementIndex = 1;
        this->loopMax_spellRange = spellRangeOrLevel << 2;
        this->sceneClassUser->primarySwitchSingleParam(0x7d36, 0x0, 0x0);
      } break;
      case 2: {
        matrixIndexDiv2 = this->sceneClassUser->matrixIndexXTimes16 / 2;
        spellTypeLocal = this->coord1 / 2;
        if (spellTypeLocal != matrixIndexDiv2) {
          spellRangeOrLevel = (((spellTypeLocal <= matrixIndexDiv2) - 1) & 2) - 1;
        }
        matrixIndexDiv2 = this->sceneClassUser->matrixIndexYTimes16 / 2;
        spellTypeLocal = this->coord2 / 2;
        if (spellTypeLocal == matrixIndexDiv2) {
          spellTypeLocal = 0;
        }
        else {
          spellTypeLocal = (((spellTypeLocal <= matrixIndexDiv2) - 1) & 2) - 1;
        }
        this->orientationRelated = 0;
        do {
          orientationIndex = this->orientationRelated;
          if ((spellRangeOrLevel == MagicAnimRel_Unconfirmedength[orientationIndex * 2]) && (spellTypeLocal == MagicAnimRel_Unconfirmedength[(orientationIndex * 2) + 1])) {
            break;
          }
          this->orientationRelated = orientationIndex + 1;
        } while ((orientationIndex + 1) < 8);
        this->incrementIndex = 0;
        if (spellItemPtr->spellLevel == 1) {
          spellRangeOrLevel = 3;
        }
        else {
          spellRangeOrLevel = (-(uint32_t)(spellItemPtr->spellLevel != 2) & 4) + 5;
        }
        this->loopMax_spellRange = spellRangeOrLevel;
        numericalStats = this->characterInventory->characterBaseStats;
        numericalStats->CurrentMp = numericalStats->CurrentMp - MpCostRelated_UnconfirmedLength[spellItemPtr->spellLevel + (spellItemPtr->spellTypeAsMpCostIndex * 6)];
        this->sceneClassUser->primarySwitchSingleParam(0x7d38, (this->orientationRelated & 7), 0x0);
      } break;
      case 3: {
        sprintf(animationString, s__d_act, spellItemPtr->typeId);
        summonAnimation = new AnimationSummon(animationString);
        this->sceneClassUser->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(summonAnimation, 0x0);
        this->coord1 = this->sceneClassUser->matrixIndexXTimes16;
        this->coord2 = this->sceneClassUser->matrixIndexYTimes16;
        this->loopMax_spellRange = 225;
        this->characterInventory->characterBaseStats->CurrentMp = 0;
        this->sceneClassUser->primarySwitchSingleParam(0x7d36, 0x0, 0x0);
      } break;
      }
    }
  } break;

  case 0x7d0e:
    Case_0x7d0e(this, param_2);
    break;

  case 0x7d20:
  case 0x7d0c:
    this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
  }
}
