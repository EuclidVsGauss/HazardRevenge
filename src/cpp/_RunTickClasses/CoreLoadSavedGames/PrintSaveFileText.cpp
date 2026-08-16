#include "HazardClasses/CoreLoadSavedGames.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/CoreLoadSavedGames.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void CoreLoadSavedGames::PrintSaveFileText(int32_t x, int32_t y, char* text, int32_t charIndex) {
  char currentChar;
  char* textCopy;
  ImageVectorWithHeader* sprite;
  int32_t rangeIterator;

  x = x - 320;
  y = y - 240;
  textCopy = text;

  for (textCopy = text; *textCopy != '\0'; textCopy++) {
    currentChar = *textCopy;
    if (currentChar == ' ') {
      x = x + 11;
    }
    for (rangeIterator = 0; rangeIterator < 7; rangeIterator++) {
      if ((StartEndCharacters___09__AZ__az__[2 * rangeIterator] <= currentChar) && (currentChar <= StartEndCharacters___09__AZ__az__[(2 * rangeIterator) + 1])) {
        sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction((&this->frameBegin)[(charIndex + rangeIterator)], this->winB_Act, (currentChar - StartEndCharacters___09__AZ__az__[rangeIterator * 2]));
        this->windowStruct->RenderClippedSprite(x, y, sprite, DrawLayer::Layer0x1);
        x = x + 11;
        break;
      }
    }
  }
}
