#include "HazardGlobals.hpp"

void SfxObject::CallRuntimeFunction(LPDIRECTSOUNDBUFFER soundBuffer) {
  if (soundBuffer != (LPDIRECTSOUNDBUFFER) nullptr) {
    soundBuffer->Release();
  }
}
