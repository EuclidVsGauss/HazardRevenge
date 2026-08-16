#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSave.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GameWindowSave.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindowSave::DrawText(int32_t currentX, int32_t currentY, char* text, int32_t fontIndex) {
  char currentChar;
  int32_t spriteIdx;
  int32_t rangeIndex;
  ImageVectorWithHeader* spriteFrame;
  char* textCopy;

  currentX = currentX - 0x140;
  currentY = currentY - 0xf0;

  for (textCopy = text; *textCopy != '\0'; textCopy++) {
    currentChar = *textCopy;
    if (currentChar == ' ') {
      currentX = currentX + 0xb;
    }
    else {
      for (rangeIndex = 0; rangeIndex < 7; rangeIndex++) {
        if ((SaveWindowSupportedCharacterRanges[2 * rangeIndex] <= currentChar) && (currentChar <= SaveWindowSupportedCharacterRanges[(2 * rangeIndex) + 1])) {
          int currentFrame = (currentChar - SaveWindowSupportedCharacterRanges[rangeIndex * 2]);
          spriteIdx = (&this->frame)[fontIndex + rangeIndex];
          spriteFrame = __InlineGetSolidSpriteFrameForAction(spriteIdx, this->actWin9, currentFrame);
          GameWindowRightSide->RenderClippedSprite(currentX, currentY, spriteFrame, DrawLayer::Layer0xFFF9);
          currentX = currentX + 0xb;
          break;
        }
      }
    }
  }
}
