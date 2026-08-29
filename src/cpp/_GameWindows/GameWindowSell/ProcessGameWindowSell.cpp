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

__forceinline void GameWindowSell::HandleMouseInput_0x7d0e() {
  int32_t boundaryIndex;
  int32_t gridColumnIndex;
  ImageVectorWithHeader* spriteFrame;

  for (boundaryIndex = 0; boundaryIndex < 5; boundaryIndex++) {
    if ((((GameWindowSellClickBoxes[boundaryIndex].lowerX <= CursorXCoord) && (CursorXCoord <= GameWindowSellClickBoxes[boundaryIndex].upperX)) && (CursorYCoord >= GameWindowSellClickBoxes[boundaryIndex].lowerY)) && (CursorYCoord <= GameWindowSellClickBoxes[boundaryIndex].upperY)) {
      break;
    }
  }

  this->sprite = nullptr;
  if (((SellWindow_YesButton_LowerX_500 < CursorXCoord) && (CursorXCoord < SellWindow_YesButton_UpperX_547)) && (SellWindow_Buttons_LowerY_17 < CursorYCoord && (CursorYCoord < SellWindow_Buttons_UpperY_30))) {

    spriteFrame = this->actWin7->__InlineGetSolidSpriteFrameForAction(this->button_or_itemIndex, 2);
    this->sprite = spriteFrame;
  }
  if (((SellWindow_NoButton_LowerX_556 < CursorXCoord) && (CursorXCoord < SellWindow_NoButton_UpperX_608)) && (SellWindow_Buttons_LowerY_17 < CursorYCoord && (CursorYCoord < SellWindow_Buttons_UpperY_30))) {

    spriteFrame = this->actWin7->__InlineGetSolidSpriteFrameForAction(this->button_or_itemIndex, 3);
    this->sprite = spriteFrame;
  }
  if (5 <= boundaryIndex) {
    return;
  }
  if (3 < (uint32_t)GameWindowSellClickBoxes[boundaryIndex].switchCommand) {
    return;
  }
  switch (GameWindowSellClickBoxes[boundaryIndex].switchCommand) {
  case 0:
    if ((((MouseButtonClick & 0x11) == 1) && (this->itemIndex != -1)) && (this->itemStructs[this->itemIndex] != nullptr)) {
      GoldAmount = GoldAmount + ((ItemStruct12k->itemArray[this->itemStructs[this->itemIndex]->typeId].price * this->discountFactor) / 100);
      this->itemStructs[this->itemIndex]->quantity = this->itemStructs[this->itemIndex]->quantity + -1;
      this->param1->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x3e, nullptr);
      this->primarySwitchSingleParam_0x7d2f(0x0, 0x0);
      if (this->itemStructs[this->itemIndex] == nullptr) {

        this->itemIndex = this->itemIndex + -1;
        this->primarySwitchSingleParam_0x7d2f(0x0, 0x0);
        return;
      }
    }
    break;
  case 1:
    if ((MouseButtonClick & 0x11) == 1) {
      this->param1->primarySwitchSingleParam_0x7d20(0x3, 0x0);
      return;
    }
    break;
  case 2:
    gridColumnIndex = (CursorXCoord - SellWindow_Grid_OffsetX_176) / SellWindow_Grid_StepX_48;
    if ((this->itemStructs[gridColumnIndex] != nullptr) && ((MouseButtonClick & 0x11) == 1)) {

      this->itemIndex = gridColumnIndex;
      this->primarySwitchSingleParam_0x7d35(this->itemStructs[gridColumnIndex], 0x0);
      return;
    }
    break;
  case 3:
    int32_t gridColumn = (CursorXCoord - SellWindow_Grid_OffsetX_176) / SellWindow_Grid_StepX_48;
    if (this->itemStructs[gridColumn + 9] == nullptr) {
      return;
    }
    if ((MouseButtonClick & 0x11) != 1) {
      return;
    }
    this->itemIndex = gridColumn + 9;
    this->primarySwitchSingleParam_0x7d35(this->itemStructs[this->itemIndex], 0x0);
    break;
  }
}

__forceinline void GameWindowSell::DrawObject_0x7d3b() {
  ImageVectorWithHeader* spriteFrame;
  int32_t itemIndex;
  char* descriptionPtr;

  spriteFrame = this->actWin7->__InlineGetSolidSpriteFrameForAction(this->frame, 0);
  GameWindowRightSide->RenderClippedSprite(-145, 0, spriteFrame, DrawLayer::Layer0xFFF8);

  spriteFrame = this->actWin7->__InlineGetSolidSpriteFrameForAction(this->title, (int32_t)(this->flag1 == 0));
  GameWindowRightSide->RenderClippedSprite(-145, 0, spriteFrame, DrawLayer::Layer0xFFF8);

  for (itemIndex = 0; itemIndex < 0x12; itemIndex = itemIndex + 1) {
    if (this->itemStructs[itemIndex] != nullptr) {
      spriteFrame = Item00Act->__InlineGetSolidSpriteFrameForAction((this->itemStructs[itemIndex])->actOffset, 1);
      GameWindowRightSide->RenderClippedSprite(((itemIndex % 9) * 0x30) + 0x36, ((itemIndex / 9) * 0x42) + 0x44, spriteFrame, DrawLayer::Layer0xFFF9);
    }
  }

  int32_t itemTextPosition = 0xb5;
  descriptionPtr = this->informationText[0];
  while (itemTextPosition < 0xe8) {
    if (*descriptionPtr != '\0') {
      this->PrintSellWindowText(0xf6 - (strlen(descriptionPtr) * 0xb >> 1), itemTextPosition, descriptionPtr, 3);
    }
    itemTextPosition = itemTextPosition + 0x11;
    descriptionPtr = descriptionPtr + 0x50;
  }
  if (this->sprite != nullptr) {
    GameWindowRightSide->RenderClippedSprite(-0x91, 0, this->sprite, DrawLayer::Layer0xFFF9);
  }

  int32_t itemLocation = this->itemIndex;
  if (itemLocation == -1) {
    return;
  }

  CoreActClass* actWin = this->actWin7;
  spriteFrame = actWin->__InlineGetSolidSpriteFrameForAction(this->select, 0);
  GameWindowRightSide->RenderClippedSprite(((itemLocation % 9) * 48) + -337, (itemLocation / 9) * 66, spriteFrame, DrawLayer::Layer0xFFF9);
}

__forceinline void GameWindowSell::DrawText_0x7d35(InventoryItemStruct* itemPtr) {
  char currentChar;
  char text1[40];
  char text2[40];
  int32_t currentLineIndex;
  int32_t integerValue;
  uint32_t textIndex;
  uint32_t formatLen;
  int32_t srcIndex;
  char* srcPtr;
  char* destWalker;

  this->informationText[2][0] = '\0';
  this->informationText[1][0] = '\0';
  this->informationText[0][0] = '\0';

  if (itemPtr != nullptr) {
    srcIndex = 0;
    currentLineIndex = 0;
    srcPtr = ItemStruct12k->itemArray[itemPtr->typeId].description;
    textIndex = 0;
    currentChar = *srcPtr;
    while ((currentChar != '\0' && (currentLineIndex < 2))) {
      currentChar = srcPtr[srcIndex];
      destWalker = (text1 + textIndex);
      *destWalker = currentChar;
      if (currentChar == '|') {
        *destWalker = '\0';
        formatLen = strlen(text1) + 1;
        memcpy(this->informationText[currentLineIndex], text1, formatLen);
        textIndex = 0;
        srcIndex = srcIndex + 1;
        currentLineIndex = currentLineIndex + 1;
      }
      else if ((currentChar == '%') && (' ' < srcPtr[srcIndex + 1])) {
        *destWalker = '\0';
        currentChar = srcPtr[srcIndex + 1];
        if (currentChar >= 'a') {
          integerValue = (&itemPtr->aParameter)[currentChar - (int32_t)'a'] / 100;
        }
        else {
          integerValue = (&itemPtr->aParameter)[currentChar - (int32_t)'A'];
        }
        sprintf(text2, s__s_d, text1, integerValue);
        textIndex = strlen(text2);

        memcpy(text1, text2, textIndex);
        srcIndex = srcIndex + 2;
      }
      else {
        textIndex = textIndex + 1;
        srcIndex = srcIndex + 1;
      }
      currentChar = srcPtr[srcIndex];
    }
    text1[textIndex] = 0;
    memcpy(this->informationText[currentLineIndex], text1, strlen(text1) + 1);
    sprintf(this->informationText[2], s__d_GOLD, ItemStruct12k->itemArray[itemPtr->typeId].price * this->discountFactor / 100);
  }
}

__forceinline void GameWindowSell::RebuildSellableItems_0x7d2f() {
  int32_t uniqueIndex;
  int32_t itemCount;

  memset(this->itemStructs, 0, 18 * sizeof(void*));
  itemCount = 0;

  for (int32_t index = 0; index < 32; index++) {
    if (((0 < ItemInventory[index].quantity) && (index != 0x13)) && (((this->flag1 == 0 && ((ItemInventory[index].equipFlags & ItemFlag::SellAndWindowRelated_0x700) == 0)) || (this->flag1 == 1 && ((ItemInventory[index].equipFlags & ItemFlag::SellAndWindowRelated_0x700) != 0))) && ((ItemInventory[index].equipFlags & ItemFlag::SellRelated_4) != 0))) {
      for (uniqueIndex = 0; uniqueIndex < itemCount; uniqueIndex++) {
        int32_t itemTypeId = ItemInventory[index].typeId;
        if ((itemTypeId == this->itemStructs[uniqueIndex]->typeId) && ((itemTypeId & 2U) != 0)) {
          break;
        }
      }
      if (uniqueIndex == itemCount) {
        this->itemStructs[itemCount] = &ItemInventory[index];
        itemCount = itemCount + 1;
      }
    }
  }

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
    this->HandleMouseInput_0x7d0e();
    break;
  case 0x7d3b:
    this->DrawObject_0x7d3b();
    return;
  case 0x7d35:
    this->DrawText_0x7d35((InventoryItemStruct*)param_2);
    break;
  case 0x7d2f:
    this->RebuildSellableItems_0x7d2f();
    break;
  }
}
