#ifndef HAZARD_GLOBALSTRUCT2048_HPP
#define HAZARD_GLOBALSTRUCT2048_HPP
#include "HazardTypedef.hpp"

struct GlobalStruct2048 {
  byte data[2048];
};
typedef struct GlobalStruct2048 GlobalStruct2048, *PGlobalStruct2048;

#endif
