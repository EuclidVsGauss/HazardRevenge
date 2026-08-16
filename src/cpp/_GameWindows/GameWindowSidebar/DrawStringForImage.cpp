#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSidebar.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GameWindowSidebar.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindowSidebar::DrawStringForImage(int32_t offsetX, int32_t offsetY, char* inputString) {
  char currentChar;
  char* specialCharRangePtr;
  ImageVectorWithHeader* imageVector;
  int32_t specialCharIndex;
  int32_t pixelX;
  int32_t frameDataIndex;
  currentChar = *inputString;

  pixelX = 0;
  do {
    if (currentChar == '\0') {
      return;
    }
    currentChar = *inputString;
    if (currentChar == ' ') {
      pixelX = pixelX + 11;
    }
    else {
      specialCharIndex = 0;
      specialCharRangePtr = SidebarWindowSpecialCharacters_c0 + 1;
      do {
        if ((specialCharRangePtr[-1] == currentChar || specialCharRangePtr[-1] < currentChar) && (currentChar <= *specialCharRangePtr)) {
          frameDataIndex = *(int32_t*)(this->sidebarTextLine3 + (specialCharIndex * 4) + 0x4a);

          imageVector = __InlineGetSolidSpriteFrameForAction(frameDataIndex, this->win0act, ((uint32_t)(uint16_t)(int16_t)currentChar - (uint32_t)(uint16_t)(int16_t)SidebarWindowSpecialCharacters_c0[specialCharIndex * 2]));
          GameWindowLeftSidebar->RenderClippedSprite(offsetX + -320 + pixelX, offsetY - 240, imageVector, DrawLayer::Layer0xFFF7);
          pixelX = pixelX + 11;
          break;
        }
        specialCharRangePtr = specialCharRangePtr + 2;
        specialCharIndex = specialCharIndex + 1;
      } while (specialCharRangePtr < &SidebarWindowSpecialCharacters_c0[15]);
    }
    currentChar = inputString[1];
    inputString = inputString + 1;
  } while (true);
}
