#ifndef HAZARD_NUMERICALCHARACTERSTATS_HPP
#define HAZARD_NUMERICALCHARACTERSTATS_HPP
#include "HazardTypedef.hpp"

struct NumericalCharacterStats {
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
  int32_t TimeGauge;
  int32_t ExpPerKill;
};
typedef struct NumericalCharacterStats NumericalCharacterStats, *PNumericalCharacterStats;

#endif
