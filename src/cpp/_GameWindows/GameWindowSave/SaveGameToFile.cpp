#include <stdio.h>
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowSave.hpp"
#include "HazardExterns/GameWindowSave.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/CharacterDetails.hpp"
#include "HazardStructs/CharacterEquipment.hpp"
#include "HazardStructs/GameState.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"
#include "HazardStructs/ObjectWrapper.hpp"

void GameWindowSave::SaveGameToFile(int32_t slotIndex) {
  ActiveCharacter** teamCharPtr;
  int32_t teamCharIdx;
  int32_t charCount;
  FILE* saveFileObject;
  int32_t checksumIdx;
  uint32_t checksumCounter;
  InventoryItemStruct* itemInventory;
  int32_t* gameFlagsPtr;
  NumericalCharacterStats* statsPtr;
  CharacterEquipment* equipPtr;
  InventoryItemStruct* saveInventory;
  int32_t* saveFlags;
  uint32_t checksumValue;
  ActiveCharacter** benchCharPtr;
  SYSTEMTIME systemTime;
  GameState* saveState;
  CharacterDetails* charDetails;

  teamCharIdx = slotIndex;
  checksumValue = 0;
  saveState = this->gameStateAddr + slotIndex;
  memset(saveState, 0, sizeof(GameState));
  GetLocalTime(&systemTime);

  sprintf(this->gameStateAddr[slotIndex].description, s___7s__02d__02d__02d__02d, this->saveDescription, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute);

  this->gameStateAddr[slotIndex].coordY = this->savePointCoordY;
  this->gameStateAddr[slotIndex].coordX = this->savePointCoordX;
  strcpy(this->gameStateAddr[slotIndex].sceneLocationName, this->saveSceneName);
  this->gameStateAddr[teamCharIdx].goldAmount = GoldAmount;

  itemInventory = ItemInventory;
  saveInventory = this->gameStateAddr[teamCharIdx].inventoryItems;
  memcpy(saveInventory, itemInventory, sizeof(InventoryItemStruct) * 32);

  gameFlagsPtr = GameFlags;
  saveFlags = this->gameStateAddr[teamCharIdx].gameFlags;
  memcpy(saveFlags, gameFlagsPtr, sizeof(uint32_t) * 2048);

  charCount = 0;
  if (TeamCharacterList[0] != nullptr) {
    teamCharPtr = TeamCharacterList;
    charDetails = this->gameStateAddr[teamCharIdx].characterDetails;
    do {
      charDetails->partyFlag = (*teamCharPtr)->characterId + 1;
      checksumIdx = 0;
      do {
        if (ObjectList[checksumIdx].sceneClassObjectPointer == (*teamCharPtr)->shiftedSceneClassUser0x48) {
          charDetails->largeNumber = ObjectList[checksumIdx].scriptUserFlags;
        }
        checksumIdx = checksumIdx + 1;
      } while (checksumIdx < 32768);

      equipPtr = &(*teamCharPtr)->charEquip;
      memcpy(&charDetails->equipment, equipPtr, sizeof(CharacterEquipment));

      statsPtr = (*teamCharPtr)->characterBaseStats;
      memcpy(&charDetails->stats, statsPtr, sizeof(NumericalCharacterStats));

      teamCharPtr = teamCharPtr + 1;
      charDetails = charDetails + 1;
      charCount = charCount + 1;
    } while (*teamCharPtr != nullptr);
  }

  if (BenchedCharacterList[0] != nullptr) {
    benchCharPtr = BenchedCharacterList;
    charDetails = this->gameStateAddr[teamCharIdx].characterDetails + charCount;
    do {
      charDetails->partyFlag = (*benchCharPtr)->characterId + 11;
      checksumIdx = 0;
      do {
        if (ObjectList[checksumIdx / 8].sceneClassObjectPointer == (*benchCharPtr)->shiftedSceneClassUser0x48) {
          charDetails->largeNumber = ObjectList[checksumIdx / 8].scriptUserFlags;
        }
        checksumIdx = checksumIdx + 8;
      } while (checksumIdx < 0x40000);

      equipPtr = &(*benchCharPtr)->charEquip;
      memcpy(&charDetails->equipment, equipPtr, sizeof(CharacterEquipment));

      statsPtr = (*benchCharPtr)->characterBaseStats;
      memcpy(&charDetails->stats, statsPtr, sizeof(NumericalCharacterStats));

      benchCharPtr = benchCharPtr + 1;
      charDetails = charDetails + 1;

    } while (*benchCharPtr != nullptr);
  }

  checksumCounter = 0;
  do {

    checksumValue = ((byte)this->gameStateAddr[teamCharIdx].description[checksumCounter] + checksumValue) & 0x3ff;
    checksumCounter = checksumCounter + 1;
  } while (checksumCounter < 45136);
  this->gameStateAddr[teamCharIdx].gameFlags[0x7ff] = checksumValue;
  saveFileObject = fopen(s_hazard_sav, s_wb);
  fwrite(this->gameStateAddr, 1, 316176, saveFileObject);
  fclose(saveFileObject);
}
