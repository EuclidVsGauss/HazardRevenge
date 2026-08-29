#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowBuy.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GameWindowBuy.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindowBuy::PrintBuyWindowText(int32_t widthOffset, int32_t heightOffset, char* textString, int32_t startingCommandIndex) {
  ImageVectorWithHeader* sprite;
  int32_t charIndex;
  int32_t textOffsetX;
  char currentChar;

  textOffsetX = 0;
  for (int32_t tmp = 0; textString[tmp] != '\0'; tmp++) {
    currentChar = textString[tmp];
    if (currentChar == ' ') {
      textOffsetX = textOffsetX + 0xb;
    }
    else {
      charIndex = 0;
      for (char* charPtr = BuyWindowSpecialCharacters_s___09__AZ__az__ + 1; charPtr < (BuyWindowSpecialCharacters_s___09__AZ__az__ + 15); charPtr = charPtr + 2) {
        if ((charPtr[-1] <= currentChar) && (currentChar <= *charPtr)) {
          CoreActClass* actObject = this->actWin6;
          sprite = actObject->__InlineGetSolidSpriteFrameForAction((&this->frame)[startingCommandIndex + charIndex], (currentChar - (BuyWindowSpecialCharacters_s___09__AZ__az__[charIndex * 2])));
          GameWindowRightSide->RenderClippedSprite(widthOffset + -0x140 + textOffsetX, heightOffset - 0xf0, sprite, DrawLayer::Layer0xFFF9);
          textOffsetX = textOffsetX + 0xb;
          break;
        }
        charIndex++;
      }
    }
  }
}
