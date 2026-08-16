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
    DrawClickableObjects_0x7d0e();
    return;

  case 0x7d35:
    DrawText_0x7d35((InventoryItemStruct*)param_2);
    return;

  case 0x7d3b:
    DrawPortraitsEtc_0x7d3b();
    return;

  default:
    return;
  }
}

__forceinline void GameWindowBuy::DrawClickableObjects_0x7d0e() {

  ClickableRectangle2* clickableRectangle;

  int32_t clickableIndex;

  for (clickableIndex = 0; clickableIndex < 4; clickableIndex++) {
    clickableRectangle = &GameWindowBuyClickBoxes[clickableIndex];
    if (
        (clickableRectangle->lowerX <= CursorXCoord) &&
        (CursorXCoord <= clickableRectangle->upperX) &&
        (CursorYCoord >= clickableRectangle->lowerY) &&
        (CursorYCoord <= clickableRectangle->upperY)) {
      break;
    }
  };

  this->buttonHighlightSprite = nullptr;

  if (__InlineCursorInsideBox(BuyWindow_YesButton_LowerX_500, BuyWindow_YesButton_LowerY_17, BuyWindow_YesButton_UpperX_547, BuyWindow_YesButton_UpperY_30)) {
    this->buttonHighlightSprite = __InlineGetSolidSpriteFrameForAction(this->button, this->actWin6, 2);
  }

  if (__InlineCursorInsideBox(BuyWindow_NoButton_LowerX_556, BuyWindow_NoButton_LowerY_17, BuyWindow_NoButton_UpperX_608, BuyWindow_NoButton_UpperY_30)) {
    this->buttonHighlightSprite = __InlineGetSolidSpriteFrameForAction(this->button, this->actWin6, 3);
  }

  if ((clickableIndex < 4) && ((MouseButtonClick & 0x11) == 1)) {
    switch (GameWindowBuyClickBoxes[clickableIndex].WindowRelatedOuter_0x14) {
    case 0:
      clickableIndex = this->inventoryCounter;
      if ((0 < this->twentyInventoryItems[clickableIndex].quantity) && ((int32_t)GoldAmount >= (ItemStruct12k->itemArray[this->twentyInventoryItems[clickableIndex].typeId].price * this->buyFactor) / 100)) {
        this->twentyInventoryItems[clickableIndex].quantity = 1;
        this->dialogueWindow->primarySwitchSingleParam_0x7d2c((this->twentyInventoryItems + this->inventoryCounter), 0x0);
        this->twentyInventoryItems[this->inventoryCounter].quantity = 1;

        int32_t itemPrice = ItemStruct12k->itemArray[this->twentyInventoryItems[this->inventoryCounter].typeId].price;
        clickableIndex = (itemPrice * this->buyFactor) / 100;
        GoldAmount = GoldAmount - clickableIndex;

        this->dialogueWindow->primarySwitchSingleParam(0x7d0a, 0x3e, 0x0);
        return;
      }
      this->dialogueWindow->primarySwitchSingleParam(0x7d0a, 0x1a, 0x0);
      return;

    case 1:
      this->dialogueWindow->primarySwitchSingleParam(0x7d20, 0x3, 0x0);
      return;

    case 2:
      clickableIndex = (CursorXCoord - BuyWindow_Grid_OffsetX_176) / BuyWindow_Grid_StepX_48;
      if (0 < this->twentyInventoryItems[clickableIndex].quantity) {
        this->inventoryCounter = clickableIndex;
        this->primarySwitchSingleParam(0x7d35, (intptr_t)(this->twentyInventoryItems + clickableIndex), 0x0);
      }
      break;

    case 3:
      clickableIndex = (CursorXCoord - BuyWindow_Grid_OffsetX_176) / BuyWindow_Grid_StepX_48;
      if (0 < this->twentyInventoryItems[clickableIndex + 9].quantity) {
        this->inventoryCounter = clickableIndex + 9;
        this->primarySwitchSingleParam(0x7d35, (intptr_t)(this->twentyInventoryItems + clickableIndex + 9), 0x0);
      }
    default:
      return;
    }
  }
}

__forceinline void GameWindowBuy::DrawText_0x7d35(InventoryItemStruct* item) {
  char lineBuffer[80];
  char tempBuffer[80];
  char* currentDest;
  char* description;
  int32_t lineCount;

  this->currentItemText[2][0] = '\0';
  this->currentItemText[1][0] = '\0';
  this->currentItemText[0][0] = '\0';

  if (item == nullptr) {
    return;
  }

  int32_t typeId = item->typeId;
  ItemReferenceStruct* entry = &ItemStruct12k->itemArray[typeId];
  description = entry->description;
  currentDest = &this->currentItemText[0][0];
  lineCount = 0;

  int32_t lineIndex = 0;
  int32_t charIndex = 0;

  while (description[lineIndex] != '\0' && lineCount < 2) {
    char c = description[lineIndex];
    lineBuffer[charIndex] = c;

    if (c == '|') {

      lineBuffer[charIndex] = '\0';
      strcpy(currentDest, lineBuffer);
      charIndex = 0;
      lineCount++;
      currentDest += 0x50;
      lineIndex++;
    }
    else if (c == '%' && description[lineIndex + 1] > ' ') {

      lineBuffer[charIndex] = '\0';
      char formatChar = description[lineIndex + 1];
      int32_t value;

      if (formatChar >= 'a') {
        value = ((int32_t*)item)[formatChar - 92] / 100;
      }
      else {
        value = ((int32_t*)item)[formatChar - 60];
      }

      sprintf(tempBuffer, "%s%d", lineBuffer, value);

      strcpy(lineBuffer, tempBuffer);
      charIndex = strlen(tempBuffer);
      lineIndex += 2;
    }
    else {

      charIndex++;
      lineIndex++;
    }
  }

  lineBuffer[charIndex] = '\0';
  strcpy(currentDest, lineBuffer);

  int32_t price = ItemStruct12k->itemArray[typeId].price;
  int32_t goldValue = (price * this->buyFactor) / 100;
  sprintf(this->currentItemText[2], "%d GOLD", goldValue);
}

__forceinline void GameWindowBuy::DrawPortraitsEtc_0x7d3b() {
  InventoryItemStruct* item;
  ImageVectorWithHeader* sprite;
  int32_t inventoryIndex;
  int32_t drawFaceOffset;
  ActiveCharacter** param_1ac;

  sprite = __InlineGetSolidSpriteFrameForAction(this->frame, this->actWin6, 0);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, sprite, DrawLayer::Layer0xFFF8);

  sprite = __InlineGetSolidSpriteFrameForAction(this->title, this->actWin6, this->storeType == 0);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, sprite, DrawLayer::Layer0xFFF8);

  for (inventoryIndex = 0; inventoryIndex < 18; inventoryIndex = inventoryIndex + 1) {
    item = &this->twentyInventoryItems[inventoryIndex];
    if (0 < item->quantity) {
      sprite = __InlineGetSolidSpriteFrameForAction(ItemStruct12k->itemArray[item->typeId].actOffset, Item00Act, 1);
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

      sprite = __InlineGetSolidSpriteFrameForAction(this->face, this->actWin6, frameCount);
      GameWindowRightSide->RenderClippedSprite(drawFaceOffset, 0xe3, sprite, DrawLayer::Layer0xFFF9);

      sprite = __InlineGetSolidSpriteFrameForAction(this->outline, this->actWin6, 0);
      GameWindowRightSide->RenderClippedSprite(drawFaceOffset, 0xe3, sprite, DrawLayer::Layer0xFFF9);
      drawFaceOffset = drawFaceOffset + 0x30;
    }
  }

  for (int32_t i = 0; i < 3; i++) {
    char* text = this->currentItemText[i];
    if (*text != '\0') {
      size_t len = strlen(text);
      this->PrintBuyText(0xf6 - ((len * 0xb) / 2), 181 + (i * 17), text, 5);
    }
  }

  sprite = __InlineGetSolidSpriteFrameForAction(this->button, this->actWin6, 4);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, sprite, DrawLayer::Layer0xFFF9);

  if (this->buttonHighlightSprite != nullptr) {
    GameWindowRightSide->RenderClippedSprite(-145, 0, this->buttonHighlightSprite, DrawLayer::Layer0xFFF9);
  }

  sprite = __InlineGetSolidSpriteFrameForAction(this->select, this->actWin6, 0);
  int32_t itemCol = this->inventoryCounter % 9;
  int32_t itemRow = this->inventoryCounter / 9;
  GameWindowRightSide->RenderClippedSprite((itemCol * 48) + -337, itemRow * 66, sprite, DrawLayer::Layer0xFFF9);
}
