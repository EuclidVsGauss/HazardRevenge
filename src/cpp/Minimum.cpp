#include "HazardGlobals.hpp"

int32_t __fastcall Minimum(int32_t valueA, int32_t valueB) {
  if (valueA > valueB) {
    valueA = valueB;
  }
  return valueA;
}
