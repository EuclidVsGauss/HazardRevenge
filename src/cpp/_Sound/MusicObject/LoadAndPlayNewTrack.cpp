#include "HazardGlobals.hpp"
#include "HazardInlineFunctions.hpp"

void MusicObject::LoadAndPlayNewTrack(uint32_t trackIndex) {
  int32_t loadResult;
  LPDIRECTSOUNDBUFFER lpDirectSoundBuffer;
  uint32_t remainingBytes;
  uint32_t bytesToDecode;
  HRESULT hResult;
  byte* destinationPtr;
  uint32_t totalDecoded1;
  LPVOID lpvAudioPtr2;
  DWORD dwAudioBytes1;
  LPVOID lpvAudioPtr1;
  DWORD dwAudioBytes2;

  if (this->flagRanPlayWithoutError != 0) {
    this->ReleaseMusicBuffer();
  }
  this->flagRanPlayWithoutError = 0;
  loadResult = this->LoadTrackPcm(trackIndex);
  this->usedForNumerator = loadResult;

  if (loadResult != 0) {
    lpDirectSoundBuffer = this->CreateMusicSoundBuffer(this->buffer, this->audioFrequency, this->channelCount, 0x80000);
    this->lpDirectSoundBuffer = lpDirectSoundBuffer;
    if (lpDirectSoundBuffer == (LPDIRECTSOUNDBUFFER) nullptr) {
      this->CloseMusicFile();
      return;
    }
    this->usedAsNumerator = this->usedForNumerator;
    this->isLooping = 0;
    this->usedForGetCurrentPosition = 0;
    this->numeratorComparator = 0;
    this->totalDecodedBytes = 0;

    lpDirectSoundBuffer->Lock(0, 0x80000, &lpvAudioPtr1, &dwAudioBytes1, &lpvAudioPtr2, &dwAudioBytes2, 0);
    totalDecoded1 = 0;

    bool processingBuffer1 = (dwAudioBytes1 != 0);
    while (processingBuffer1) {

      if (this->numeratorComparator >= this->usedAsNumerator) {
        if (this->isLooping != 0) {
          this->ResetMusicFilePointer();
          this->usedAsNumerator = this->usedAsNumerator + this->usedForNumerator;
        }
        else {

          destinationPtr = totalDecoded1 + (byte*)lpvAudioPtr1;
          memset(destinationPtr, 0x80, dwAudioBytes1 - totalDecoded1);
          break;
        }
      }

      remainingBytes = this->usedAsNumerator - this->numeratorComparator;
      bytesToDecode = dwAudioBytes1 - totalDecoded1;
      if (bytesToDecode <= remainingBytes) {
        remainingBytes = bytesToDecode;
      }
      DecodeADPCMBlock((int16_t*)(totalDecoded1 + (intptr_t)lpvAudioPtr1), remainingBytes);
      totalDecoded1 = totalDecoded1 + remainingBytes;
      this->numeratorComparator = this->numeratorComparator + remainingBytes;

      if (dwAudioBytes1 <= totalDecoded1) {
        processingBuffer1 = false;
      }
    }

    totalDecoded1 = 0;
    bool processingBuffer2 = (dwAudioBytes2 != 0);
    while (processingBuffer2) {

      if (this->numeratorComparator >= this->usedAsNumerator) {
        if (this->isLooping != 0) {
          this->ResetMusicFilePointer();
          this->usedAsNumerator = this->usedAsNumerator + this->usedForNumerator;
        }
        else {

          destinationPtr = totalDecoded1 + (byte*)lpvAudioPtr2;
          memset(destinationPtr, 0x80, dwAudioBytes2 - totalDecoded1);
          break;
        }
      }

      bytesToDecode = this->usedAsNumerator - this->numeratorComparator;
      remainingBytes = dwAudioBytes2 - totalDecoded1;
      if (bytesToDecode < remainingBytes) {
        remainingBytes = bytesToDecode;
      }
      this->DecodeADPCMBlock((int16_t*)(totalDecoded1 + (intptr_t)lpvAudioPtr2), remainingBytes);
      totalDecoded1 = totalDecoded1 + remainingBytes;
      this->numeratorComparator = this->numeratorComparator + remainingBytes;

      if (dwAudioBytes2 <= totalDecoded1) {
        processingBuffer2 = false;
      }
    }

    this->lpDirectSoundBuffer->Unlock(lpvAudioPtr1, dwAudioBytes1, lpvAudioPtr2, dwAudioBytes2);
    this->lpDirectSoundBuffer->GetCurrentPosition((LPDWORD) & this->usedForGetCurrentPosition, (LPDWORD) nullptr);
    this->lpDirectSoundBuffer->SetVolume(-10000);
    hResult = this->lpDirectSoundBuffer->Play(0, 0, 1);
    if (hResult == 0) {
      this->flagRanPlayWithoutError = 1;
      this->lpDirectSoundBuffer->SetVolume(this->soundVolume);
    }
  }
}
