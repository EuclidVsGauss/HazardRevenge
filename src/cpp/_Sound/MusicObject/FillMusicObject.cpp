#include "HazardClasses/MusicObject.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"

MusicObject::MusicObject(LPDIRECTSOUND soundPointer) {
  this->DirectSoundObject = soundPointer;
  this->lpDirectSoundBuffer = (LPDIRECTSOUNDBUFFER) nullptr;
  this->flagRanPlayWithoutError = 0;
  this->byteStream = nullptr;
  this->SetMusicVolume(1.0);
}
