#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSpellcast.hpp"
#include "HazardClasses/GameWindowWeapon.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardEnums/ItemFlag.hpp"
#include "HazardEnums/WindowToggle.hpp"
#include "HazardExterns/GameWindowWeapon.hpp"
#include "HazardGlobals.hpp"
#include "HazardPatches.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/CharacterEquipment.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/InventoryItemSharant.hpp"
#include "HazardStructs/InventoryItemSpell.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/InventoryItemWeapon.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ItemReferenceStruct.hpp"
#include "HazardStructs/WeaponSlotFrame.hpp"
#include "HazardStructs/WindowReference.hpp"

const int32_t WeaponWindow_ActiveSlot_LowerX_456 = 456;
const int32_t WeaponWindow_ActiveSlot_UpperX_574 = 574;
const int32_t WeaponWindow_ActiveSlot_LowerY_43 = 43;
const int32_t WeaponWindow_ActiveSlot_UpperY_71 = 71;

const int32_t WeaponWindow_Height_288 = 288;

const int32_t WeaponWindow_Grid_OffsetX_1824 = 1824;
const int32_t WeaponWindow_Grid_StepX_118 = 118;

__forceinline void GameWindowWeapon::InitializeObject_0x7d11(intptr_t param_2) {
  this->mainSceneHandler = (SceneHandler*)param_2;
  this->primarySwitchSingleParam_SetWindow_0x7d16(0x0, nullptr);
}

__forceinline void GameWindowWeapon::DrawObject_0x7d3b() {
  InventoryItemStruct* itemStructPtr;
  ImageVectorWithHeader* spriteFrame;
  int32_t charIndex;
  ActiveCharacter* activeChar;
  int32_t sharantCount;

  sharantCount = 0;

  spriteFrame = this->actWin2->__InlineGetSolidSpriteFrameForAction(this->actFrame, 0);
  GameWindowRightSide->RenderClippedSprite(this->staticXBoundary + -0x91, this->dynamicYBoundary, spriteFrame, DrawLayer::Layer0xFFF6);

  for (charIndex = 0; TeamCharacterList[charIndex] != nullptr; charIndex = charIndex + 1) {
    if (TeamCharacterList[charIndex]->sceneClassUser == *this->mainSceneHandler->selectedUnits32) {
      break;
    }
  }

  activeChar = TeamCharacterList[charIndex];
  if (activeChar == nullptr) {
    return;
  }

  if (0 < (activeChar->charEquip).equipmentWeapon.quantity) {
    for (; sharantCount < (activeChar->charEquip).equipmentWeapon.numberSharants; sharantCount++) {
      spriteFrame = this->actWin2->__InlineGetSolidSpriteFrameForAction(this->actSlot, 0);
      (GameWindowRightSide->RenderClippedSprite)(this->staticXBoundary + -145 + (sharantCount * 19), this->dynamicYBoundary, spriteFrame, DrawLayer::Layer0xFFF6);
    }
  }

  for (charIndex = 0; charIndex < 40; charIndex++) {
    if (0 < (&(activeChar->charEquip).equipmentWeapon)[charIndex].quantity) {
      if (charIndex < 34) {
        spriteFrame = Item00Act->__InlineGetSolidSpriteFrameForAction((&(activeChar->charEquip).equipmentWeapon)[charIndex].actOffset, 1);
      }
      else {
        spriteFrame = Item00Act->__InlineGetSolidSpriteFrameForAction((&(activeChar->charEquip).equipmentWeapon)[charIndex].actOffset, 2);
      }
      GameWindowRightSide->RenderClippedSprite(WeaponSlotFrames[charIndex].itemCoord1 + -145 + this->staticXBoundary, WeaponSlotFrames[charIndex].itemCoord2 + this->dynamicYBoundary, spriteFrame, DrawLayer::Layer0xFFF6);
    }
  }

  charIndex = 0;
  itemStructPtr = &(activeChar->charEquip).ActiveSlots[0];
  do {
    if (itemStructPtr->typeId != 0) {

      spriteFrame = Item00Act->__InlineGetSolidSpriteFrameForAction(itemStructPtr->actOffset, 1);
      GameWindowRightSide->RenderClippedSprite(this->staticXBoundary + 326 + charIndex, this->dynamicYBoundary + 57, spriteFrame, DrawLayer::Layer0xFFF6);
    }
    charIndex = charIndex + 30;
    itemStructPtr = itemStructPtr + 1;
  } while (charIndex < 120);

  if (this->latestEquipmentItem.quantity <= 0) {
    return;
  }

  spriteFrame = Item00Act->__InlineGetSolidSpriteFrameForAction(this->latestEquipmentItem.actOffset, 1);
  GameWindowLeftSidebar->RenderClippedSprite(this->cursorWidthWhileHolding + CursorXCoord, this->cursorHeightWhileHolding + CursorYCoord, spriteFrame, DrawLayer::Layer0xFFF7);

  spriteFrame = Item00Act->__InlineGetSolidSpriteFrameForAction(this->latestEquipmentItem.actOffset, 1);
  GameWindowRightSide->RenderClippedSprite(this->cursorWidthWhileHolding + -0x91 + CursorXCoord, this->cursorHeightWhileHolding + CursorYCoord, spriteFrame, DrawLayer::Layer0xFFF7);
  if (this->latestEquipmentItem.quantity <= 1) {
    return;
  }

  spriteFrame = Item00Act->__InlineGetSolidSpriteFrameForAction(this->latestEquipmentItem.actOffset, 1);
  GameWindowLeftSidebar->RenderClippedSprite(this->cursorWidthWhileHolding + CursorXCoord, this->cursorHeightWhileHolding + CursorYCoord, spriteFrame, DrawLayer::Layer0xFFF7);

  spriteFrame = this->actWin2->__InlineGetSolidSpriteFrameForAction(this->actSlot, this->latestEquipmentItem.quantity);
  GameWindowRightSide->RenderClippedSprite(this->cursorWidthWhileHolding + -0x1c7 + CursorXCoord, this->cursorHeightWhileHolding + -0xe6 + CursorYCoord, spriteFrame, DrawLayer::Layer0xFFF7);
}

__forceinline void GameWindowWeapon::RunTick_0x7d3c() {
  int32_t toggleState;
  int32_t adjustedY;

  toggleState = this->hideOpenCloseFlag;
  switch (toggleState) {
  case WindowToggle::Hidden:
    adjustedY = this->dynamicYBoundary + 0x10;
    this->dynamicYBoundary = adjustedY & ((0 < adjustedY) - 1);
    this->primarySwitchSingleParam(0x7d16, 0x0, 0x0);
    if (this->dynamicYBoundary != 0) {
      return;
    }
    this->hideOpenCloseFlag = 1;
    return;

  case WindowToggle::Opening:
    if (*this->mainSceneHandler->selectedUnits32 == nullptr) {
      this->hideOpenCloseFlag = WindowToggle::Closing;
    }
    return;

  case WindowToggle::Closing:
    toggleState = this->dynamicYBoundary + -0x10;
    if (toggleState < -0x120) {
      toggleState = -0x120;
    }
    this->dynamicYBoundary = toggleState;
    this->primarySwitchSingleParam(0x7d16, 0x0, 0x0);
    if (this->dynamicYBoundary != -0x120) {
      return;
    }
    this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
    return;
  default:
    return;
  }
}

__forceinline void GameWindowWeapon::CancelOrCloseWindow_0x7d0c() {
  this->hideOpenCloseFlag = WindowToggle::Closing;
}

__forceinline void GameWindowWeapon::PlaceItemInWindow_0x7d2e(intptr_t param_2, intptr_t param_3) {

  int32_t sharantLoopCounter;
  SceneHandler* sceneHandler;
  WeaponSlotFrame* weaponFrame;
  int32_t charIndex;
  uint32_t equipFlagMasked;
  ActiveCharacter* activeChar;
  SceneHandler* genericHandler;
  SceneHandler* equipHandler;
  int32_t slotValue;
  InventoryItemWeapon* weaponSlot;
  InventoryItemSharant* sharantSlot;
  InventoryItemStruct* activeSlot;
  InventoryItemStruct* destSlot;
  InventoryItemStruct* item;

  item = (InventoryItemStruct*)param_2;

  for (charIndex = 0; TeamCharacterList[charIndex] != nullptr; charIndex = charIndex + 1) {
    if (TeamCharacterList[charIndex]->sceneClassUser == *this->mainSceneHandler->selectedUnits32) {
      break;
    }
  }

  activeChar = TeamCharacterList[charIndex];
  if (activeChar != nullptr) {
    for (charIndex = 0; charIndex < 44; charIndex++) {
      weaponFrame = WeaponSlotFrames + charIndex;
      if (param_3 == 0) {
        slotValue = (weaponFrame->itemCoord1 + this->staticXBoundary) - CursorXCoord;
        if (slotValue < 0) {
          slotValue = -slotValue;
        }
        if (slotValue <= weaponFrame->itemFlag1) {
          slotValue = (this->dynamicYBoundary - CursorYCoord) + weaponFrame->itemCoord2;
          if (slotValue < 0) {
            slotValue = -slotValue;
          }
          if (slotValue <= weaponFrame->itemFlag1) {
            goto label_check_weapon_equip;
          }
        }
      }
      else if (param_3 == 1) {
      label_check_weapon_equip:

        if (((item->equipFlags & ItemFlag::SellAndWindowRelated_0x700) == weaponFrame->itemFlag2) && (((item->equipFlags >> (activeChar->characterId + 0xb)) & 1) == 0)) {
          if ((0 < (&(activeChar->charEquip).equipmentWeapon)[charIndex].quantity) && (equipHandler = activeChar->sceneClassUser->mainSceneHandler, equipHandler->primarySwitchSingleParam(0x7d2c, (intptr_t)(&(activeChar->charEquip).equipmentWeapon + charIndex), 0x0), charIndex == 0)) {
            sharantSlot = (activeChar->charEquip).equipmentSharants;
            sharantLoopCounter = 6;
            do {
              while (0 < sharantSlot->quantity) {
                sceneHandler = activeChar->sceneClassUser->mainSceneHandler;
                sceneHandler->primarySwitchSingleParam(0x7d2c, (intptr_t)sharantSlot, 0x0);
              }
              sharantSlot = sharantSlot + 1;
              sharantLoopCounter = sharantLoopCounter + -1;
            } while (sharantLoopCounter != 0);
          }
          if (((item->equipFlags & 0x700) == ItemFlag::WindowRelated_0x600) && ((activeChar->charEquip).equipmentWeapon.quantity <= 0 || (charIndex + -0x21 > (activeChar->charEquip).equipmentWeapon.numberSharants))) {
            this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, 0x1a, 0);
          }
          else {
            weaponSlot = &(activeChar->charEquip).equipmentWeapon + charIndex;

            memcpy(weaponSlot, item, sizeof(InventoryItemStruct));
            weaponSlot->quantity = 1;

            item->quantity = item->quantity - 1;
            equipFlagMasked = (uintptr_t)(&(activeChar->charEquip).equipmentWeapon)[charIndex].equipFlags & 0x700;
            if (equipFlagMasked == 0x100) {
              this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, 0x41, 0);
            }
            else {
              genericHandler = this->mainSceneHandler;
              if (equipFlagMasked == 0x200) {
                genericHandler->primarySwitchSingleParam(0x7d0a, 0x3f, 0);
              }
              else {
                genericHandler->primarySwitchSingleParam(0x7d0a, 0x3e, 0);
              }
            }
          }
          if (item->quantity == 0x0) {
            return;
          }
          sceneHandler = activeChar->sceneClassUser->mainSceneHandler;
          sceneHandler->primarySwitchSingleParam(0x7d2c, param_2, 0x0);
          return;
        }
      }
    }

    if (((
             (WeaponWindow_ActiveSlot_LowerX_456 < CursorXCoord) && (CursorXCoord < WeaponWindow_ActiveSlot_UpperX_574)) &&
         (WeaponWindow_ActiveSlot_LowerY_43 < CursorYCoord)) &&
        ((CursorYCoord < WeaponWindow_ActiveSlot_UpperY_71 &&
          ((item->equipFlags & ItemFlag::WindowSlot_0x40) != 0)) &&
         (((item->equipFlags >> (activeChar->characterId + 0xb)) & 1) == 0))) {

      int32_t sharantOffset = (((CursorXCoord * 4) - WeaponWindow_Grid_OffsetX_1824) / WeaponWindow_Grid_StepX_118) + 40;
      activeSlot = (InventoryItemStruct*)(&(activeChar->charEquip).equipmentWeapon + sharantOffset);
      if (0 < (&(activeChar->charEquip).equipmentWeapon)[sharantOffset].quantity) {
        sceneHandler = activeChar->sceneClassUser->mainSceneHandler;
        sceneHandler->primarySwitchSingleParam(0x7d2c, (intptr_t)activeSlot, 0x0);
      }
      destSlot = activeSlot;
      memcpy(destSlot, item, sizeof(InventoryItemStruct));
      activeSlot->quantity = 0;
    }
  }
}

__forceinline void GameWindowWeapon::SetWindow_0x7d16() {
  WindowReference windowReference;
  windowReference.coords[0] = 393;
  windowReference.coords[1] = 0;
  windowReference.coords[2] = 640;
  windowReference.coords[3] = this->dynamicYBoundary + WeaponWindow_Height_288;
  windowReference.windowAddress = (intptr_t)this;
  this->mainSceneHandler->primarySwitchSingleParam(0x7d16, 3, (intptr_t)&windowReference);
}

__forceinline void GameWindowWeapon::ToggleWindow_0x7d20() {
  this->hideOpenCloseFlag = (this->hideOpenCloseFlag <= 1) ? WindowToggle::Closing : WindowToggle::Hidden;
}

void GameWindowWeapon::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {
  switch (switchParam) {
  case 0x7d11:
    this->InitializeObject_0x7d11(param_2);
    break;
  case 0x7d3b:
    this->DrawObject_0x7d3b();
    break;
  case 0x7d3c:
    this->RunTick_0x7d3c();
    break;
  case 0x7d0c:
    this->CancelOrCloseWindow_0x7d0c();
    break;
  case 0x7d0e: {

    SceneHandler* sceneHandlerLocal;
    InventoryItemStruct* itemStruct;
    WeaponSlotFrame* weaponFrameLocal;
    int32_t charIndexLocal;
    uint32_t flagMasked;
    ActiveCharacter* activeCharLocal;
    GameWindowSpellcast* spellcastWindow;
    int32_t coordDelta;
    InventoryItemSharant* sharantSlotLocal;
    SceneHandler* windowHandlerLocal;
    InventoryItemWeapon* weaponSlotLocal;

    if (param_2 == 0x0) {
      return;
    }

    for (charIndexLocal = 0; TeamCharacterList[charIndexLocal] != nullptr; charIndexLocal = charIndexLocal + 1) {
      if (TeamCharacterList[charIndexLocal]->sceneClassUser == *this->mainSceneHandler->selectedUnits32) {
        break;
      }
    }

    activeCharLocal = TeamCharacterList[charIndexLocal];
    if (activeCharLocal == nullptr) {
      return;
    }

    windowHandlerLocal = this->mainSceneHandler;
    windowHandlerLocal->primarySwitchSingleParam_0x7d17(0, 0x0);

    for (charIndexLocal = 0; charIndexLocal < 44; charIndexLocal++) {
      weaponFrameLocal = WeaponSlotFrames + charIndexLocal;
      coordDelta = (weaponFrameLocal->itemCoord1 - CursorXCoord) + this->staticXBoundary;
      if (coordDelta < 0) {
        coordDelta = -coordDelta;
      }
      if (coordDelta <= weaponFrameLocal->itemFlag1) {
        coordDelta = (this->dynamicYBoundary - CursorYCoord) + weaponFrameLocal->itemCoord2;
        if (coordDelta < 0) {
          coordDelta = -coordDelta;
        }
        if ((coordDelta <= weaponFrameLocal->itemFlag1) && (0 < ((&activeCharLocal->charEquip.equipmentWeapon)[charIndexLocal]).quantity)) {
          if (charIndexLocal < 0x2c) {

            this->mainSceneHandler->primarySwitchSingleParam_0x7d35(ItemStruct12k->itemArray[(&(activeCharLocal->charEquip).equipmentWeapon)[charIndexLocal].typeId].name, 0x1);

            this->mainSceneHandler->primarySwitchSingleParam(0x7d35, (intptr_t)(&(activeCharLocal->charEquip).equipmentWeapon + charIndexLocal), 0x2);
            goto label_process_weapon_mouse_click;
          }
          break;
        }
      }
    }

    this->mainSceneHandler->primarySwitchSingleParam(0x7d35, 0, 0x1);
    this->mainSceneHandler->primarySwitchSingleParam(0x7d35, 0, 0x2);

  label_process_weapon_mouse_click:
    flagMasked = MouseButtonClick & 0x11;
    switch (flagMasked) {
    case 0x1: {
      if (((charIndexLocal < 0x2c) && ((&(activeCharLocal->charEquip).equipmentWeapon)[charIndexLocal].typeId != 0)) && (weaponSlotLocal = &(activeCharLocal->charEquip).equipmentWeapon + charIndexLocal, 0 < (&(activeCharLocal->charEquip).equipmentWeapon)[charIndexLocal].quantity)) {

        memcpy(&this->latestEquipmentItem, weaponSlotLocal, sizeof(InventoryItemWeapon));
        coordDelta = weaponSlotLocal->quantity - this->latestEquipmentItem.quantity;
        weaponSlotLocal->quantity = coordDelta;
        if (coordDelta == 0) {
          (&(activeCharLocal->charEquip).equipmentWeapon)[charIndexLocal].typeId = 0;
#if PATCH_FIX_UNEQUIP_BUG == 1
          memset(&(&(activeCharLocal->charEquip).equipmentWeapon)[charIndexLocal], 0, sizeof(InventoryItemStruct));
#endif
        }
        this->cursorWidthWhileHolding = WeaponSlotFrames[charIndexLocal].itemCoord1 + this->staticXBoundary - CursorXCoord;
        this->cursorHeightWhileHolding = WeaponSlotFrames[charIndexLocal].itemCoord2 + this->dynamicYBoundary - CursorYCoord;
        if (charIndexLocal == 0) {
          charIndexLocal = 6;
          sharantSlotLocal = activeCharLocal->charEquip.equipmentSharants;
          do {
            coordDelta = sharantSlotLocal->quantity;
            while (0 < coordDelta) {
              sceneHandlerLocal = activeCharLocal->sceneClassUser->mainSceneHandler;
              sceneHandlerLocal->primarySwitchSingleParam(0x7d2c, (intptr_t)sharantSlotLocal, 0x0);
              coordDelta = sharantSlotLocal->quantity;
            }
            sharantSlotLocal = sharantSlotLocal + 1;
            charIndexLocal = charIndexLocal + -1;
          } while (charIndexLocal != 0);
        }
        this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, 0x3e, 0x0);
      }
    } break;
    case 0x10: {
      itemStruct = &this->latestEquipmentItem;
      if (0 < this->latestEquipmentItem.quantity) {
        CursorXCoord = CursorXCoord + this->cursorWidthWhileHolding;
        CursorYCoord = CursorYCoord + this->cursorHeightWhileHolding;
        windowHandlerLocal = this->mainSceneHandler;
        windowHandlerLocal->primarySwitchSingleParam_0x7d2e(itemStruct, 0x0);
        CursorXCoord = CursorXCoord - this->cursorWidthWhileHolding;
        CursorYCoord = CursorYCoord - this->cursorHeightWhileHolding;
        if ((itemStruct->quantity != 0) && (this->primarySwitchSingleParam_0x7d2e(itemStruct, 0x1), itemStruct->quantity != 0)) {
          this->mainSceneHandler->primarySwitchSingleParam(0x7d2c, (intptr_t)itemStruct, 0x0);
        }
        itemStruct->quantity = 0;
      }
    } break;
    case 0x11:
      if (0 < this->latestEquipmentItem.quantity) {
        this->mainSceneHandler->primarySwitchSingleParam_0x7d35(ItemStruct12k->itemArray[this->latestEquipmentItem.typeId].name, 0x1);
        this->mainSceneHandler->primarySwitchSingleParam_0x7d35(&this->latestEquipmentItem, 0x2);
        this->mainSceneHandler->primarySwitchSingleParam_0x7d17(10, 0x0);
      }
      break;
    }

    if ((MouseButtonClick & 0x22) == 2) {
      for (charIndexLocal = 0; TeamCharacterList[charIndexLocal] != nullptr; charIndexLocal = charIndexLocal + 1) {
        if ((GameWindowBase*)TeamCharacterList[charIndexLocal]->sceneClassUser == *this->mainSceneHandler->selectedUnits32) {
          break;
        }
      }

      activeCharLocal = TeamCharacterList[charIndexLocal];
      if (activeCharLocal != nullptr) {
        for (charIndexLocal = 6; charIndexLocal < 34; charIndexLocal++) {
          weaponFrameLocal = WeaponSlotFrames + charIndexLocal;
          coordDelta = (weaponFrameLocal->itemCoord1 - CursorXCoord) + this->staticXBoundary;
          if (coordDelta < 0) {
            coordDelta = -coordDelta;
          }
          if (coordDelta <= weaponFrameLocal->itemFlag1) {
            coordDelta = (this->dynamicYBoundary - CursorYCoord) + weaponFrameLocal->itemCoord2;
            if (coordDelta < 0) {
              coordDelta = -coordDelta;
            }
            if (coordDelta <= weaponFrameLocal->itemFlag1) {
              if (0 < (&(activeCharLocal->charEquip).equipmentWeapon)[charIndexLocal].quantity) {
                spellcastWindow = new GameWindowSpellcast(activeCharLocal->sceneClassUser, (InventoryItemSpell*)(&(activeCharLocal->charEquip).equipmentWeapon + charIndexLocal));
                this->mainSceneHandler->StoreAndInitializeObject(spellcastWindow);
              }
              break;
            }
          }
        }

        if ((((WeaponWindow_ActiveSlot_LowerX_456 < CursorXCoord) && (CursorXCoord < WeaponWindow_ActiveSlot_UpperX_574)) && (WeaponWindow_ActiveSlot_LowerY_43 < CursorYCoord)) && (CursorYCoord < WeaponWindow_ActiveSlot_UpperY_71)) {
          activeCharLocal->sceneClassUser->primarySwitchSingleParam_0x7d1c((((CursorXCoord * 4) - WeaponWindow_Grid_OffsetX_1824) / 0x76), 0x0);
        }
      }
    }
  } break;
  case 0x7d2e:
    this->PlaceItemInWindow_0x7d2e(param_2, param_3);
    break;
  case 0x7d16:
    this->SetWindow_0x7d16();
    break;
  case 0x7d20:
    this->ToggleWindow_0x7d20();
    break;
  }
}
