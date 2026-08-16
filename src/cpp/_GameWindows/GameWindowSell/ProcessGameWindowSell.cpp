#include <stdio.h>
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/GameWindowSell.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardEnums/ItemFlag.hpp"
#include "HazardExterns/GameWindowSell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ClickableRectangle2.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ItemReferenceStruct.hpp"

const int32_t SellWindow_YesButton_LowerX_500 = 500;
const int32_t SellWindow_YesButton_UpperX_547 = 547;
const int32_t SellWindow_NoButton_LowerX_556 = 556;
const int32_t SellWindow_NoButton_UpperX_608 = 608;
const int32_t SellWindow_Buttons_LowerY_17 = 17;
const int32_t SellWindow_Buttons_UpperY_30 = 30;
const int32_t SellWindow_Grid_OffsetX_176 = 176;
const int32_t SellWindow_Grid_StepX_48 = 48;

__forceinline void GameWindowSell::Case_0x7d0e() {

  int32_t mouseButtonState;
  ClickableRectangle2* screenBoundaryIterator;

  int32_t boundaryIndex;

  ImageVectorWithHeader* spriteFrame;

  boundaryIndex = 0;
  screenBoundaryIterator = GameWindowSellClickBoxes;
  do {
    if ((((screenBoundaryIterator->lowerX == CursorXCoord || screenBoundaryIterator->lowerX < CursorXCoord) && (CursorXCoord <= screenBoundaryIterator->upperX)) && (screenBoundaryIterator->lowerY <= CursorYCoord)) && (CursorYCoord <= screenBoundaryIterator->upperY)) {
      break;
    }
    screenBoundaryIterator = screenBoundaryIterator + 1;
    boundaryIndex = boundaryIndex + 1;
  } while (screenBoundaryIterator < GameWindowSellClickBoxes + 5);

  this->sprite = nullptr;
  if (((SellWindow_YesButton_LowerX_500 < CursorXCoord) && (CursorXCoord < SellWindow_YesButton_UpperX_547)) && (SellWindow_Buttons_LowerY_17 < CursorYCoord && (CursorYCoord < SellWindow_Buttons_UpperY_30))) {

    spriteFrame = __InlineGetSolidSpriteFrameForAction(this->button_or_itemIndex, this->actWin7, 2);
    this->sprite = spriteFrame;
  }
  if (((SellWindow_NoButton_LowerX_556 < CursorXCoord) && (CursorXCoord < SellWindow_NoButton_UpperX_608)) && (SellWindow_Buttons_LowerY_17 < CursorYCoord && (CursorYCoord < SellWindow_Buttons_UpperY_30))) {

    spriteFrame = __InlineGetSolidSpriteFrameForAction(this->button_or_itemIndex, this->actWin7, 3);
    this->sprite = spriteFrame;
  }
  if (4 < boundaryIndex) {
    return;
  }
  if (3 < (uint32_t)GameWindowSellClickBoxes[boundaryIndex].WindowRelatedOuter_0x14) {
    return;
  }
  mouseButtonState = MouseButtonClick;
  switch (GameWindowSellClickBoxes[boundaryIndex].WindowRelatedOuter_0x14) {
  case 0:
    if ((((mouseButtonState & 0x11) == 1) && (this->itemIndex != -1)) && (this->itemStructs[this->itemIndex] != nullptr)) {
      GoldAmount = GoldAmount + ((ItemStruct12k->itemArray[this->itemStructs[this->itemIndex]->typeId].price * this->param3) / 100);
      this->itemStructs[this->itemIndex]->quantity = this->itemStructs[this->itemIndex]->quantity + -1;
      this->param1->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x3e, nullptr);
      this->primarySwitchSingleParam(0x7d2f, 0x0, 0x0);
      if (this->itemStructs[this->itemIndex] == nullptr) {

        this->itemIndex = this->itemIndex + -1;
        this->primarySwitchSingleParam(0x7d2f, 0x0, 0x0);
        return;
      }
    }
    break;
  case 1:
    mouseButtonState = MouseButtonClick;
    if ((mouseButtonState & 0x11) == 1) {
      this->param1->primarySwitchSingleParam(0x7d20, 0x3, 0x0);
      return;
    }
    break;
  case 2:
    boundaryIndex = (CursorXCoord - SellWindow_Grid_OffsetX_176) / SellWindow_Grid_StepX_48;
    if ((this->itemStructs[boundaryIndex] != nullptr) && ((mouseButtonState & 0x11) == 1)) {

      this->itemIndex = boundaryIndex;
      this->primarySwitchSingleParam_0x7d35(this->itemStructs[boundaryIndex], 0x0);
      return;
    }
    break;
  case 3:
    int32_t gridColumn = (CursorXCoord - SellWindow_Grid_OffsetX_176) / SellWindow_Grid_StepX_48;
    if (this->itemStructs[gridColumn] == nullptr) {
      return;
    }
    if ((mouseButtonState & 0x11) != 1) {
      return;
    }
    this->itemIndex = gridColumn + 9;
    this->primarySwitchSingleParam_0x7d35(this->itemStructs[this->itemIndex], 0x0);
    break;
  }
}

__forceinline void GameWindowSell::Case_0x7d3b() {
  char currentChar;

  uint32_t negativeStrLenMinusOne;
  ImageVectorWithHeader* spriteFrame;
  int32_t columnOrYOffset;
  char* descriptionPtr;
  char* strWalker;
  InventoryItemStruct** inventoryItemPtr;

  spriteFrame = __InlineGetSolidSpriteFrameForAction(this->frame, this->actWin7, 0);
  GameWindowRightSide->RenderClippedSprite(-145, 0, spriteFrame, DrawLayer::Layer0xFFF8);

  spriteFrame = __InlineGetSolidSpriteFrameForAction(this->title, this->actWin7, (int32_t)(this->flag1 == 0));
  GameWindowRightSide->RenderClippedSprite(-145, 0, spriteFrame, DrawLayer::Layer0xFFF8);

  inventoryItemPtr = this->itemStructs;
  columnOrYOffset = 0;
  do {
    if (*inventoryItemPtr != nullptr) {

      spriteFrame = __InlineGetSolidSpriteFrameForAction((*inventoryItemPtr)->actOffset, Item00Act, 1);
      GameWindowRightSide->RenderClippedSprite(((columnOrYOffset % 9) * 0x30) + 0x36, ((columnOrYOffset / 9) * 0x42) + 0x44, spriteFrame, DrawLayer::Layer0xFFF9);
    }
    columnOrYOffset = columnOrYOffset + 1;
    inventoryItemPtr = inventoryItemPtr + 1;
  } while (columnOrYOffset < 0x12);

  columnOrYOffset = 0xb5;
  descriptionPtr = this->char3;
  do {
    if (*descriptionPtr != '\0') {
      negativeStrLenMinusOne = 0xffffffff;
      strWalker = descriptionPtr;
      do {
        if (negativeStrLenMinusOne == 0) {
          break;
        }
        negativeStrLenMinusOne = negativeStrLenMinusOne - 1;
        currentChar = *strWalker;
        strWalker = strWalker + 1;
      } while (currentChar != '\0');
      this->SomeNestedFunction(0xf6 - ((~negativeStrLenMinusOne - 1) * 0xb >> 1), columnOrYOffset, descriptionPtr, 3);
    }
    columnOrYOffset = columnOrYOffset + 0x11;
    descriptionPtr = descriptionPtr + 0x50;
  } while (columnOrYOffset < 0xe8);
  if (this->sprite != nullptr) {
    GameWindowRightSide->RenderClippedSprite(-0x91, 0, this->sprite, DrawLayer::Layer0xFFF9);
  }
  columnOrYOffset = this->itemIndex;
  if (columnOrYOffset == -1) {
    return;
  }

  spriteFrame = __InlineGetSolidSpriteFrameForAction(this->select, this->actWin7, 0);
  GameWindowRightSide->RenderClippedSprite(((columnOrYOffset % 9) * 48) + -337, (columnOrYOffset / 9) * 66, spriteFrame, DrawLayer::Layer0xFFF9);
}

__forceinline void GameWindowSell::Case_0x7d35(intptr_t param_2) {
  char currentChar;

  char* destBuffer;
  char text1[80];
  char text2[80];
  InventoryItemStruct* itemPtr;
  int32_t segmentCount;
  int32_t integerValue;
  uint32_t segmentLen;
  uint32_t formatLen;
  int32_t srcIndex;
  char* srcPtr;
  char* destWalker;

  srcIndex = 0;
  destBuffer = this->char3;
  this->loadTrackGoldStringInterpolation[0] = '\0';
  this->char2[0] = '\0';
  *destBuffer = '\0';
  itemPtr = (InventoryItemStruct*)param_2;
  if (itemPtr != nullptr) {
    segmentCount = 0;
    srcPtr = ItemStruct12k->itemArray[itemPtr->typeId].description;
    segmentLen = 0;
    currentChar = *srcPtr;
    while ((currentChar != '\0' && (segmentCount < 2))) {
      currentChar = srcPtr[srcIndex];
      destWalker = (char*)(text1 + segmentLen);
      *destWalker = currentChar;
      if (currentChar == '|') {
        *destWalker = '\0';
        formatLen = strlen(text1) + 1;
        memcpy(destBuffer, text1, formatLen);
        segmentLen = 0;
        srcIndex = srcIndex + 1;
        segmentCount = segmentCount + 1;
        destBuffer = destBuffer + 0x50;
      }
      else if ((currentChar == '%') && (' ' < srcPtr[srcIndex + 1])) {
        *destWalker = '\0';
        currentChar = srcPtr[srcIndex + 1];
        if (currentChar < 'a') {
          integerValue = ((int32_t*)itemPtr)[currentChar - 60];
        }
        else {
          integerValue = ((int32_t*)itemPtr)[currentChar - 92] / 100;
        }
        sprintf(text2, s__s_d, text1, integerValue);
        segmentLen = strlen(text2);
        srcIndex = srcIndex + 2;
        memcpy(text1, text2, segmentLen);
      }
      else {
        segmentLen = segmentLen + 1;
        srcIndex = srcIndex + 1;
      }
      currentChar = srcPtr[srcIndex];
    }
    text1[segmentLen] = 0;
    segmentLen = strlen(text1) + 1;
    srcPtr = this->char3 + (segmentCount * 0x50);
    memcpy(srcPtr, text1, segmentLen);
    sprintf(this->loadTrackGoldStringInterpolation, s__d_GOLD, (ItemStruct12k->itemArray[itemPtr->typeId].price * this->param3) / 100);
    return;
  }
}

__forceinline void GameWindowSell::Case_0x7d2f() {
  int32_t uniqueIndex;
  uint32_t equipFlags;
  InventoryItemStruct** arrayWalker;
  int32_t itemCount;
  InventoryItemStruct* currentInventoryItem;
  InventoryItemStruct** targetSlot;

  targetSlot = this->itemStructs;

  memset(targetSlot, 0, 18 * sizeof(void*));
  itemCount = 0;
  currentInventoryItem = ItemInventory;
  do {
    if (((0 < currentInventoryItem->quantity) && (currentInventoryItem != ItemInventory + 0x13)) && (((this->flag1 == 0 && (equipFlags = currentInventoryItem->equipFlags, (equipFlags & ItemFlag::SellAndWindowRelated_0x700) == 0)) || (this->flag1 == 1 && (equipFlags = currentInventoryItem->equipFlags, (equipFlags & ItemFlag::SellAndWindowRelated_0x700) != 0))) && ((equipFlags & ItemFlag::SellRelated_4) != 0))) {
      uniqueIndex = 0;
      if (0 < itemCount) {
        arrayWalker = this->itemStructs;
        do {
          if ((currentInventoryItem->typeId == (*arrayWalker)->typeId) && ((currentInventoryItem->typeId & 2U) != 0)) {
            break;
          }
          uniqueIndex = uniqueIndex + 1;
          arrayWalker = arrayWalker + 1;
        } while (uniqueIndex < itemCount);
      }
      if (uniqueIndex == itemCount) {
        itemCount = itemCount + 1;
        *targetSlot = currentInventoryItem;
        targetSlot = targetSlot + 1;
      }
    }
    currentInventoryItem = currentInventoryItem + 1;
  } while (currentInventoryItem < ItemInventory + 32);
  itemCount = this->itemIndex;
  if (itemCount == -1) {
    return;
  }
  this->primarySwitchSingleParam_0x7d35(this->itemStructs[itemCount], 0x0);
}

void GameWindowSell::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {
  (void)param_3;

  switch (switchParam) {
  case 0x7d0e:
    Case_0x7d0e();
    break;
  case 0x7d3b:
    Case_0x7d3b();
    return;
  case 0x7d35:
    Case_0x7d35(param_2);
    break;
  case 0x7d2f:
    Case_0x7d2f();
    break;
  }
}
