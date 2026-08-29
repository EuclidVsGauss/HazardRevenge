#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSidebar.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GameWindowSidebar.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindowSidebar::PrintSidebarWindowText(int32_t param_1, int32_t param_2, char* inputStr) {
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
      for (char* charPtr = SidebarWindowSpecialCharacters_c0 + 1; charPtr < (SidebarWindowSpecialCharacters_c0 + 15); charPtr = charPtr + 2) {
        if ((charPtr[-1] <= currentChar) && (currentChar <= *charPtr)) {
          CoreActClass* actObject = this->win0act;
          frameIndex = (&this->actStr0)[charIndex];
          sprite = actObject->__InlineGetSolidSpriteFrameForAction(frameIndex, currentChar - SidebarWindowSpecialCharacters_c0[charIndex * 2]);
          GameWindowLeftSidebar->RenderClippedSprite(param_1 + -0x140 + totalWidth, param_2 - 0xf0, sprite, DrawLayer::Layer0xFFF7);
          totalWidth = totalWidth + 0xb;
          break;
        }
        charIndex++;
      }
    }
  }
}
