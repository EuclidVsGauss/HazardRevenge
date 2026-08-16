#include <stdio.h>
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowInventory.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardEnums/ItemFlag.hpp"
#include "HazardEnums/WindowToggle.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ItemReferenceStruct.hpp"
#include "HazardStructs/WindowReference.hpp"

const int32_t InventoryWindow_Grid1_LowerX_457 = 457;
const int32_t InventoryWindow_Grid1_UpperX_617 = 617;
const int32_t InventoryWindow_Grid1_LowerY_304 = 304;
const int32_t InventoryWindow_Grid1_UpperY_432 = 432;

const int32_t InventoryWindow_Grid2_LowerX_167 = 167;
const int32_t InventoryWindow_Grid2_UpperX_449 = 449;
const int32_t InventoryWindow_Grid2_LowerY_303 = 303;
const int32_t InventoryWindow_Grid2_UpperY_437 = 437;

const int32_t InventoryWindow_Trash_LowerX_585 = 585;
const int32_t InventoryWindow_Trash_LowerY_400 = 400;

__forceinline void GameWindowInventory::Case_0x7d11(intptr_t param_2) {
  this->mainSceneHandler = (SceneHandler*)param_2;
  this->primarySwitchSingleParam_SetWindow_0x7d16(0x0, nullptr);
}

__forceinline void GameWindowInventory::Case_0x7d3b() {
  int32_t inventoryLoopIndexX;
  uint32_t stringLengthCounter;

  int32_t posXOffset;
  ImageVectorWithHeader* spriteFrame;
  int32_t* textLinePtr;
  int32_t* charIteratorPtr;
  char currentCharValue;

  int32_t param_1;
  InventoryItemStruct* currentItemPointer;
  InventoryItemStruct* comparisonItemPointer;

  spriteFrame = __InlineGetSolidSpriteFrameForAction(this->actFrame, this->win3actPointer, 0);
  GameWindowRightSide->RenderClippedSprite(this->staticXBoundary + -0x91, this->dynamicYBoundary, spriteFrame, DrawLayer::Layer0xFFF6);
  param_1 = 0;
  currentItemPointer = ItemInventory;
  do {
    if (0 < currentItemPointer->quantity) {

      spriteFrame = __InlineGetSolidSpriteFrameForAction(currentItemPointer->actOffset, Item00Act, 1);
      inventoryLoopIndexX = (param_1 % 5) * 0x20;
      GameWindowRightSide->RenderClippedSprite(inventoryLoopIndexX + 0x147 + this->staticXBoundary, (((param_1 / 5) + 10) * 0x20) + this->dynamicYBoundary, spriteFrame, DrawLayer::Layer0xFFF7);
      if (1 < currentItemPointer->quantity) {

        spriteFrame = __InlineGetSolidSpriteFrameForAction(this->actNumber, this->win3actPointer, currentItemPointer->quantity);
        GameWindowRightSide->RenderClippedSprite(inventoryLoopIndexX + 0x10 + this->staticXBoundary, ((param_1 / 5) * 0x20) + 0x5a + this->dynamicYBoundary, spriteFrame, DrawLayer::Layer0xFFF7);
      }
    }
    currentItemPointer = currentItemPointer + 1;
    inventoryLoopIndexX = param_1 + 1;
    param_1 = inventoryLoopIndexX;
  } while (currentItemPointer < 20 + ItemInventory);
  param_1 = 0;
  if (inventoryLoopIndexX < 32) {
    comparisonItemPointer = ItemInventory + inventoryLoopIndexX;
    do {
      if (0 < comparisonItemPointer->quantity) {

        spriteFrame = __InlineGetSolidSpriteFrameForAction(comparisonItemPointer->actOffset, Item00Act, 1);
        inventoryLoopIndexX = (param_1 / 6) * 67;
        posXOffset = (param_1 % 6) * 47;
        GameWindowRightSide->RenderClippedSprite(posXOffset + 0x35 + this->staticXBoundary, this->dynamicYBoundary + 0x14e + inventoryLoopIndexX, spriteFrame, DrawLayer::Layer0xFFF7);
        if (1 < comparisonItemPointer->quantity) {

          spriteFrame = __InlineGetSolidSpriteFrameForAction(this->actNumber, this->win3actPointer, comparisonItemPointer->quantity);
          GameWindowRightSide->RenderClippedSprite(posXOffset + -0x101 + this->staticXBoundary, this->dynamicYBoundary + 0x74 + inventoryLoopIndexX, spriteFrame, DrawLayer::Layer0xFFF7);
        }
      }
      comparisonItemPointer = comparisonItemPointer + 1;
      param_1 = param_1 + 1;
    } while (comparisonItemPointer < ItemInventory + 32);
  }
  inventoryLoopIndexX = 0;
  textLinePtr = (int32_t*)this->textLine1;
  do {
    if (*(char*)textLinePtr != '\0') {
      stringLengthCounter = 0xffffffff;
      charIteratorPtr = textLinePtr;
      do {
        if (stringLengthCounter == 0) {
          break;
        }
        stringLengthCounter = stringLengthCounter - 1;
        currentCharValue = *(char*)charIteratorPtr;
        charIteratorPtr = (int32_t*)((intptr_t)charIteratorPtr + 1);
      } while (currentCharValue != '\0');
      this->PresumablyDisplayMultiLineText((this->staticXBoundary - ((~stringLengthCounter - 1) * 0xb >> 1)) + 246, this->dynamicYBoundary + 443 + inventoryLoopIndexX, (char*)textLinePtr, 2);
    }
    inventoryLoopIndexX = inventoryLoopIndexX + 12;
    textLinePtr = textLinePtr + 20;
  } while (inventoryLoopIndexX < 24);
  if ((this->itemHeldInCursor).quantity == 0) {
    return;
  }

  spriteFrame = __InlineGetSolidSpriteFrameForAction((this->itemHeldInCursor).actOffset, Item00Act, 1);
  (GameWindowLeftSidebar->RenderClippedSprite)(this->cursorWidthWhileHolding + CursorXCoord, this->cursorHeightWhileHolding + CursorYCoord, spriteFrame, DrawLayer::Layer0xFFF8);

  spriteFrame = __InlineGetSolidSpriteFrameForAction((this->itemHeldInCursor).actOffset, Item00Act, 1);
  GameWindowRightSide->RenderClippedSprite(this->cursorWidthWhileHolding + -145 + CursorXCoord, this->cursorHeightWhileHolding + CursorYCoord, spriteFrame, DrawLayer::Layer0xFFF8);
  if ((this->itemHeldInCursor).quantity <= 1) {
    return;
  }

  spriteFrame = __InlineGetSolidSpriteFrameForAction((this->itemHeldInCursor).actOffset, Item00Act, 1);
  (GameWindowLeftSidebar->RenderClippedSprite)(this->cursorWidthWhileHolding + CursorXCoord, this->cursorHeightWhileHolding + CursorYCoord, spriteFrame, DrawLayer::Layer0xFFF8);

  spriteFrame = __InlineGetSolidSpriteFrameForAction(this->actNumber, this->win3actPointer, (this->itemHeldInCursor).quantity);
  GameWindowRightSide->RenderClippedSprite(this->cursorWidthWhileHolding + -455 + CursorXCoord, this->cursorHeightWhileHolding + -230 + CursorYCoord, spriteFrame, DrawLayer::Layer0xFFF8);
}

__forceinline void GameWindowInventory::Case_0x7d3c() {
  int32_t updatedYBoundary;
  uint32_t adjustedYValue;

  switch (this->hideOpenCloseFlag) {
  case 2: {
    this->primarySwitchSingleParam_SetWindow_0x7d16(0x0, nullptr);
    updatedYBoundary = this->dynamicYBoundary + 16;
    if (0xc0 < updatedYBoundary) {
      updatedYBoundary = 0xc0;
    }
    this->dynamicYBoundary = updatedYBoundary;
    if (updatedYBoundary == 0xc0) {
      this->mainSceneHandler->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(this, 0x0);
      return;
    }
    return;
  }
  case 0: {
    adjustedYValue = this->dynamicYBoundary - 0x10;
    adjustedYValue = adjustedYValue & (((int32_t)adjustedYValue < 0) - 1);
    this->dynamicYBoundary = adjustedYValue;
    if (adjustedYValue == 0) {
      this->hideOpenCloseFlag = WindowToggle::Opening;
    }
    this->primarySwitchSingleParam_SetWindow_0x7d16(0x0, nullptr);
    return;
  }
  }
}

__forceinline void GameWindowInventory::Case_0x7d16() {
  WindowReference windowReference;

  windowReference.coords[1] = this->dynamicYBoundary + 288;
  windowReference.coords[0] = 145;
  windowReference.coords[2] = 640;
  windowReference.coords[3] = 480;
  windowReference.windowAddress = (intptr_t)this;
  this->mainSceneHandler->primarySwitchSingleParam_SetWindow_0x7d16(4, &windowReference);
}

__forceinline void GameWindowInventory::Case_0x7d20() {
  this->hideOpenCloseFlag = (this->hideOpenCloseFlag <= 1) ? WindowToggle::Closing : WindowToggle::Hidden;
}

__forceinline void GameWindowInventory::Case_0x7d0c() {
  this->hideOpenCloseFlag = WindowToggle::Closing;
}

__forceinline void GameWindowInventory::Case_0x7d0e(intptr_t param_2, intptr_t param_3) {

  InventoryItemStruct* targetItemPointer;
  GameWindowBase** selectedUnitsPointer;
  GameWindowBase* firstSelectedUnit;
  int32_t inventoryIndex;
  uint32_t mouseClickMask;
  int32_t adjustedYCoord;
  int32_t adjustedXCoord;
  InventoryItemStruct* sourceItemPointer;

  InventoryItemStruct* destinationItemPointer;

  (void)param_3;

  inventoryIndex = -1;
  if (param_2 != 0x0) {
    this->mainSceneHandler->primarySwitchSingleParam_0x7d17(0, 0x0);
    adjustedXCoord = this->staticXBoundary;
    if (((adjustedXCoord + InventoryWindow_Grid1_LowerX_457 < CursorXCoord) && (CursorXCoord < adjustedXCoord + InventoryWindow_Grid1_UpperX_617)) && (adjustedYCoord = this->dynamicYBoundary, adjustedYCoord + InventoryWindow_Grid1_LowerY_304 <= CursorYCoord && (CursorYCoord < adjustedYCoord + InventoryWindow_Grid1_UpperY_432))) {
      inventoryIndex = (CursorYCoord - adjustedYCoord) + -InventoryWindow_Grid1_LowerY_304;
      adjustedYCoord = (CursorXCoord - adjustedXCoord) + -InventoryWindow_Grid1_LowerX_457;
      inventoryIndex = (((int32_t)(inventoryIndex + (inventoryIndex >> 0x1f & 0x1fU)) >> 5) * 5) + ((int32_t)(adjustedYCoord + (adjustedYCoord >> 0x1f & 0x1fU)) >> 5);
    }
    if (((adjustedXCoord + InventoryWindow_Grid2_LowerX_167 < CursorXCoord) && (CursorXCoord < adjustedXCoord + InventoryWindow_Grid2_UpperX_449)) && (adjustedYCoord = this->dynamicYBoundary, adjustedYCoord + InventoryWindow_Grid2_LowerY_303 <= CursorYCoord && (CursorYCoord < adjustedYCoord + InventoryWindow_Grid2_UpperY_437))) {
      inventoryIndex = (((CursorXCoord - adjustedXCoord) + -InventoryWindow_Grid2_LowerX_167) / 0x2f) + 0x14 + ((((CursorYCoord - adjustedYCoord) + -InventoryWindow_Grid2_LowerY_303) / 0x43) * 6);
    }
    if ((inventoryIndex < 0) || (targetItemPointer = ItemInventory + inventoryIndex, ItemInventory[inventoryIndex].quantity <= 0)) {
      this->mainSceneHandler->primarySwitchSingleParam(0x7d35, (intptr_t)nullptr, 0x1);
      targetItemPointer = nullptr;
    }
    else {
      this->mainSceneHandler->primarySwitchSingleParam(0x7d35, (intptr_t)ItemStruct12k->itemArray[ItemInventory[inventoryIndex].typeId].name, 0x1);
    }

    this->mainSceneHandler->primarySwitchSingleParam(0x7d35, (intptr_t)targetItemPointer, 0x2);
    if (((((MouseButtonClick & 0x22) == 2) && (0 <= inventoryIndex)) && (inventoryIndex != 0x13)) && (0 < ItemInventory[inventoryIndex].quantity)) {
      selectedUnitsPointer = this->mainSceneHandler->selectedUnits32;
      firstSelectedUnit = *selectedUnitsPointer;
      if (((firstSelectedUnit != nullptr) && (selectedUnitsPointer[1] == nullptr)) && ((ItemInventory[inventoryIndex].equipFlags & ItemFlag::SellAndWindowRelated_0x700) == 0 && (firstSelectedUnit->primarySwitchSingleParam(0x7d1b, ItemInventory[inventoryIndex].typeId, 0x0), (*(byte*)&ItemInventory[inventoryIndex].equipFlags & ItemFlag::AlsoWindow_0x10) != 0))) {
        ItemInventory[inventoryIndex].quantity = ItemInventory[inventoryIndex].quantity + -1;
      }
    }

    mouseClickMask = MouseButtonClick & 0x11;
    switch (mouseClickMask) {
    case 0x11: {
      if (0 < (this->itemHeldInCursor).quantity) {
        this->mainSceneHandler->primarySwitchSingleParam(0x7d35, (intptr_t)ItemStruct12k->itemArray[(this->itemHeldInCursor).typeId].name, 0x1);
        this->mainSceneHandler->primarySwitchSingleParam(0x7d35, (intptr_t)&this->itemHeldInCursor, 0x2);
        this->mainSceneHandler->primarySwitchSingleParam_0x7d17(10, 0x0);
        return;
      }
      break;
    }
    case 0x10: {
      targetItemPointer = &this->itemHeldInCursor;
      if (((this->itemHeldInCursor).quantity != 0) && (this->mainSceneHandler->primarySwitchSingleParam_0x7d2e(targetItemPointer, 0x0), targetItemPointer->quantity != 0)) {
        this->primarySwitchSingleParam_0x7d2e(targetItemPointer, 0x0);
        return;
      }
      break;
    }
    case 1: {
      inventoryIndex = this->staticXBoundary;
      if (((inventoryIndex + InventoryWindow_Grid1_LowerX_457 < CursorXCoord) && (CursorXCoord < inventoryIndex + InventoryWindow_Grid1_UpperX_617)) && (adjustedXCoord = this->dynamicYBoundary, adjustedXCoord + InventoryWindow_Grid1_LowerY_304 <= CursorYCoord && (CursorYCoord < adjustedXCoord + 0x1ac))) {
        inventoryIndex = (((CursorXCoord - inventoryIndex) + -InventoryWindow_Grid1_LowerX_457) / 0x1f) + ((((CursorYCoord - adjustedXCoord) + -InventoryWindow_Grid1_LowerY_304) / 0x1f) * 5);
        targetItemPointer = ItemInventory + inventoryIndex;
        if ((0 < ItemInventory[inventoryIndex].quantity) && (inventoryIndex != 0x13)) {
          sourceItemPointer = targetItemPointer;
          destinationItemPointer = &this->itemHeldInCursor;
          memcpy(destinationItemPointer, sourceItemPointer, sizeof(InventoryItemStruct));
          targetItemPointer->quantity = targetItemPointer->quantity - (this->itemHeldInCursor).quantity;
          this->cursorWidthWhileHolding = (((inventoryIndex % 5) * 31) - CursorXCoord) + 471 + this->staticXBoundary;
          this->cursorHeightWhileHolding = (((inventoryIndex / 5) * 0x1f) - CursorYCoord) + 0x140 + this->dynamicYBoundary;
          this->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x3e, nullptr);
        }
      }
      inventoryIndex = this->staticXBoundary;
      if ((((inventoryIndex + InventoryWindow_Grid2_LowerX_167 < CursorXCoord) && (CursorXCoord < inventoryIndex + InventoryWindow_Grid2_UpperX_449)) && (adjustedXCoord = this->dynamicYBoundary, adjustedXCoord + InventoryWindow_Grid2_LowerY_303 <= CursorYCoord)) && (CursorYCoord < adjustedXCoord + InventoryWindow_Grid2_UpperY_437)) {
        inventoryIndex = (((CursorXCoord - inventoryIndex) + -InventoryWindow_Grid2_LowerX_167) / 0x2f) + ((((CursorYCoord - adjustedXCoord) + -InventoryWindow_Grid2_LowerY_303) / 0x43) * 6);
        targetItemPointer = ItemInventory + inventoryIndex + 0x14;
        if (0 < ItemInventory[inventoryIndex + 0x14].quantity) {
          sourceItemPointer = targetItemPointer;
          destinationItemPointer = &this->itemHeldInCursor;

          memcpy(destinationItemPointer, sourceItemPointer, sizeof(InventoryItemStruct));
          targetItemPointer->quantity = targetItemPointer->quantity - (this->itemHeldInCursor).quantity;
          this->cursorWidthWhileHolding = (((inventoryIndex % 6) * 0x2f) - CursorXCoord) + 0xc6 + this->staticXBoundary;
          this->cursorHeightWhileHolding = (((inventoryIndex / 6) * 0x43) - CursorYCoord) + 0x14e + this->dynamicYBoundary;
          this->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x3e, nullptr);
          return;
        }
      }
    } break;
    }
  }
}

__forceinline void GameWindowInventory::Case_0x7d2e(InventoryItemStruct* param2AsItem) {
  uint32_t equipFlagsValue;
  int32_t inventoryGridIndex;
  int32_t currentSlotIndex;
  InventoryItemStruct* targetSlotPointer;
  InventoryItemStruct* sourceItemPointer;

  if (((
           (this->staticXBoundary + InventoryWindow_Trash_LowerX_585 < CursorXCoord) &&
           (CursorXCoord < this->staticXBoundary + InventoryWindow_Grid1_UpperX_617)) &&
       (this->dynamicYBoundary + InventoryWindow_Trash_LowerY_400 < CursorYCoord)) &&
      (CursorYCoord < this->dynamicYBoundary + InventoryWindow_Grid1_UpperY_432 &&
       ((*(byte*)&param2AsItem->equipFlags & 8) != 0))) {
    param2AsItem->quantity = 0;
  }
  equipFlagsValue = param2AsItem->equipFlags;
  inventoryGridIndex = this->staticXBoundary;
  if ((equipFlagsValue & 0x20) == 0) {
    if ((
            (inventoryGridIndex + InventoryWindow_Grid1_LowerX_457 < CursorXCoord) &&
            (CursorXCoord < inventoryGridIndex + InventoryWindow_Grid1_UpperX_617)) &&
        (currentSlotIndex = this->dynamicYBoundary, currentSlotIndex + InventoryWindow_Grid1_LowerY_304 <= CursorYCoord &&
                                                        (CursorYCoord < currentSlotIndex + InventoryWindow_Grid1_UpperY_432 &&
                                                         (currentSlotIndex = (CursorYCoord - currentSlotIndex) + -InventoryWindow_Grid1_LowerY_304,
                                                          inventoryGridIndex = (((CursorXCoord - inventoryGridIndex) + -InventoryWindow_Grid1_LowerX_457) / 0x1f) + (((int32_t)(currentSlotIndex + (currentSlotIndex >> 0x1f & 0x1fU)) >> 5) * 5),
                                                          inventoryGridIndex < 0x14)))) {
      currentSlotIndex = ItemInventory[inventoryGridIndex].quantity;
      targetSlotPointer = ItemInventory + inventoryGridIndex;
      if (currentSlotIndex == 0) {
      label_copy_to_empty_slot:
        sourceItemPointer = param2AsItem;

        memcpy(targetSlotPointer, sourceItemPointer, sizeof(InventoryItemStruct));
      }
      else {
        if (((ItemInventory[inventoryGridIndex].typeId != param2AsItem->typeId) || ((equipFlagsValue & 2) == 0)) || (9 < currentSlotIndex + param2AsItem->quantity)) {
          goto label_play_item_drop_sound;
        }
      label_stack_item_quantity:
        if (currentSlotIndex == 0) {
          goto label_copy_to_empty_slot;
        }
        targetSlotPointer->quantity = currentSlotIndex + param2AsItem->quantity;
      }
      param2AsItem->quantity = 0;
    }
  }
  else if (((inventoryGridIndex + InventoryWindow_Grid2_LowerX_167 < CursorXCoord) && (CursorXCoord < inventoryGridIndex + InventoryWindow_Grid2_UpperX_449)) && (currentSlotIndex = this->dynamicYBoundary, currentSlotIndex + InventoryWindow_Grid2_LowerY_303 <= CursorYCoord && (CursorYCoord < currentSlotIndex + InventoryWindow_Grid2_UpperY_437 && (inventoryGridIndex = (((CursorXCoord - inventoryGridIndex) + -InventoryWindow_Grid2_LowerX_167) / 47) + ((((CursorYCoord - currentSlotIndex) + -InventoryWindow_Grid2_LowerY_303) / 67) * 6), inventoryGridIndex < 0xc)))) {
    currentSlotIndex = ItemInventory[inventoryGridIndex + 0x14].quantity;
    targetSlotPointer = ItemInventory + inventoryGridIndex + 0x14;
    if (currentSlotIndex == 0) {
      goto label_copy_to_empty_slot;
    }
    if (((ItemInventory[inventoryGridIndex + 20].typeId == param2AsItem->typeId) && ((equipFlagsValue & 2) != 0)) && (currentSlotIndex + param2AsItem->quantity < 9)) {
      goto label_stack_item_quantity;
    }
  }
label_play_item_drop_sound:
  this->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x3e, nullptr);
  if (param2AsItem->quantity != 0) {
    this->mainSceneHandler->primarySwitchSingleParam_0x7d2c(param2AsItem, 0x0);
    return;
  }
}

__forceinline void GameWindowInventory::Case_0x7d35(intptr_t param_2) {
  int32_t stringParsingIndex;
  int32_t* lineBufferPtr;
  int32_t lineCounter;
  char* descriptionStringPtr;
  uint32_t lineBufferIndex;
  char currentCharValue;
  char* lineBufferStart;
  char text1[80];
  char text2[80];
  int32_t statValue;
  InventoryItemStruct* param2AsItem = (InventoryItemStruct*)param_2;

  stringParsingIndex = 0;
  lineBufferPtr = (int32_t*)this->textLine1;
  *(char*)this->textLine2 = 0;
  *(char*)lineBufferPtr = 0;
  if (param_2 != 0x0) {
    lineCounter = 0;
    descriptionStringPtr = ItemStruct12k->itemArray[param2AsItem->typeId].description;
    lineBufferIndex = 0;
    currentCharValue = *descriptionStringPtr;
    while ((currentCharValue != '\0' && (lineCounter < 2))) {
      currentCharValue = descriptionStringPtr[stringParsingIndex];
      lineBufferStart = (text1 + lineBufferIndex);
      *lineBufferStart = currentCharValue;
      if (currentCharValue == '|') {
        *lineBufferStart = '\0';
        strcpy((char*)lineBufferPtr, text1);
        lineBufferIndex = 0;
        stringParsingIndex = stringParsingIndex + 1;
        lineCounter = lineCounter + 1;
        lineBufferPtr = (int32_t*)((char*)lineBufferPtr + 0x14);
      }
      else if ((currentCharValue == '%') && (' ' < descriptionStringPtr[stringParsingIndex + 1])) {
        *lineBufferStart = '\0';
        currentCharValue = descriptionStringPtr[stringParsingIndex + 1];
        if (currentCharValue < 'a') {
          statValue = ((uint32_t*)param_2)[currentCharValue - (0xf0 / 4)];
        }
        else {
          statValue = ((uint32_t*)param_2)[currentCharValue - (0x170 / 4)] / 100;
        }
        sprintf(text2, s__s_d, text1, statValue);
        strcpy(text1, text2);
        lineBufferIndex = strlen(text1);
        stringParsingIndex = stringParsingIndex + 2;
      }
      else {
        lineBufferIndex = lineBufferIndex + 1;
        stringParsingIndex = stringParsingIndex + 1;
      }
      currentCharValue = descriptionStringPtr[stringParsingIndex];
    }
    text1[lineBufferIndex] = 0;
    strcpy(this->textLine1 + (lineCounter * 80), text1);
  }
}

void GameWindowInventory::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {
  InventoryItemStruct* param2AsItem = (InventoryItemStruct*)param_2;

  switch (switchParam) {
  case 0x7d11:
    Case_0x7d11(param_2);
    return;
  case 0x7d3b:
    Case_0x7d3b();
    return;
  case 0x7d3c:
    Case_0x7d3c();
    return;
  case 0x7d16:
    Case_0x7d16();
    return;
  case 0x7d20:
    Case_0x7d20();
    return;
  case 0x7d0c:
    Case_0x7d0c();
    return;
  case 0x7d0e:
    Case_0x7d0e(param_2, param_3);
    break;
  case 0x7d2e:
    Case_0x7d2e(param2AsItem);
    break;
  case 0x7d35:
    Case_0x7d35(param_2);
    break;
  }
}
