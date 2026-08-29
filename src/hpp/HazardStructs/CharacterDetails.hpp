#ifndef HAZARD_CHARACTERDETAILS_HPP
#define HAZARD_CHARACTERDETAILS_HPP

#include "HazardStructs/CharacterEquipment.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"
#include "HazardTypedef.hpp"

struct CharacterEquipment;

struct CharacterDetails {
  int32_t partyFlag;
  int32_t largeNumber;
  NumericalCharacterStats stats;
  CharacterEquipment equipment;
};
typedef struct CharacterDetails CharacterDetails, *PCharacterDetails;

#endif
