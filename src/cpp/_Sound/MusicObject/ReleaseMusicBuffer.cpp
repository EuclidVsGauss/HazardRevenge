#include "HazardGlobals.hpp"

void MusicObject::ReleaseMusicBuffer() {
  IDirectSoundBuffer* lpDirectSoundBufferLocal;

  lpDirectSoundBufferLocal = this->lpDirectSoundBuffer;
  if (lpDirectSoundBufferLocal != nullptr) {
    lpDirectSoundBufferLocal->Stop();
    this->lpDirectSoundBuffer->Release();
    this->lpDirectSoundBuffer = (LPDIRECTSOUNDBUFFER) nullptr;
    this->flagRanPlayWithoutError = 0;
    this->CloseMusicFile();
  }
}
