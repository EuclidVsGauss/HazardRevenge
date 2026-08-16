#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassUser.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"

int32_t __fastcall SceneClassUser::CreateCharacterAndInitialiseEquipment(NumericalCharacterStats* stats, int32_t characterId) {
  ActiveCharacter* slots;
  int32_t loopCounter;
  int32_t index;
  int32_t* equipPtr;

  index = 0;
  while (TeamCharacterList[index] != nullptr) {
    index = index + 1;
  }

  if (index < 5) {
    slots = new ActiveCharacter();
    TeamCharacterList[index] = slots;
    slots->shiftedSceneClassUser0x48 = this;
    slots->characterBaseStats = stats;
    slots->characterId = characterId;
  }
  else {
    index = 0;
    while (BenchedCharacterList[index] != nullptr) {
      index++;
    }

    slots = new ActiveCharacter();
    BenchedCharacterList[index] = slots;
    slots->shiftedSceneClassUser0x48 = this;
    slots->characterBaseStats = stats;
    slots->characterId = characterId;
  }

  equipPtr = (int32_t*)&slots->charEquip;
  for (loopCounter = 836; loopCounter != 0; loopCounter = loopCounter + -1) {
    *equipPtr = 0;
    equipPtr = equipPtr + 1;
  }

  switch (characterId) {
  case 0:
    this->primarySwitchSingleParam(0x7d2b, 44, 0x0);
    this->primarySwitchSingleParam(0x7d2b, 244, 40);
    return index;
  case 1:
    this->primarySwitchSingleParam(0x7d2b, 82, 0x0);
    this->primarySwitchSingleParam(0x7d2b, 223, 40);
    return index;
  case 2:
    this->primarySwitchSingleParam(0x7d2b, 54, 0x0);
    this->primarySwitchSingleParam(0x7d2b, 250, 0x28);
    return index;
  case 3:
    this->primarySwitchSingleParam(0x7d2b, 45, 0x0);
    this->primarySwitchSingleParam(0x7d2b, 247, 0x28);
    return index;
  case 4:
    this->primarySwitchSingleParam(0x7d2b, 0x24, 0x0);
    return index;
  case 5:
    this->primarySwitchSingleParam(0x7d2b, 0x58, 0x0);
    this->primarySwitchSingleParam(0x7d2b, 0xd0, 0x28);
    return index;
  case 6:
    this->primarySwitchSingleParam(0x7d2b, 0x53, 0x0);
    this->primarySwitchSingleParam(0x7d2b, 0xdf, 0x28);
    return index;
  case 7:
    this->primarySwitchSingleParam(0x7d2b, 0x4d, 0x0);
    this->primarySwitchSingleParam(0x7d2b, 0x7f, 0x1);
    this->primarySwitchSingleParam(0x7d2b, 0xf8, 0x28);
    return index;
  case 8:
    this->primarySwitchSingleParam(0x7d2b, 0x64, 0x0);
    this->primarySwitchSingleParam(0x7d2b, 0x76, 0x1);
    this->primarySwitchSingleParam(0x7d2b, 0xfe, 0x28);
    return index;
  case 9:
    this->primarySwitchSingleParam(0x7d2b, 0x35, 0x0);
    this->primarySwitchSingleParam(0x7d2b, 0x79, 0x1);
    this->primarySwitchSingleParam(0x7d2b, 0xf2, 0x28);
  }
  return index;
}
