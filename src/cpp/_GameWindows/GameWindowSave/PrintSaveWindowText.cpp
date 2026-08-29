#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSave.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GameWindowSave.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindowSave::PrintSaveWindowText(int32_t currentX, int32_t currentY, char* text, int32_t fontIndex) {
  char currentChar;
  int32_t spriteIdx;
  int32_t rangeIndex;
  ImageVectorWithHeader* spriteFrame;

  currentX -= 0x140;
  currentY -= 0xf0;

  if (text[0] == '\0') {
    return;
  }

  for (int32_t tmp = 0; text[tmp] != '\0'; tmp++) {
    currentChar = text[tmp];
    if (currentChar == ' ') {
      currentX = currentX + 11;
    }
    else {
      for (rangeIndex = 0; rangeIndex < 7; rangeIndex++) {
        if ((SaveWindowSupportedCharacterRanges[2 * rangeIndex] <= currentChar) &&
            (currentChar <= SaveWindowSupportedCharacterRanges[(2 * rangeIndex) + 1])) {
          int currentFrame = (currentChar - SaveWindowSupportedCharacterRanges[rangeIndex * 2]);
          CoreActClass* actObject = this->actWin9;
          spriteIdx = (&this->frame)[fontIndex + rangeIndex];
          spriteFrame = actObject->__InlineGetSolidSpriteFrameForAction(spriteIdx, currentFrame);
          GameWindowRightSide->RenderClippedSprite(currentX, currentY, spriteFrame, DrawLayer::Layer0xFFF9);
          currentX = currentX + 11;
          break;
        }
      }
    }
  }
}
