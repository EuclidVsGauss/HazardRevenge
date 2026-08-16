#include "HazardClasses/SfxObject.hpp"
#include "HazardExterns/SfxObject.hpp"
#include "HazardGlobals.hpp"

SfxObject::SfxObject() {
  int32_t createResult;

  createResult = DirectSoundCreate(nullptr, &DirectSoundObject, nullptr);
  if (createResult != 0) {
    Sleep(3000);
    createResult = DirectSoundCreate(nullptr, &DirectSoundObject, nullptr);
    if (createResult != 0) {
      MessageBoxA(GameFullscreenWindow, s_Direct_Sound_Error, s_Error, 0);
      this->isDirectSoundObjectCreated = 0;
      goto label_check_dsound_created;
    }
  }
  this->isDirectSoundObjectCreated = 1;
label_check_dsound_created:
  if (this->isDirectSoundObjectCreated != 0) {
    DirectSoundObject->SetCooperativeLevel(GameFullscreenWindow, 1);
  }
}
