#ifndef HAZARD_POINTERKEYVALUEPAIR_HPP
#define HAZARD_POINTERKEYVALUEPAIR_HPP
#include "HazardTypedef.hpp"

struct StringIntegerMap {
  char* Key;
  int32_t Value;
};
typedef struct StringIntegerMap StringIntegerMap, *PStringIntegerMap;

#endif
