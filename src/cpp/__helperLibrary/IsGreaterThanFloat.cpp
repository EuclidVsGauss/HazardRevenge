#include "HazardGlobals.hpp"

#pragma optimize("s", on)

int32_t __cdecl IsGreaterThanFloat(double* valuePtr) {
  return (*valuePtr >= GlobalThreshold);
}

#pragma optimize("s", off)
