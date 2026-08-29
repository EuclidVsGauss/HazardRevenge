#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowSell.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GameWindowSell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindowSell::PrintSellWindowText(int32_t param_1, int32_t param_2, char* inputStr, int32_t param_4) {
  char currentChar;
  int32_t frameIndex;
  ImageVectorWithHeader* sprite;
  int32_t charIndex;

  int32_t totalWidth = 0;
  for (int32_t tmp = 0; inputStr[tmp] != '\0'; tmp++) {
    currentChar = inputStr[tmp];
    if (currentChar == ' ') {
      totalWidth = totalWidth + 11;
    }
    else {

      charIndex = 0;
      for (char* charPtr = SellWindowSpecialCharacters_s___09__AZ__az__ + 1; charPtr < (SellWindowSpecialCharacters_s___09__AZ__az__ + 15); charPtr = charPtr + 2) {
        if ((charPtr[-1] <= currentChar) && (currentChar <= *charPtr)) {
          CoreActClass* actObject = this->actWin7;
          frameIndex = (&this->frame)[param_4 + charIndex];
          sprite = actObject->__InlineGetSolidSpriteFrameForAction(frameIndex, currentChar - SellWindowSpecialCharacters_s___09__AZ__az__[charIndex * 2]);
          GameWindowRightSide->RenderClippedSprite(param_1 + -0x140 + totalWidth, param_2 - 0xf0, sprite, DrawLayer::Layer0xFFF9);
          totalWidth = totalWidth + 0xb;
          break;
        }
        charIndex++;
      }
    }
  }
}
