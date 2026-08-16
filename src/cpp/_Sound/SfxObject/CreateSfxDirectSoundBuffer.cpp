#include "HazardGlobals.hpp"

LPDIRECTSOUNDBUFFER SfxObject::CreateDirectSoundBuffer(int32_t* copyFrom, int32_t size, DWORD samplingRate) {
  HRESULT hResult;
  pcmwaveformat_tag waveformat;
  DSBUFFERDESC dsbuffer;
  LPDIRECTSOUNDBUFFER lpDirectSoundBuffer;
  LPVOID lpvAudioPtr1;
  DWORD dwAudioBytes1;
  LPVOID lpvAudioPtr2;
  DWORD dwAudioBytes2;

  if (this->isDirectSoundObjectCreated != 0) {

    dsbuffer.dwReserved = 0;
    dsbuffer.lpwfxFormat = (LPWAVEFORMATEX)&waveformat;
    dsbuffer.dwSize = 0x14;
    dsbuffer.dwFlags = 0x100e2;
    dsbuffer.dwBufferBytes = (DWORD)size;

    waveformat.wf.wFormatTag = 1;
    waveformat.wf.nChannels = 1;
    waveformat.wBitsPerSample = 8;
    waveformat.wf.nBlockAlign = 1;
    waveformat.wf.nSamplesPerSec = samplingRate;
    waveformat.wf.nAvgBytesPerSec = samplingRate;

    hResult = DirectSoundObject->CreateSoundBuffer((LPCDSBUFFERDESC)&dsbuffer, &lpDirectSoundBuffer, (IUnknown*)nullptr);

    if (hResult == 0) {
      lpDirectSoundBuffer->Lock(0, (DWORD)size, &lpvAudioPtr1, &dwAudioBytes1, &lpvAudioPtr2, &dwAudioBytes2, 1);

      if (dwAudioBytes1 != 0) {
        memcpy(lpvAudioPtr1, copyFrom, dwAudioBytes1);
      }

      if (dwAudioBytes2 != 0) {
        memcpy(lpvAudioPtr2, (int32_t*)(dwAudioBytes1 + (intptr_t)copyFrom), dwAudioBytes2);
      }

      lpDirectSoundBuffer->Unlock(lpvAudioPtr1, dwAudioBytes1, lpvAudioPtr2, dwAudioBytes2);
      return lpDirectSoundBuffer;
    }
  }
  return (LPDIRECTSOUNDBUFFER) nullptr;
}
