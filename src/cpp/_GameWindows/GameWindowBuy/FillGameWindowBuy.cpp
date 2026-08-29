#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowBuy.hpp"
#include "HazardExterns/GameWindowBuy.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"

GameWindowBuy::GameWindowBuy(GameWindowBase* parentWindow, int32_t* items, int32_t buyFactor, int32_t storeType) {
  CoreActClass* actionManager;
  int32_t index;
  int32_t* quantityPtr;
  InventoryItemStruct* inventorySlot;
  int32_t remainingItems;

  this->dialogueWindow = parentWindow;
  actionManager = new CoreActClass(s_win6_act);
  this->actWin6 = actionManager;
  this->discountFactor = buyFactor;

  quantityPtr = &this->frame;
  for (int32_t i = 20; i != 0; i = i + -1) {
    *quantityPtr = -1;
    quantityPtr = quantityPtr + 1;
  }

  index = this->actWin6->GetActionIndexByName(s_frame);
  this->frame = index;
  index = this->actWin6->GetActionIndexByName(s_button);
  this->button = index;
  index = this->actWin6->GetActionIndexByName(s_select);
  this->select = index;
  index = this->actWin6->GetActionIndexByName(s_face);
  this->face = index;
  index = this->actWin6->GetActionIndexByName(s_outline);
  this->outline = index;
  index = this->actWin6->GetActionIndexByName(s_str0);
  this->str0 = index;
  index = this->actWin6->GetActionIndexByName(s_str1);
  this->str1 = index;
  index = this->actWin6->GetActionIndexByName(s_str2);
  this->str2 = index;
  index = this->actWin6->GetActionIndexByName(s_str3);
  this->str3 = index;
  index = this->actWin6->GetActionIndexByName(s_str4);
  this->str4 = index;
  index = this->actWin6->GetActionIndexByName(s_str5);
  this->str5 = index;
  index = this->actWin6->GetActionIndexByName(s_str6);
  this->str6 = index;
  index = this->actWin6->GetActionIndexByName(s_title);
  this->storeType = storeType;
  inventorySlot = this->twentyInventoryItems;
  this->title = index;
  this->inventoryCounter = 0;
  this->buttonHighlightSprite = nullptr;
  this->currentItemText[2][0] = '\0';
  this->currentItemText[1][0] = '\0';
  this->currentItemText[0][0] = '\0';

  memset(inventorySlot, 0, 20 * sizeof(InventoryItemStruct));
  for (remainingItems = 0; remainingItems < 18; remainingItems++) {
    if (items[remainingItems] != 0) {
      this->dialogueWindow->primarySwitchSingleParam(0x7d37, (intptr_t)items[remainingItems], (intptr_t)(inventorySlot + remainingItems));
    }
  }
  if (items[this->inventoryCounter] != 0) {
    primarySwitchSingleParam(0x7d35, (intptr_t)(this->twentyInventoryItems + this->inventoryCounter), 0);
  }
}
