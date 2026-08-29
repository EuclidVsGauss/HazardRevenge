#include <windows.h>
#include "HazardClasses/MusicObject.hpp"
#include "HazardGlobals.hpp"

void InitializeMusicObject() {
  PtrMusicObject = new MusicObject(DirectSoundObject);
}
