#include "HazardGlobals.hpp"

LPDIRECTSOUNDBUFFER MusicObject::CreateMusicSoundBuffer(LPDIRECTSOUNDBUFFER bufferToFill, int32_t samplesPerSec, int32_t numChannels, int32_t bufferSizeBytes) {
  IDirectSound* directSoundObj;
  int32_t combinedAddress;
  uint32_t blockAlign;
  HRESULT hResult;
  pcmwaveformat_tag waveformat;
  DSBUFFERDESC bufferDesc;

  combinedAddress = (numChannels & 0xffff) * ((uintptr_t)bufferToFill & 0xffff);
  blockAlign = (int32_t)(combinedAddress + (combinedAddress >> 31 & 0x7)) >> 3;

  bufferDesc.dwSize = 20;
  bufferDesc.dwFlags = 65762;
  bufferDesc.dwBufferBytes = bufferSizeBytes;
  bufferDesc.dwReserved = 0;
  bufferDesc.lpwfxFormat = (LPWAVEFORMATEX)&waveformat;

  waveformat.wf.wFormatTag = 1;
  waveformat.wf.nChannels = (int16_t)numChannels;
  waveformat.wf.nSamplesPerSec = samplesPerSec;
  waveformat.wf.nAvgBytesPerSec = (blockAlign & 0xffff) * samplesPerSec;
  waveformat.wf.nBlockAlign = (int16_t)blockAlign;
  waveformat.wBitsPerSample = 16;
  directSoundObj = this->DirectSoundObject;
  if (directSoundObj != nullptr) {
    hResult = directSoundObj->CreateSoundBuffer(&bufferDesc, &bufferToFill, nullptr);
    if (hResult == 0) {
      return bufferToFill;
    }
  }
  return (LPDIRECTSOUNDBUFFER) nullptr;
}
