#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSpellcast.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/InventoryItemSpell.hpp"

GameWindowSpellcast::GameWindowSpellcast(GameWindowBase* sceneClassUserIdentifier, InventoryItemSpell* spellItemParam) {
  this->spellItem = spellItemParam;
  this->sceneClassUser = sceneClassUserIdentifier;
  this->init0_1 = 0;
  this->init0_2 = 0;
  this->isActiveFlag = 0;

  int32_t characterIndex = 0;
  ActiveCharacter** characterList = TeamCharacterList;

  for (characterIndex = 0; characterList[characterIndex] != nullptr; characterIndex++) {
    if (characterList[characterIndex]->shiftedSceneClassUser0x48 == sceneClassUserIdentifier) {
      break;
    }
  }

  this->characterInventory = characterList[characterIndex];
}
