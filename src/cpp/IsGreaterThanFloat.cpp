#include "HazardGlobals.hpp"

int32_t __cdecl IsGreaterThanFloat(double* valuePtr) {
  if (GlobalThreshold <= *valuePtr) {
    return 1;
  }
  return 0;
}
