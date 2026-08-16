#include "HazardClasses/MusicObject.hpp"
#include "HazardGlobals.hpp"

void ShutDownMusicObject(void) {
  if (PtrMusicObject != nullptr) {
    delete PtrMusicObject;
  }
}
