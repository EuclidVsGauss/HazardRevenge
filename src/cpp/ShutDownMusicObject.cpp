#include "HazardClasses/MusicObject.hpp"
#include "HazardGlobals.hpp"

void ShutDownMusicObject() {
  if (PtrMusicObject != nullptr) {
    delete PtrMusicObject;
  }
}
