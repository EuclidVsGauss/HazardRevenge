#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/MusicObject.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardExterns/MusicObject.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"

void MusicObject::DecodeADPCMBlock(int16_t* outputBuffer, int32_t numberSamples) {
  int32_t* channelState;
  byte adpcmNibble;
  uint16_t decodedSample;
  int32_t byteValue;
  int32_t sampleIndex;

  sampleIndex = 0;
  if (0 < numberSamples) {
    while (sampleIndex < numberSamples) {
      channelState = &this->prevSample + ((uint32_t)((this->channelCount & sampleIndex) != 0) * 2);
      if (this->nibbleToggle == 0) {
        byteValue = this->byteStream->readByte();
        this->currentByte = byteValue;
        adpcmNibble = byteValue & 0xf;
      }
      else {
        adpcmNibble = this->currentByte >> 4;
      }
      this->adpcmStepIndex = adpcmNibble;
      if ((adpcmNibble & 8) != 0) {
        decodedSample = 0x8000;
        byteValue = channelState[1] - (((((adpcmNibble & 7) * 2) + 1) * AdpcmStepSizeTable[*channelState]) >> 3);
        channelState[1] = byteValue;
        if (byteValue < -0x8000) {
          channelState[1] = -0x8000;
        }
        else {
          goto label_load_decoded_sample;
        }
      }
      else {
        decodedSample = 0x7fff;
        byteValue = channelState[1] + (((((adpcmNibble & 7) * 2) + 1) * AdpcmStepSizeTable[*channelState]) >> 3);
        channelState[1] = byteValue;
        if (byteValue > 0x7fff) {
          channelState[1] = 0x7fff;
        }
        else {
        label_load_decoded_sample:
          decodedSample = *(uint16_t*)(channelState + 1);
        }
      }
      *outputBuffer = decodedSample;
      byteValue = *channelState + AdpcmIndexAdjustTable[this->adpcmStepIndex];
      *channelState = byteValue;
      *channelState = __InlineMinimum(__InlineMaximum(*channelState, 0), 0x58);
      sampleIndex = sampleIndex + 2;
      outputBuffer = outputBuffer + 1;
      this->nibbleToggle = (this->nibbleToggle == 0);
    }
  }
}
