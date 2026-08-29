#include "HazardGlobals.hpp"

#pragma optimize("s", on)

__declspec(nothrow) int32_t PseudoRng() {
  RngSeed = (RngSeed * 214013) + 2531011;
  return RngSeed >> 16 & 0x7fff;
}

#pragma optimize("s", off)
