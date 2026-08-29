#include "HazardGlobals.hpp"

int32_t SfxObject::RunPlay(LPDIRECTSOUNDBUFFER param_1, int32_t unused, int32_t unsignedPan) {

  int32_t pan;
  DWORD status;

  (void)unused;

  if (param_1 != nullptr) {
    (param_1->GetStatus)(&status);
    if ((status & 1) != 0) {
      (param_1->SetCurrentPosition)(0);
    }
    pan = (unsignedPan - 128) * 10000 / 128;
    (param_1->SetPan)(pan);
    (param_1->Play)(0, 0, 0);
  }
  return 0;
}
