#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreMovieClass.hpp"
#include "HazardClasses/SfxObject.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"

void __fastcall CoreMovieClass::LoadMovieChunks() {
  int16_t runLengthOrSkipFlag;
  uint32_t paletteIndex;
  uint32_t runLength;
  int32_t dataOffset;
  int32_t repeatCounter;
  int32_t currentOffset;
  byte rgbTriplet[3];
  uint16_t paletteEntryCount;
  uint32_t rawSkipValue;

  this->visualsUnpackedFile->readFile(&paletteEntryCount, 2);
  dataOffset = 0;
  if ((int16_t)paletteEntryCount != 0) {
    do {
      this->visualsUnpackedFile->readFile(rgbTriplet, 3);
      this->colorMapBuffer512b[dataOffset] = ((uint16_t)(rgbTriplet[2] >> ((byte)InvBlueOffset & 0x1f)) << ((byte)BlueOffset1 & 0x1f)) + ((uint16_t)(rgbTriplet[1] >> ((byte)InvGreenOffset & 0x1f)) << ((byte)GreenOffset1 & 0x1f)) + ((uint16_t)(rgbTriplet[0] >> ((byte)InvRedOffset & 0x1f)) << ((byte)RedOffset1 & 0x1f));
      dataOffset = dataOffset + 1;
    } while (dataOffset < (int32_t)(paletteEntryCount & 0xffff));
  }

  dataOffset = 0;
  do {
    paletteIndex = this->visualsUnpackedFile->readByte();
    paletteIndex = paletteIndex & 0xff;
    if (paletteIndex == 0) {
      this->visualsUnpackedFile->readFile(&rawSkipValue, 2);
      dataOffset = dataOffset + (rawSkipValue & 0xffff);
    }
    else if (paletteIndex < 0x81) {
      for (; paletteIndex != 0; paletteIndex = paletteIndex - 1) {
        runLength = this->visualsUnpackedFile->readByte();
        this->buffer204800[dataOffset] = this->colorMapBuffer512b[runLength];
        dataOffset = dataOffset + 1;
      }
    }
    else {
      runLength = this->visualsUnpackedFile->readByte();
      repeatCounter = paletteIndex - 0x80;
      runLengthOrSkipFlag = this->colorMapBuffer512b[runLength];
      currentOffset = dataOffset;
      if (0 < repeatCounter) {
        do {
          dataOffset = currentOffset + 1;
          repeatCounter = repeatCounter + -1;
          this->buffer204800[currentOffset] = runLengthOrSkipFlag;
          currentOffset = dataOffset;
        } while (repeatCounter != 0);
      }
    }
  } while (dataOffset < 0x19000);

  if (this->callCounter == 0) {
    PtrSfxObject->RunPlay(this->latestLpDirectSoundBuffer, 255, 128);
  }
}
