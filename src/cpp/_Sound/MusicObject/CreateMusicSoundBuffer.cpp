#include "HazardGlobals.hpp"

LPDIRECTSOUNDBUFFER MusicObject::CreateMusicSoundBuffer(int32_t sampleRate, int32_t samplesPerSec, int32_t numChannels, int32_t bufferSizeBytes) {
  IDirectSound* directSoundObj;
  int32_t combinedAddress;
  int16_t blockAlign;
  HRESULT hResult;
  pcmwaveformat_tag waveformat = {0};
  DSBUFFERDESC bufferDesc = {0};
  LPDIRECTSOUNDBUFFER directSoundBuffer;

  uint16_t localNumChannels = numChannels;
  uint16_t localSampleRate = sampleRate;

  combinedAddress = localNumChannels * localSampleRate;
  blockAlign = (combinedAddress + (combinedAddress >> 31 & 0x7)) >> 3;

  bufferDesc.dwSize = 20;
  bufferDesc.dwFlags = 65762;
  bufferDesc.dwBufferBytes = bufferSizeBytes;
  bufferDesc.lpwfxFormat = (LPWAVEFORMATEX)&waveformat;

  waveformat.wf.wFormatTag = 1;
  waveformat.wf.nChannels = localNumChannels;
  waveformat.wf.nSamplesPerSec = samplesPerSec;
  waveformat.wf.nAvgBytesPerSec = blockAlign * samplesPerSec;
  waveformat.wf.nBlockAlign = blockAlign;
  waveformat.wBitsPerSample = localSampleRate;

  directSoundObj = this->DirectSoundObject;
  if (directSoundObj != nullptr) {
    hResult = directSoundObj->CreateSoundBuffer(&bufferDesc, &directSoundBuffer, nullptr);
    if (hResult != 0) {
      return nullptr;
    }
    return directSoundBuffer;
  }
  return nullptr;
}
