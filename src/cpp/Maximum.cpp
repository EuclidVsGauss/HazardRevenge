#include "HazardGlobals.hpp"

int32_t __fastcall Maximum(int32_t a, int32_t b) {
  if (a < b) {
    a = b;
  }
  return a;
}
