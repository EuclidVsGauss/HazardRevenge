#include <windows.h>
#include "HazardClasses/SfxObject.hpp"
#include "HazardGlobals.hpp"

void ShutDownSfxObject() {
  if (PtrSfxObject != nullptr) {
    delete PtrSfxObject;
  }
}
