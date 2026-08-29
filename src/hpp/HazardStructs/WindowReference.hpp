#ifndef HAZARD_WINDOWREFERENCEPTR_HPP
#define HAZARD_WINDOWREFERENCEPTR_HPP
#include "HazardTypedef.hpp"

struct WindowReference {
  int32_t coords[4];
  intptr_t windowAddress;
};
typedef struct WindowReference WindowReference, *PWindowReference;

#endif
