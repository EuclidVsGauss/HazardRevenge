#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowSell.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GameWindowSell.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void GameWindowSell::SomeNestedFunction(int32_t param_1, int32_t param_2, char* param_3, int32_t param_4) {
  char currentChar;
  int32_t frameIndex;
  int32_t numberFrames;
  char* pcCharRange;
  ImageVectorWithHeader* sprite;
  int32_t rangeStartOffset;

  uint16_t relativeCharValue;
  ActContent* txtContent;
  int32_t rangeIndex;
  int32_t* frameArray;

  char* inputStr = param_3;
  int32_t totalWidth = 0;
  for (; *inputStr != 0; inputStr++) {
    currentChar = *inputStr;
    if (currentChar == ' ') {
      totalWidth = totalWidth + 11;
    }
    else {
      rangeStartOffset = 0;
      for (pcCharRange = SellWindowSpecialCharacters_s___09__AZ__az__ + 1; pcCharRange < 14 + SellWindowSpecialCharacters_s___09__AZ__az__; pcCharRange = pcCharRange + 2) {
        if (pcCharRange[-1] <= currentChar && currentChar <= *pcCharRange) {
          rangeIndex = param_4 + rangeStartOffset;
          frameArray = (&this->frame);
          frameIndex = frameArray[rangeIndex];

          if (frameIndex >= 0) {
            txtContent = this->actWin7->txtContent;
            numberFrames = txtContent[frameIndex].numberFrames;
            if (numberFrames > 0) {
              ImageVectorWithHeader** spriteMap = this->actWin7->solidSpriteMap;
              relativeCharValue = currentChar - SellWindowSpecialCharacters_s___09__AZ__az__[rangeStartOffset * 2];
              sprite = spriteMap[txtContent[frameIndex].ptrFrameStart[relativeCharValue % numberFrames]];
            }
            else {
              sprite = nullptr;
            }
          }
          else {
            sprite = nullptr;
          }
          GameWindowRightSide->RenderClippedSprite(param_1 + -0x140 + totalWidth, param_2 - 0xf0, sprite, DrawLayer::Layer0xFFF9);
          totalWidth = totalWidth + 0xb;
          break;
        }
        rangeStartOffset = rangeStartOffset + 1;
      }
    }
  }
}
