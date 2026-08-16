#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"

void MusicObject::UpdateSoundBuffer() {
  IDirectSoundBuffer* soundBuffer;
  int32_t decodedAudioDelta;
  uint32_t playCursorDistance;
  uint32_t playCursorWrappedDistance;
  uint32_t bytesToDecodeRemaining;
  uint32_t playCursor;
  uint32_t decodedBytesProgress;

  LPVOID lpAudioPtr1;
  DWORD dwAudioBytes1;
  LPVOID secondLpAudioPtr1;
  uint32_t secondDwAudioBytes1;
  DWORD dwAudioBytes2;
  uint32_t currentPlayCursor;
  LPVOID lpAudioPtr2;

  if ((this->flagRanPlayWithoutError != 0) && (soundBuffer = this->lpDirectSoundBuffer, soundBuffer != nullptr)) {
    soundBuffer->GetCurrentPosition((LPDWORD)&currentPlayCursor, (LPDWORD) nullptr);
    playCursor = this->usedForGetCurrentPosition;
    if (currentPlayCursor < playCursor) {
      decodedAudioDelta = (currentPlayCursor - playCursor) + 0x80000;
    }
    else {
      decodedAudioDelta = currentPlayCursor - playCursor;
    }
    this->usedForGetCurrentPosition = currentPlayCursor;
    playCursor = this->numeratorComparator;
    decodedAudioDelta = this->totalDecodedBytes + decodedAudioDelta;
    this->totalDecodedBytes = decodedAudioDelta;
    bytesToDecodeRemaining = (decodedAudioDelta - playCursor) + 0x80000;
    if (0x8000 < bytesToDecodeRemaining) {
      playCursorDistance = playCursor & 0x7ffff;
      playCursor = ((bytesToDecodeRemaining & 0xffff8000) + playCursor) & 0x7ffff;
      soundBuffer = this->lpDirectSoundBuffer;

      if (playCursorDistance < playCursor) {

        soundBuffer->Lock(playCursorDistance, playCursor - playCursorDistance, &lpAudioPtr1, (LPDWORD)&dwAudioBytes1, &lpAudioPtr2, (LPDWORD)&dwAudioBytes2, 0);
        decodedBytesProgress = 0x0;

        bool processingBuffer1 = (dwAudioBytes1 != 0);
        while (processingBuffer1) {
          if (this->numeratorComparator >= this->usedAsNumerator) {
            if (this->isLooping != 0) {
              this->ResetMusicFilePointer();
              this->usedAsNumerator = this->usedAsNumerator + this->usedForNumerator;
            }
            else {

              memset((byte*)lpAudioPtr1 + decodedBytesProgress, 0x80, dwAudioBytes1 - decodedBytesProgress);
              break;
            }
          }

          bytesToDecodeRemaining = this->usedAsNumerator - this->numeratorComparator;
          playCursor = dwAudioBytes1 - decodedBytesProgress;
          if (bytesToDecodeRemaining < playCursor) {
            playCursor = bytesToDecodeRemaining;
          }
          this->DecodeADPCMBlock((int16_t*)((intptr_t)lpAudioPtr1 + decodedBytesProgress), playCursor);
          decodedBytesProgress = decodedBytesProgress + playCursor;
          this->numeratorComparator = this->numeratorComparator + playCursor;

          if (dwAudioBytes1 <= decodedBytesProgress) {
            processingBuffer1 = false;
          }
        }

        playCursor = 0;
        bool processingBuffer2 = (dwAudioBytes2 != 0);
        while (processingBuffer2) {
          if (this->numeratorComparator >= this->usedAsNumerator) {
            if (this->isLooping != 0) {
              this->ResetMusicFilePointer();
              this->usedAsNumerator = this->usedAsNumerator + this->usedForNumerator;
            }
            else {

              memset((byte*)lpAudioPtr2 + playCursor, 0x80, dwAudioBytes2 - playCursor);
              break;
            }
          }

          playCursorDistance = this->usedAsNumerator - this->numeratorComparator;
          bytesToDecodeRemaining = dwAudioBytes2 - playCursor;
          if (playCursorDistance < bytesToDecodeRemaining) {
            bytesToDecodeRemaining = playCursorDistance;
          }
          this->DecodeADPCMBlock((int16_t*)((intptr_t)lpAudioPtr2 + playCursor), bytesToDecodeRemaining);
          playCursor = playCursor + bytesToDecodeRemaining;
          this->numeratorComparator = this->numeratorComparator + bytesToDecodeRemaining;

          if (dwAudioBytes2 <= playCursor) {
            processingBuffer2 = false;
          }
        }

        this->lpDirectSoundBuffer->Unlock(lpAudioPtr1, dwAudioBytes1, lpAudioPtr2, dwAudioBytes2);
      }
      else {

        soundBuffer->Lock(playCursorDistance, 0x80000 - playCursorDistance, &secondLpAudioPtr1, (LPDWORD)&secondDwAudioBytes1, &lpAudioPtr2, (LPDWORD)&dwAudioBytes2, 0);
        decodedBytesProgress = 0x0;

        bool processingSecondBuffer1 = (secondDwAudioBytes1 != 0);
        while (processingSecondBuffer1) {
          if (this->numeratorComparator >= this->usedAsNumerator) {
            if (this->isLooping != 0) {
              this->ResetMusicFilePointer();
              this->usedAsNumerator = this->usedAsNumerator + this->usedForNumerator;
            }
            else {

              memset((byte*)secondLpAudioPtr1 + decodedBytesProgress, 0x80, secondDwAudioBytes1 - decodedBytesProgress);
              break;
            }
          }

          playCursorDistance = this->usedAsNumerator - this->numeratorComparator;
          bytesToDecodeRemaining = secondDwAudioBytes1 - decodedBytesProgress;
          if (playCursorDistance < bytesToDecodeRemaining) {
            bytesToDecodeRemaining = playCursorDistance;
          }
          this->DecodeADPCMBlock((int16_t*)((intptr_t)secondLpAudioPtr1 + decodedBytesProgress), bytesToDecodeRemaining);
          decodedBytesProgress = decodedBytesProgress + bytesToDecodeRemaining;
          this->numeratorComparator = this->numeratorComparator + bytesToDecodeRemaining;

          if (secondDwAudioBytes1 <= decodedBytesProgress) {
            processingSecondBuffer1 = false;
          }
        }

        bytesToDecodeRemaining = 0;
        bool processingSecondBuffer2 = (dwAudioBytes2 != 0);
        while (processingSecondBuffer2) {
          if (this->numeratorComparator >= this->usedAsNumerator) {
            if (this->isLooping != 0) {
              this->ResetMusicFilePointer();
              this->usedAsNumerator = this->usedAsNumerator + this->usedForNumerator;
            }
            else {

              memset((byte*)lpAudioPtr2 + bytesToDecodeRemaining, 0x80, dwAudioBytes2 - bytesToDecodeRemaining);
              break;
            }
          }

          playCursorWrappedDistance = this->usedAsNumerator - this->numeratorComparator;
          playCursorDistance = dwAudioBytes2 - bytesToDecodeRemaining;
          if (playCursorWrappedDistance < playCursorDistance) {
            playCursorDistance = playCursorWrappedDistance;
          }
          this->DecodeADPCMBlock((int16_t*)((intptr_t)lpAudioPtr2 + bytesToDecodeRemaining), playCursorDistance);
          bytesToDecodeRemaining = bytesToDecodeRemaining + playCursorDistance;
          this->numeratorComparator = this->numeratorComparator + playCursorDistance;

          if (dwAudioBytes2 <= bytesToDecodeRemaining) {
            processingSecondBuffer2 = false;
          }
        }

        this->lpDirectSoundBuffer->Unlock(secondLpAudioPtr1, (DWORD)secondDwAudioBytes1, lpAudioPtr2, dwAudioBytes2);
        if (playCursor != 0) {
          this->WriteDecodedAudioToBuffer(0, playCursor);
        }
      }
    }
    if ((this->usedAsNumerator <= this->totalDecodedBytes) && (this->isLooping == 0)) {
      this->ReleaseMusicBuffer();
    }
  }
}
