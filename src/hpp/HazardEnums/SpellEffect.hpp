#ifndef HAZARD_SPELLEFFECTENUM_HPP
#define HAZARD_SPELLEFFECTENUM_HPP

#include "HazardTypedef.hpp"

typedef int32_t SpellEffectEnum;

struct SpellEffect {
  enum Value {
    FireDamage = 1,
    IceDamage = 2,
    LightningDamage = 3,
    WindDamage = 4,
    EarthDamage = 5,
    HealAlly = 6,
    Gloomy = 7,
    Wander = 8,
    CureGloomy = 9,
    CureWander = 10,
    HalveHp = 11,
    CureAllEffects = 12,
  };
};

#endif
