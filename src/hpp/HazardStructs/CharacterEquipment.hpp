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
  InventoryItemAccessory equipmentAccessory1;
  InventoryItemAccessory equipmentAccessory2;
  InventoryItemSpell equipmentSpells[28];
  InventoryItemSharant SharantSlot6;
  InventoryItemSharant SharantSlot5;
  InventoryItemSharant SharantSlot4;
  InventoryItemSharant SharantSlot3;
  InventoryItemSharant SharantSlot2;
  InventoryItemSharant SharantSlot1;
  InventoryItemStruct ActiveSlot1;
  InventoryItemStruct ActiveSlot2;
  InventoryItemStruct ActiveSlot3;
  InventoryItemStruct ActiveSlot4;
};
typedef struct CharacterEquipment CharacterEquipment, *PCharacterEquipment;

#endif
