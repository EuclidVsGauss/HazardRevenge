#ifndef HAZARD_DEFAULTCHARACTERSTATS_HPP
#define HAZARD_DEFAULTCHARACTERSTATS_HPP
#include "HazardTypedef.hpp"
#include "NumericalCharacterStats.hpp"

struct DefaultCharacterStats {
  char* NamePointer;
  int32_t Id;
  NumericalCharacterStats Stats;
  char* Battle1;
  char* Town1;
  char* Battle2;
  char* Town2;
  char* Battle3;
  char* Town3;
  char* Battle4;
  char* Town4;
};
typedef struct DefaultCharacterStats DefaultCharacterStats, *PDefaultCharacterStats;

#endif
