#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreMovieClass.hpp"
#include "HazardClasses/SfxObject.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"

void __fastcall CoreMovieClass::LoadMovieChunks() {
  int16_t runLengthOrSkipFlag;
  int32_t paletteIndex;
  uint32_t runLength;
  int32_t dataOffset;
  byte rgbTriplet[3];
  uint16_t paletteEntryCount;
  uint32_t rawSkipValue;

  this->visualsUnpackedFile->readFile(&paletteEntryCount, 2);

  for (dataOffset = 0; dataOffset < paletteEntryCount; dataOffset++) {
    this->visualsUnpackedFile->readFile(rgbTriplet, 3);
    int16_t red = (rgbTriplet[0] >> InvRedOffset) << RedOffset1;
    int16_t green = (rgbTriplet[1] >> InvGreenOffset) << GreenOffset1;
    int16_t blue = (rgbTriplet[2] >> InvBlueOffset) << BlueOffset1;
    this->colorMapBuffer512b[dataOffset] = blue + green + red;
  }

  dataOffset = 0;
  while (dataOffset < 0x19000) {
    paletteIndex = this->visualsUnpackedFile->readByte();
    paletteIndex = paletteIndex & 0xff;
    if (paletteIndex == 0) {
      this->visualsUnpackedFile->readFile(&rawSkipValue, 2);
      dataOffset = dataOffset + (rawSkipValue & 0xffff);
    }
    else if (paletteIndex > 0x80) {
      runLength = this->visualsUnpackedFile->readByte();
      paletteIndex = paletteIndex - 0x80;
      runLengthOrSkipFlag = this->colorMapBuffer512b[runLength];
      for (; paletteIndex > 0; paletteIndex--) {
        this->buffer204800[dataOffset] = runLengthOrSkipFlag;
        dataOffset++;
      }
    }
    else {
      for (; paletteIndex > 0; paletteIndex = paletteIndex - 1) {
        runLength = this->visualsUnpackedFile->readByte();
        this->buffer204800[dataOffset] = this->colorMapBuffer512b[runLength];
        dataOffset = dataOffset + 1;
      }
    }
  }

  if (this->callCounter == 0) {
    PtrSfxObject->RunPlay(this->latestLpDirectSoundBuffer, 255, 128);
  }
}
