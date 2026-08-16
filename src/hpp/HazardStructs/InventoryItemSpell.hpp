#ifndef HAZARD_INVENTORYITEMSPELL_HPP
#define HAZARD_INVENTORYITEMSPELL_HPP
#include "HazardEnums/SpellEffect.hpp"
#include "HazardEnums/SpellType.hpp"
#include "HazardTypedef.hpp"

struct InventoryItemSpell {
  int32_t quantity;
  int32_t typeId;
  int32_t equipFlags;
  int32_t actOffset;
  int32_t itemCategory;
  SpellTypeEnum spellType;
  SpellEffectEnum spellEffect;
  int32_t spellLevel;
  int32_t spellExp;
  int32_t spellTypeAsMpCostIndex;
  int32_t actAnimationNumber;
  int32_t experienceAwardedPerCast;
  int32_t spellPower;
  int32_t spellExpRequired2;
  int32_t spellExpRequired3;
  int32_t spellExpRequired4;
  int32_t spellExpRequired5;
  int32_t spellExpRequired6;
  int32_t nothing[1];
};
typedef struct InventoryItemSpell InventoryItemSpell, *PInventoryItemSpell;

#endif
