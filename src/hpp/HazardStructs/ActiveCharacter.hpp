#ifndef HAZARD_ACTIVECHARACTER_HPP
#define HAZARD_ACTIVECHARACTER_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardStructs/CharacterEquipment.hpp"
#include "HazardTypedef.hpp"

struct NumericalCharacterStats;

struct ActiveCharacter {
  int32_t characterId;
  NumericalCharacterStats* characterBaseStats;
  GameWindowBase* shiftedSceneClassUser0x48;
  CharacterEquipment charEquip;
};
typedef struct ActiveCharacter ActiveCharacter, *PActiveCharacter;

#endif
