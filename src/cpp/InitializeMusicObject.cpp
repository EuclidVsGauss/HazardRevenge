#include <windows.h>
#include "HazardClasses/MusicObject.hpp"
#include "HazardGlobals.hpp"

void InitializeMusicObject(void) {
  PtrMusicObject = new MusicObject(DirectSoundObject);
}
