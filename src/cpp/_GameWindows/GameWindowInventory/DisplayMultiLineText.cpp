#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowInventory.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GameWindowInventory.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindowInventory::PresumablyDisplayMultiLineText(int32_t param_1, int32_t param_2, char* param_3, int32_t param_4) {
  char currentChar;
  char* charEntry;
  ImageVectorWithHeader* frameToRender;
  int32_t charIndex;
  int32_t xOffset;

  currentChar = *param_3;
  xOffset = 0;

  do {
    if (currentChar == '\0') {
      return;
    }
    currentChar = *param_3;
    if (currentChar == ' ') {
      xOffset = xOffset + 0xb;
    }
    else {
      charIndex = 0;
      charEntry = InventoryWindowSpecialCharacters + 1;
      do {
        if ((charEntry[-1] == currentChar || charEntry[-1] < currentChar) && (currentChar <= *charEntry)) {
          frameToRender = __InlineGetSolidSpriteFrameForAction((&this->actFrame)[param_4 + charIndex], this->win3actPointer, currentChar - InventoryWindowSpecialCharacters[charIndex * 2]);
          GameWindowRightSide->RenderClippedSprite(param_1 + -0x140 + xOffset, param_2 - 0xf0, frameToRender, DrawLayer::Layer0xFFF7);
          xOffset = xOffset + 0xb;
          break;
        }
        charEntry = charEntry + 2;
        charIndex = charIndex + 1;
      } while (charEntry < InventoryWindowSpecialCharacters + 15);
    }
    currentChar = param_3[1];
    param_3 = param_3 + 1;
  } while (true);
}
