#include <windows.h>
#include "HazardClasses/SfxObject.hpp"
#include "HazardGlobals.hpp"

void ShutDownSfxObject(void) {
  if (PtrSfxObject != nullptr) {
    delete PtrSfxObject;
  }
}
