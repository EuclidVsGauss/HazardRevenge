#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/MusicObjectBase.hpp"
#include "HazardExterns/GameWindowDialogue.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/TextBuffer.hpp"

void GameWindowDialogue::Talkbox(char* textString, char flagColorScale) {

  uint32_t fractionalX;
  uint32_t fractionalY;
  int32_t interpolatedIntensity;
  uint32_t textLength;
  uint32_t fractionalXComponent;
  int16_t* ptrTalkbox;
  uint32_t fractionalYComponent;
  TextBuffer* currentBuffer;
  int32_t textPixelOffset;
  int32_t horizontalCounter;
  int32_t verticalCounter;
  int32_t countdown;
  int16_t* destPixel;

  memset(this->screen_480x640x2, 0x0, (7680 * 4) + 2);
  textLength = strlen(textString) + 1;
  countdown = TalkboxTextFontRelated(this->screen_480x640x2, 480, textString, textLength);
  currentBuffer = this->struct94kb_1;
  if (this->initZero_posPtr == currentBuffer) {
    currentBuffer = this->struct94kb_2;
  }
  this->initZero_posPtr = currentBuffer;
  ptrTalkbox = TalkboxImageVector;

  memcpy(currentBuffer, ptrTalkbox, 23512 * 4);
  countdown = countdown * 15;

  if (0 < countdown) {
    textPixelOffset = 16990;
    verticalCounter = 0;
    do {
      fractionalY = verticalCounter / 15;
      horizontalCounter = 0;

      destPixel = this->initZero_posPtr->textWideBytes + (textPixelOffset / 2);
      for (horizontalCounter = 0; horizontalCounter < 0xc30000; horizontalCounter = horizontalCounter + 0x8000) {
        fractionalX = horizontalCounter / 156;
        fractionalYComponent = fractionalY & 0xff;
        fractionalXComponent = fractionalX & 0xff;
        char* pixelPointer = this->screen_480x640x2;

        int32_t x = (int32_t)(fractionalX >> 8);
        int32_t y = (int32_t)(fractionalY >> 8);
        int32_t fx = (int32_t)fractionalXComponent;
        int32_t fy = (int32_t)fractionalYComponent;

        int32_t topLeft = (y * 480) + x;

        interpolatedIntensity = (((int32_t)pixelPointer[topLeft] * (255 - fy) * (255 - fx)) +
                                 ((int32_t)pixelPointer[topLeft + 1] * (255 - fy) * fx) +
                                 ((int32_t)pixelPointer[topLeft + 480] * fy * (255 - fx)) +
                                 ((int32_t)pixelPointer[topLeft + 481] * fy * fx)) >>
                                16;

        if (0 < interpolatedIntensity) {
          if (flagColorScale == 0) {

            *destPixel = this->grayScale[interpolatedIntensity];
          }
          if (flagColorScale == 1) {

            *destPixel = this->coloredScale[interpolatedIntensity];
          }
        }
        destPixel = destPixel + 1;
      }
      verticalCounter = verticalCounter + 0x1000;
      textPixelOffset = textPixelOffset + 990;
      countdown = countdown + -1;
    } while (countdown != 0);
  }
}
