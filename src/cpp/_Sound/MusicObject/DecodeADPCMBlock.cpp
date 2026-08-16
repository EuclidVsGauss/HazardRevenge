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
  uint32_t byteValue;
  uint32_t sampleIndex;

  sampleIndex = 0;
  if (0 < numberSamples) {
    do {
      channelState = &this->prevSample + ((uint32_t)((this->channelCount & sampleIndex) != 0) * 2);
      if (this->nibbleToggle == 0) {
        byteValue = this->byteStream->readByte();
        this->currentByte = (byte)byteValue;
        adpcmNibble = (byte)byteValue & 0xf;
      }
      else {
        adpcmNibble = this->currentByte >> 4;
      }
      this->adpcmStepIndex = adpcmNibble;
      if ((adpcmNibble & 8) == 0) {
        decodedSample = 0x7fff;
        byteValue = channelState[1] + ((int32_t)((((adpcmNibble & 7) * 2) + 1) * AdpcmStepSizeTable[*channelState]) >> 3);
        channelState[1] = byteValue;
        if ((int32_t)byteValue < 0x8000) {
          goto label_load_decoded_sample;
        }
        channelState[1] = 0x7fff;
      }
      else {
        decodedSample = 0x8000;
        byteValue = channelState[1] - ((int32_t)((((adpcmNibble & 7) * 2) + 1) * AdpcmStepSizeTable[*channelState]) >> 3);
        channelState[1] = byteValue;
        if ((int32_t)byteValue < -0x8000) {
          channelState[1] = 0xffff8000;
        }
        else {
        label_load_decoded_sample:
          decodedSample = *(uint16_t*)(channelState + 1);
        }
      }
      *outputBuffer = decodedSample;
      byteValue = *channelState + AdpcmIndexAdjustTable[this->adpcmStepIndex];
      *channelState = byteValue;
      *channelState = __InlineMinimum(__InlineMaximum(*channelState, (int32_t)0), (int32_t)0x58);
      sampleIndex = sampleIndex + 2;
      outputBuffer = outputBuffer + 1;
      this->nibbleToggle = (uint32_t)(this->nibbleToggle == 0);
    } while ((int32_t)sampleIndex < numberSamples);
  }
}
