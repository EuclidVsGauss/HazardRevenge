#include "HazardGlobals.hpp"

SfxObject::~SfxObject() {
  if (this->isDirectSoundObjectCreated != 0) {
    DirectSoundObject->Release();
  }
}
