#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowBuy.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GameWindowBuy.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindowBuy::PrintBuyText(int32_t widthOffset, int32_t heightOffset, char* textString, int32_t startingCommandIndex) {
  char* rangePtr;
  ImageVectorWithHeader* sprite;
  int32_t charIndex;
  int32_t cursorX;
  char currentChar;

  currentChar = *textString;
  cursorX = 0;
  do {
    if (currentChar == '\0') {
      return;
    }
    currentChar = *textString;
    if (currentChar == ' ') {
      cursorX = cursorX + 0xb;
    }
    else {
      charIndex = 0;
      rangePtr = BuyWindowSpecialCharacters_s___09__AZ__az__ + 1;
      do {
        if ((rangePtr[-1] == currentChar || rangePtr[-1] < currentChar) && (currentChar <= *rangePtr)) {

          sprite = __InlineGetSolidSpriteFrameForAction(this->unusedActCommands[startingCommandIndex + charIndex + -13], this->actWin6, ((uint32_t)(uint16_t)(int16_t)currentChar - (uint32_t)(uint16_t)(int16_t)(BuyWindowSpecialCharacters_s___09__AZ__az__[charIndex * 2])));
          GameWindowRightSide->RenderClippedSprite(widthOffset + -0x140 + cursorX, heightOffset - 0xf0, sprite, DrawLayer::Layer0xFFF9);
          cursorX = cursorX + 0xb;
          break;
        }
        rangePtr = rangePtr + 2;
        charIndex = charIndex + 1;
      } while (rangePtr < BuyWindowSpecialCharacters_s___09__AZ__az__ + 15);
    }
    currentChar = textString[1];
    textString = textString + 1;
  } while (true);
}
