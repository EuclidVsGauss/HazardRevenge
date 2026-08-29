#ifndef HAZARD_DEFAULTCHARACTERSTATS_HPP
#define HAZARD_DEFAULTCHARACTERSTATS_HPP
#include "HazardTypedef.hpp"

struct DefaultCharacterStats {
  char* NamePointer;
  int32_t Id;
  int32_t CurrentHp;
  int32_t MaxHp;
  int32_t CurrentMp;
  int32_t MaxMp;
  int32_t Power;
  int32_t ToHit;
  int32_t Guard;
  int32_t Speed;
  int32_t FireResistance;
  int32_t IceResistance;
  int32_t LightningResistance;
  int32_t WindResistance;
  int32_t LandResistance;
  int32_t Eye;
  int32_t Barrage;
  int32_t PowerGrowth;
  int32_t ToHitGrowth;
  int32_t GuardGrowth;
  int32_t SpeedGrowth;
  int32_t Experience;
  int32_t Level;
  int32_t SpriteOutfitLevel;
  int32_t Unused2;
  int32_t Unused3;
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
