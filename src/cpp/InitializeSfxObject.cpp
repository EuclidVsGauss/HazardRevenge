#include <windows.h>
#include "HazardClasses/SfxObject.hpp"
#include "HazardGlobals.hpp"

void InitializeSfxObject(void) {
  SfxObject* soundObject;

  soundObject = new SfxObject();
  PtrSfxObject = soundObject;
}
