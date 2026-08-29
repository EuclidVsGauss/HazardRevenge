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

__forceinline void GameWindowMerchant::DrawObject_0x7d3b() {
  ImageVectorWithHeader* spriteToDraw;
  ImageVectorWithHeader* buttonSprite;

  spriteToDraw = this->actWin5->__InlineGetSolidSpriteFrameForAction(this->frame, 0);
  GameWindowRightSide->RenderClippedSprite(CONST_0xFFFFFF6F, 0, spriteToDraw, DrawLayer_Layer0xFFF8);

  if (this->selectedButtonIndex != -1) {
    buttonSprite = this->actWin5->__InlineGetSolidSpriteFrameForAction(this->button, this->selectedButtonIndex);
    GameWindowRightSide->RenderClippedSprite(CONST_0xFFFFFF6F, 0x0, buttonSprite, DrawLayer_Layer0xFFF9);
  }
}

__forceinline void GameWindowMerchant::HandleMouseInput_0x7d0e() {

  this->selectedButtonIndex = -1;
  for (int32_t loop = 0; loop < 3; loop++) {
    if ((CursorXCoord >= MerchantWindowClickBoxes_WindowRelated[loop].lowerX) && (CursorXCoord <= MerchantWindowClickBoxes_WindowRelated[loop].upperX) &&
        (CursorYCoord >= MerchantWindowClickBoxes_WindowRelated[loop].lowerY) && (CursorYCoord <= MerchantWindowClickBoxes_WindowRelated[loop].upperY)) {
      this->selectedButtonIndex = MerchantWindowClickBoxes_WindowRelated[loop].short1;
    }
  }

  if ((MouseButtonClick & 0x11) == 1) {
    switch (this->selectedButtonIndex) {
    case 0:
      this->dialogueWindow->primarySwitchSingleParam_0x7d20(1, 0);
      break;
    case 1:
      this->dialogueWindow->primarySwitchSingleParam_0x7d20(2, 0);
      break;
    case 2:
      this->dialogueWindow->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0);
      break;
    }
  }
}

void GameWindowMerchant::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {
  (void)param_2;
  (void)param_3;

  switch (switchParam) {
  case 0x7d3b:
    this->DrawObject_0x7d3b();
    break;

  case 0x7d0e:
    this->HandleMouseInput_0x7d0e();
    break;
  }
}
