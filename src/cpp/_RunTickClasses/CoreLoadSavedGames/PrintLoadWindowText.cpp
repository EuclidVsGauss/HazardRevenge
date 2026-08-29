#include "HazardClasses/CoreLoadSavedGames.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/CoreLoadSavedGames.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void CoreLoadSavedGames::PrintLoadWindowText(int32_t x, int32_t y, char* text, int32_t charIndex) {
  x = x - 320;
  y = y - 240;

  if (*text != '\0') {
    char* textPtr = text;
    while (*textPtr != '\0') {
      char currentChar = *textPtr;
      if (currentChar == ' ') {
        x = x + 11;
      }
      for (int32_t rangeIterator = 0; rangeIterator < 7; rangeIterator++) {
        if (StartEndCharacters___09__AZ__az__[2 * rangeIterator] <= currentChar && currentChar <= StartEndCharacters___09__AZ__az__[(2 * rangeIterator) + 1]) {
          ImageVectorWithHeader* sprite = this->winB_Act->__InlineGetSolidSpriteFrameForAction(
              (&this->frameBegin)[charIndex + rangeIterator], currentChar - StartEndCharacters___09__AZ__az__[rangeIterator * 2]);
          this->windowStruct->RenderClippedSprite(x, y, sprite, DrawLayer::Layer0x1);
          x = x + 11;
          break;
        }
      }
      textPtr++;
    }
  }
}
