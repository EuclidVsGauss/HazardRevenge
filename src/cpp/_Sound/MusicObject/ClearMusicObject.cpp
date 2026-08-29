#include "HazardClasses/MusicObject.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"

MusicObject::~MusicObject() {
  IDirectSoundBuffer* soundBuffer;

  soundBuffer = this->lpDirectSoundBuffer;
  if (soundBuffer != nullptr) {
    soundBuffer->Release();
  }
  if (this->byteStream != nullptr) {
    UnpackedFileBase::CloseUnpackedFile(this->byteStream);
  }
}
