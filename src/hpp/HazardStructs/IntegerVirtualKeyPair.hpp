#ifndef HAZARD_INTEGERVIRTUALKEYPAIR_HPP
#define HAZARD_INTEGERVIRTUALKEYPAIR_HPP
#include "HazardTypedef.hpp"

struct IntegerVirtualKeyPair {
  int32_t index;
  int32_t virtualKey;
};
typedef struct IntegerVirtualKeyPair IntegerVirtualKeyPair, *PIntegerVirtualKeyPair;

#endif
