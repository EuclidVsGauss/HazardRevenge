#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/MusicObject.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardExterns/MusicObject.hpp"
#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"

void MusicObject::WriteDecodedAudioToBuffer(uint32_t lockOffset, DWORD bytesToLock) {
  int32_t* sampleDeltaPtr;
  byte indexShifted;
  uint16_t sampleValue;
  uint32_t availableBytes;
  uint32_t stepValue;
  int32_t sampleCalc;
  uint16_t* outputPtr;
  uint32_t channelOffset;
  uint32_t dwAudioBytes1;
  LPVOID lpAudioPtr1;
  uint32_t dwAudioBytes2;
  LPVOID lpAudioPtr2;
  uint32_t offset;

  this->lpDirectSoundBuffer->Lock(lockOffset, bytesToLock, &lpAudioPtr1, (LPDWORD)&dwAudioBytes1, &lpAudioPtr2, (LPDWORD)&dwAudioBytes2, 0);

  offset = 0;
  bool processingBuffer1 = (dwAudioBytes1 != 0);
  while (processingBuffer1) {

    if (this->numeratorComparator >= this->usedAsNumerator) {
      if (this->isLooping != 0) {
        this->ResetMusicFilePointer();
        this->usedAsNumerator = this->usedAsNumerator + this->usedForNumerator;
      }
      else {
        memset((void*)(offset + (intptr_t)lpAudioPtr1), 0x80, dwAudioBytes1 - offset);
        break;
      }
    }

    availableBytes = this->usedAsNumerator - this->numeratorComparator;
    if (dwAudioBytes1 - offset <= availableBytes) {
      availableBytes = dwAudioBytes1 - offset;
    }

    channelOffset = 0;
    outputPtr = (uint16_t*)(offset + (intptr_t)lpAudioPtr1);
    if (0 < (int32_t)availableBytes) {
      do {
        sampleDeltaPtr = &this->prevSample + ((uint32_t)((this->channelCount & channelOffset) != 0) * 2);
        if (this->nibbleToggle == 0) {
          stepValue = this->byteStream->readByte();
          this->currentByte = (byte)stepValue;
          this->adpcmStepIndex = (byte)stepValue & 0xf;
        }
        else {
          this->adpcmStepIndex = this->currentByte >> 4;
        }
        indexShifted = this->adpcmStepIndex;
        if ((indexShifted & 8) == 0) {
          sampleCalc = sampleDeltaPtr[1] + ((int32_t)((((indexShifted & 7) * 2) + 1) * AdpcmStepSizeTable[*sampleDeltaPtr]) >> 3);
          sampleValue = 0x7fff;
          sampleDeltaPtr[1] = sampleCalc;
          if (sampleCalc < 0x8000) {
            sampleValue = *(uint16_t*)(sampleDeltaPtr + 1);
          }
          else {
            sampleDeltaPtr[1] = 0x7fff;
          }
          *outputPtr = sampleValue;
        }
        else {
          sampleDeltaPtr[1] = sampleDeltaPtr[1] - ((int32_t)((((indexShifted & 7) * 2) + 1) * AdpcmStepSizeTable[*sampleDeltaPtr]) >> 3);
          sampleValue = 0x8000;
          if (sampleDeltaPtr[1] < -0x8000) {
            sampleDeltaPtr[1] = -0x8000;
            *outputPtr = sampleValue;
          }
          else {
            *outputPtr = *(uint16_t*)(sampleDeltaPtr + 1);
          }
        }
        stepValue = *sampleDeltaPtr + AdpcmIndexAdjustTable[this->adpcmStepIndex];
        *sampleDeltaPtr = stepValue;

        *sampleDeltaPtr = __InlineMinimum(__InlineMaximum(*sampleDeltaPtr, (int32_t)0), (int32_t)0x58);
        channelOffset = channelOffset + 2;
        outputPtr = outputPtr + 1;
        this->nibbleToggle = (uint32_t)(this->nibbleToggle == 0);
      } while ((int32_t)channelOffset < (int32_t)availableBytes);
    }

    offset = offset + availableBytes;
    this->numeratorComparator = this->numeratorComparator + availableBytes;

    if (dwAudioBytes1 <= offset) {
      processingBuffer1 = false;
    }
  }

  offset = 0;
  bool processingBuffer2 = (dwAudioBytes2 != 0);
  while (processingBuffer2) {

    if (this->usedAsNumerator <= this->numeratorComparator) {
      if (this->isLooping == 0) {
        memset((void*)(offset + (intptr_t)lpAudioPtr2), 0x80, dwAudioBytes2 - offset);
        break;
      }
      this->ResetMusicFilePointer();
      this->usedAsNumerator = this->usedAsNumerator + this->usedForNumerator;
    }

    availableBytes = this->usedAsNumerator - this->numeratorComparator;
    if (dwAudioBytes2 - offset <= availableBytes) {
      availableBytes = dwAudioBytes2 - offset;
    }

    channelOffset = 0;
    outputPtr = (uint16_t*)(offset + (intptr_t)lpAudioPtr2);
    if (0 < (int32_t)availableBytes) {
      do {
        sampleDeltaPtr = &this->prevSample + ((uint32_t)((this->channelCount & channelOffset) != 0) * 2);
        if (this->nibbleToggle == 0) {
          stepValue = this->byteStream->readByte();
          this->currentByte = (byte)stepValue;
          this->adpcmStepIndex = (byte)stepValue & 0xf;
        }
        else {
          this->adpcmStepIndex = this->currentByte >> 4;
        }
        indexShifted = this->adpcmStepIndex;
        if ((indexShifted & 8) == 0) {
          sampleCalc = sampleDeltaPtr[1] + ((int32_t)((((indexShifted & 7) * 2) + 1) * AdpcmStepSizeTable[*sampleDeltaPtr]) >> 3);
          sampleValue = 0x7fff;
          sampleDeltaPtr[1] = sampleCalc;
          if (sampleCalc < 0x8000) {
            sampleValue = *(uint16_t*)(sampleDeltaPtr + 1);
          }
          else {
            sampleDeltaPtr[1] = 0x7fff;
          }
          *outputPtr = sampleValue;
        }
        else {
          sampleDeltaPtr[1] = sampleDeltaPtr[1] - ((int32_t)((((indexShifted & 7) * 2) + 1) * AdpcmStepSizeTable[*sampleDeltaPtr]) >> 3);
          sampleValue = 0x8000;
          if (sampleDeltaPtr[1] < -0x8000) {
            sampleDeltaPtr[1] = -0x8000;
            *outputPtr = sampleValue;
          }
          else {
            *outputPtr = *(uint16_t*)(sampleDeltaPtr + 1);
          }
        }
        stepValue = *sampleDeltaPtr + AdpcmIndexAdjustTable[this->adpcmStepIndex];
        *sampleDeltaPtr = stepValue;

        *sampleDeltaPtr = __InlineMinimum(__InlineMaximum(*sampleDeltaPtr, (int32_t)0), (int32_t)0x58);
        channelOffset = channelOffset + 2;
        outputPtr = outputPtr + 1;
        this->nibbleToggle = (uint32_t)(this->nibbleToggle == 0);
      } while ((int32_t)channelOffset < (int32_t)availableBytes);
    }

    offset = offset + availableBytes;
    this->numeratorComparator = this->numeratorComparator + availableBytes;

    if (offset >= dwAudioBytes2) {
      processingBuffer2 = false;
    }
  }

  this->lpDirectSoundBuffer->Unlock(lpAudioPtr1, dwAudioBytes1, lpAudioPtr2, dwAudioBytes2);
}
