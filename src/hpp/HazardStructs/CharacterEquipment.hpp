#ifndef HAZARD_CHARACTEREQUIPMENT_HPP
#define HAZARD_CHARACTEREQUIPMENT_HPP

#include "HazardStructs/InventoryItemAccessory.hpp"
#include "HazardStructs/InventoryItemArmor.hpp"
#include "HazardStructs/InventoryItemBoots.hpp"
#include "HazardStructs/InventoryItemBracer.hpp"
#include "HazardStructs/InventoryItemSharant.hpp"
#include "HazardStructs/InventoryItemSpell.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/InventoryItemWeapon.hpp"
#include "HazardTypedef.hpp"

struct CharacterEquipment {
  InventoryItemWeapon equipmentWeapon;
  InventoryItemArmor equipmentArmor;
  InventoryItemBracer equipmentBracer;
  InventoryItemBoots equipmentBoots;
  InventoryItemAccessory equipmentAccessories[2];
  InventoryItemSpell equipmentSpells[28];
  InventoryItemSharant equipmentSharants[6];
  InventoryItemStruct ActiveSlots[4];
};
typedef struct CharacterEquipment CharacterEquipment, *PCharacterEquipment;

#endif
