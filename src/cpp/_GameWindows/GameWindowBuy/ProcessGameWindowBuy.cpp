#include <stdio.h>
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowBuy.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GameWindowBuy.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/ClickableRectangle2.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ItemReferenceStruct.hpp"

const int32_t BuyWindow_YesButton_LowerX_500 = 500;
const int32_t BuyWindow_YesButton_UpperX_547 = 547;
const int32_t BuyWindow_YesButton_LowerY_17 = 17;
const int32_t BuyWindow_YesButton_UpperY_30 = 30;

const int32_t BuyWindow_NoButton_LowerX_556 = 556;
const int32_t BuyWindow_NoButton_UpperX_608 = 608;
const int32_t BuyWindow_NoButton_LowerY_17 = 17;
const int32_t BuyWindow_NoButton_UpperY_30 = 30;

const int32_t BuyWindow_Grid_OffsetX_176 = 176;
const int32_t BuyWindow_Grid_StepX_48 = 48;

void GameWindowBuy::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {

  (void)param_3;

  switch (switchParam) {
  case 0x7d0e:
    this->DrawClickableObjects_0x7d0e();
    return;

  case 0x7d35:
    this->DrawText_0x7d35((InventoryItemStruct*)param_2);
    return;

  case 0x7d3b:
    this->DrawPortraitsEtc_0x7d3b();
    return;

  default:
    return;
  }
}

__forceinline void GameWindowBuy::DrawClickableObjects_0x7d0e() {

  int32_t clickableIndex;
  int32_t gridColumnIndex;

  for (clickableIndex = 0; clickableIndex < 4; clickableIndex++) {
    if (
        (GameWindowBuyClickBoxes[clickableIndex].lowerX <= CursorXCoord) &&
        (CursorXCoord <= GameWindowBuyClickBoxes[clickableIndex].upperX) &&
        (CursorYCoord >= GameWindowBuyClickBoxes[clickableIndex].lowerY) &&
        (CursorYCoord <= GameWindowBuyClickBoxes[clickableIndex].upperY)) {
      break;
    }
  };

  this->buttonHighlightSprite = nullptr;

  if (__InlineCursorInsideBox(BuyWindow_YesButton_LowerX_500, BuyWindow_YesButton_LowerY_17, BuyWindow_YesButton_UpperX_547, BuyWindow_YesButton_UpperY_30)) {
    this->buttonHighlightSprite = this->actWin6->__InlineGetSolidSpriteFrameForAction(this->button, 2);
  }

  if (__InlineCursorInsideBox(BuyWindow_NoButton_LowerX_556, BuyWindow_NoButton_LowerY_17, BuyWindow_NoButton_UpperX_608, BuyWindow_NoButton_UpperY_30)) {
    this->buttonHighlightSprite = this->actWin6->__InlineGetSolidSpriteFrameForAction(this->button, 3);
  }

  if ((clickableIndex < 4) && ((MouseButtonClick & 0x11) == 1)) {
    switch (GameWindowBuyClickBoxes[clickableIndex].switchCommand) {
    case 0:
      clickableIndex = this->inventoryCounter;
      if ((0 < this->twentyInventoryItems[clickableIndex].quantity) && ((int32_t)GoldAmount >= (ItemStruct12k->itemArray[this->twentyInventoryItems[clickableIndex].typeId].price * this->discountFactor) / 100)) {
        this->twentyInventoryItems[clickableIndex].quantity = 1;
        this->dialogueWindow->primarySwitchSingleParam_0x7d2c((this->twentyInventoryItems + this->inventoryCounter), 0x0);
        this->twentyInventoryItems[this->inventoryCounter].quantity = 1;

        int32_t itemPrice = ItemStruct12k->itemArray[this->twentyInventoryItems[this->inventoryCounter].typeId].price;
        clickableIndex = (itemPrice * this->discountFactor) / 100;
        GoldAmount = GoldAmount - clickableIndex;

        this->dialogueWindow->primarySwitchSingleParam(0x7d0a, 0x3e, 0x0);
        return;
      }
      this->dialogueWindow->primarySwitchSingleParam(0x7d0a, 0x1a, 0x0);
      return;

    case 1:
      this->dialogueWindow->primarySwitchSingleParam_0x7d20(0x3, 0x0);
      return;

    case 2:
      gridColumnIndex = (CursorXCoord - BuyWindow_Grid_OffsetX_176) / BuyWindow_Grid_StepX_48;
      if (0 < this->twentyInventoryItems[gridColumnIndex].quantity) {
        this->inventoryCounter = gridColumnIndex;
        this->primarySwitchSingleParam(0x7d35, (intptr_t)(this->twentyInventoryItems + this->inventoryCounter), 0x0);
        return;
      }
      break;

    case 3:
      gridColumnIndex = (CursorXCoord - BuyWindow_Grid_OffsetX_176) / BuyWindow_Grid_StepX_48;
      if (0 < this->twentyInventoryItems[gridColumnIndex + 9].quantity) {
        this->inventoryCounter = gridColumnIndex + 9;
        this->primarySwitchSingleParam(0x7d35, (intptr_t)(this->twentyInventoryItems + this->inventoryCounter), 0x0);
      }
    default:
      return;
    }
  }
}

__forceinline void GameWindowBuy::DrawText_0x7d35(InventoryItemStruct* itemPtr) {
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

  this->currentItemText[2][0] = '\0';
  this->currentItemText[1][0] = '\0';
  this->currentItemText[0][0] = '\0';

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
        memcpy(this->currentItemText[currentLineIndex], text1, formatLen);
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
    memcpy(this->currentItemText[currentLineIndex], text1, strlen(text1) + 1);
    sprintf(this->currentItemText[2], s__d_GOLD, ItemStruct12k->itemArray[itemPtr->typeId].price * this->discountFactor / 100);
  }
}

__forceinline void GameWindowBuy::DrawPortraitsEtc_0x7d3b() {
  ImageVectorWithHeader* sprite;
  int32_t inventoryIndex;
  int32_t drawFaceOffset;
  ActiveCharacter** param_1ac;

  sprite = this->actWin6->__InlineGetSolidSpriteFrameForAction(this->frame, 0);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, sprite, DrawLayer::Layer0xFFF8);

  sprite = this->actWin6->__InlineGetSolidSpriteFrameForAction(this->title, this->storeType == 0);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, sprite, DrawLayer::Layer0xFFF8);

  for (inventoryIndex = 0; inventoryIndex < 18; inventoryIndex = inventoryIndex + 1) {
    if (0 < this->twentyInventoryItems[inventoryIndex].quantity) {
      sprite = Item00Act->__InlineGetSolidSpriteFrameForAction(ItemStruct12k->itemArray[this->twentyInventoryItems[inventoryIndex].typeId].actOffset, 1);
      GameWindowRightSide->RenderClippedSprite(((inventoryIndex % 9) * 0x30) + 0x36, ((inventoryIndex / 9) * 0x42) + 0x44, sprite, DrawLayer::Layer0xFFF9);
    }
  }

  param_1ac = TeamCharacterList;
  if (*param_1ac != nullptr) {
    drawFaceOffset = 0xb;
    for (param_1ac = TeamCharacterList; *param_1ac != nullptr; param_1ac++) {
      int32_t characterId = (*param_1ac)->characterId;
      int32_t itemTypeId = this->twentyInventoryItems[this->inventoryCounter].typeId;
      int32_t itemEquipFlags = ItemStruct12k->itemArray[itemTypeId].equipFlags;
      int32_t bitIndex = characterId + 0xb;
      int32_t frameCount = ((itemEquipFlags >> bitIndex) & 1U) + ((uint16_t)((*param_1ac)->characterId) << 1);

      sprite = this->actWin6->__InlineGetSolidSpriteFrameForAction(this->face, frameCount);
      GameWindowRightSide->RenderClippedSprite(drawFaceOffset, 0xe3, sprite, DrawLayer::Layer0xFFF9);

      sprite = this->actWin6->__InlineGetSolidSpriteFrameForAction(this->outline, 0);
      GameWindowRightSide->RenderClippedSprite(drawFaceOffset, 0xe3, sprite, DrawLayer::Layer0xFFF9);
      drawFaceOffset = drawFaceOffset + 0x30;
    }
  }

  for (int32_t i = 0; i < 3; i++) {
    char* text = this->currentItemText[i];
    if (*text != '\0') {
      size_t len = strlen(text);
      this->PrintBuyWindowText(0xf6 - ((len * 0xb) / 2), 181 + (i * 17), text, 5);
    }
  }

  sprite = this->actWin6->__InlineGetSolidSpriteFrameForAction(this->button, 4);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, sprite, DrawLayer::Layer0xFFF9);

  if (this->buttonHighlightSprite != nullptr) {
    GameWindowRightSide->RenderClippedSprite(-145, 0, this->buttonHighlightSprite, DrawLayer::Layer0xFFF9);
  }

  sprite = this->actWin6->__InlineGetSolidSpriteFrameForAction(this->select, 0);
  int32_t itemCol = this->inventoryCounter % 9;
  int32_t itemRow = this->inventoryCounter / 9;
  GameWindowRightSide->RenderClippedSprite((itemCol * 48) + -337, itemRow * 66, sprite, DrawLayer::Layer0xFFF9);
}
