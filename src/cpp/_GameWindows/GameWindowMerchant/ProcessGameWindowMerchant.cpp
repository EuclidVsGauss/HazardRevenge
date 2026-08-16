#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/GameWindowMerchant.hpp"
#include "HazardExterns/GameWindowMerchant.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ClickableRectangle1.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

const int32_t CONST_0xFFFFFF6F = -0x91;
const int32_t DrawLayer_Layer0xFFF8 = 0xfff8;
const int32_t DrawLayer_Layer0xFFF9 = 0xfff9;

__forceinline void Case_0x7d3b(GameWindowMerchant* _this) {

  ImageVectorWithHeader* spriteToDraw;

  spriteToDraw = GameWindowBase::__InlineGetSolidSpriteFrameForAction(_this->frame, _this->actWin5, 0);
  GameWindowRightSide->RenderClippedSprite(CONST_0xFFFFFF6F, 0, spriteToDraw, DrawLayer_Layer0xFFF8);

  if (_this->selectedButtonIndex != -1) {

    spriteToDraw = GameWindowBase::__InlineGetSolidSpriteFrameForAction(_this->button, _this->actWin5, _this->selectedButtonIndex);
  }

  GameWindowRightSide->RenderClippedSprite(CONST_0xFFFFFF6F, 0x0, spriteToDraw, DrawLayer_Layer0xFFF9);
}

__forceinline void Case_0x7d0e(GameWindowMerchant* _this) {
  int32_t contentIndex;
  int32_t frameIndex;
  ClickableRectangle1* boxPtr;

  _this->selectedButtonIndex = -1;
  contentIndex = CursorXCoord;
  frameIndex = CursorYCoord;
  boxPtr = MerchantWindowClickBoxes_WindowRelated;

  do {
    if ((contentIndex >= boxPtr->lowerX) && (contentIndex <= boxPtr->upperX) &&
        (frameIndex >= boxPtr->lowerY) && (frameIndex <= boxPtr->upperY)) {
      _this->selectedButtonIndex = *(int32_t*)&boxPtr->short1;
      contentIndex = CursorXCoord;
      frameIndex = CursorYCoord;
    }
    boxPtr++;
  } while (boxPtr < MerchantWindowClickBoxes_WindowRelated + 3);

  if ((MouseButtonClick & 0x11) == 1) {
    contentIndex = _this->selectedButtonIndex;
    switch (contentIndex) {
    case 0:
      _this->dialogueWindow->primarySwitchSingleParam(0x7d20, 1, 0);
      break;
    case 1:
      _this->dialogueWindow->primarySwitchSingleParam(0x7d20, 2, 0);
      break;
    case 2:
      _this->dialogueWindow->primarySwitchSingleParam(0x7d0c, (intptr_t)_this, 0);
      break;
    }
  }
}

void GameWindowMerchant::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {
  (void)param_2;
  (void)param_3;

  switch (switchParam) {
  case 0x7d3b:
    Case_0x7d3b(this);
    break;

  case 0x7d0e:
    Case_0x7d0e(this);
    break;
  }
}
