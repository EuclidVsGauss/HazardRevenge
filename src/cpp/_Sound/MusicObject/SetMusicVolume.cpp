#include "HazardClasses/MusicObject.hpp"
#include "HazardExterns/MusicObject.hpp"
#include "HazardGlobals.hpp"

void MusicObject::SetMusicVolume(float volumeFactor) {
  int32_t volume;

  volume = -10000 - (int32_t)(MusicVolumeScaleFactor * volumeFactor);
  this->soundVolume = volume;
  if (this->flagRanPlayWithoutError != 0) {
    this->lpDirectSoundBuffer->SetVolume(volume);
  }
}
