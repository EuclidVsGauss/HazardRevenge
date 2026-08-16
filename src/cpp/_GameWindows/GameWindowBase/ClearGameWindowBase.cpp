#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/ObjectWrapper.hpp"

GameWindowBase::~GameWindowBase() {
  if (this->mainSceneHandler != nullptr) {
    this->mainSceneHandler->primarySwitchSingleParam_0x7d10(this, 0x0);
  }

  int32_t objectListIndex = 0;
  for (objectListIndex = 0; objectListIndex < 0x8000; objectListIndex++) {
    if (ObjectList[objectListIndex].sceneClassObjectPointer == this) {
      break;
    }
  }
  if (objectListIndex < 0x8000) {
    ObjectList[objectListIndex].sceneClassObjectPointer = nullptr;
  }

  objectListIndex = 0;
  if (TeamCharacterList[0] != nullptr) {
    ActiveCharacter** currentTeamChar = TeamCharacterList;
    while (*currentTeamChar != nullptr) {
      if ((*currentTeamChar)->shiftedSceneClassUser0x48 == this) {
        break;
      }
      currentTeamChar++;
      objectListIndex++;
    }
  }

  ActiveCharacter** teamCharToDelete = TeamCharacterList + objectListIndex;
  if (TeamCharacterList[objectListIndex] != nullptr) {
    delete TeamCharacterList[objectListIndex];
    ActiveCharacter* nextTeamChar = TeamCharacterList[objectListIndex + 1];
    *teamCharToDelete = nextTeamChar;

    if (nextTeamChar != nullptr) {
      ActiveCharacter** currentTeamSlot = teamCharToDelete;
      do {
        nextTeamChar = *(currentTeamSlot + 2);
        currentTeamSlot = currentTeamSlot + 1;
        *currentTeamSlot = nextTeamChar;
      } while (nextTeamChar != nullptr);
    }
  }

  objectListIndex = 0;
  if (BenchedCharacterList[0] != nullptr) {
    ActiveCharacter** currentBenchedChar = BenchedCharacterList;
    while (*currentBenchedChar != nullptr) {
      if ((*currentBenchedChar)->shiftedSceneClassUser0x48 == this) {
        break;
      }
      currentBenchedChar++;
      objectListIndex++;
    }
  }

  ActiveCharacter** benchedCharToDelete = BenchedCharacterList + objectListIndex;
  if (BenchedCharacterList[objectListIndex] != nullptr) {
    delete BenchedCharacterList[objectListIndex];
    ActiveCharacter* nextBenchedChar = BenchedCharacterList[objectListIndex + 1];
    *benchedCharToDelete = nextBenchedChar;

    if (nextBenchedChar != nullptr) {
      ActiveCharacter** currentBenchedSlot = benchedCharToDelete;
      do {
        nextBenchedChar = *(currentBenchedSlot + 2);
        currentBenchedSlot = currentBenchedSlot + 1;
        *currentBenchedSlot = nextBenchedChar;
      } while (nextBenchedChar != nullptr);
    }
  }
}
