#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowInventory.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GameWindowInventory.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindowInventory::PrintInventoryWindowText(int32_t initialOffsetX, int32_t initialOffsetY, char* textString, int32_t param_4) {
  char currentChar;
  ImageVectorWithHeader* frameToRender;
  int32_t charIndex;
  int32_t currentOffsetX;

  currentOffsetX = 0;
  for (int32_t index = 0; textString[index] != '\0'; index++) {
    currentChar = textString[index];
    if (currentChar == ' ') {
      currentOffsetX = currentOffsetX + 0xb;
    }
    else {
      charIndex = 0;
      for (char* charPtr = InventoryWindowSpecialCharacters + 1; charPtr < (InventoryWindowSpecialCharacters + 15); charPtr = charPtr + 2) {
        if (charPtr[-1] <= currentChar && currentChar <= *charPtr) {
          CoreActClass* actObject = this->win3actPointer;
          frameToRender = actObject->__InlineGetSolidSpriteFrameForAction((&this->actFrame)[param_4 + charIndex], currentChar - InventoryWindowSpecialCharacters[charIndex * 2]);
          GameWindowRightSide->RenderClippedSprite(initialOffsetX + -0x140 + currentOffsetX, initialOffsetY - 0xf0, frameToRender, DrawLayer::Layer0xFFF7);
          currentOffsetX = currentOffsetX + 0xb;
          break;
        }
        charIndex++;
      }
    }
  }
}
