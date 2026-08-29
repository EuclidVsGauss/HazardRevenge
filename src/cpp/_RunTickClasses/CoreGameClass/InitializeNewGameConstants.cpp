#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreGameClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/ObjectWrapper.hpp"
#include "HazardStructs/WindowReference.hpp"

void CoreGameClass::InitializeNewGameConstants() {

  int32_t loopCounter;
  int32_t charIndex;
  ActiveCharacter** charListPtr;
  int32_t* sceneArrayPtr;
  int32_t sceneIndex;

  if (GameFlags == nullptr) {
    GameFlags = new int32_t[2048];
  }
  int32_t flagIndex;
  for (flagIndex = 0; flagIndex < 2048; flagIndex = flagIndex + 1) {
    GameFlags[flagIndex] = 0;
  }
  GameFlags[0] = 1;
  memset(ItemInventory, 0, sizeof(ItemInventory));
  GoldAmount = 500;
  this->counterDrawObjects = 0;
  if (ObjectList == nullptr) {
    ObjectList = (ObjectWrapper*)new byte[32768 * sizeof(ObjectWrapper)];
  }
  int32_t objectIndex;
  for (objectIndex = 0; objectIndex < 32768; objectIndex = objectIndex + 1) {
    ObjectList[objectIndex].sceneClassObjectPointer = nullptr;
  }

  charListPtr = BenchedCharacterList;
  for (charIndex = 12; charIndex != 0; charIndex = charIndex + -1) {
    *charListPtr = nullptr;
    charListPtr = charListPtr + 1;
  }
  charListPtr = TeamCharacterList;
  for (charIndex = 12; charIndex != 0; charIndex = charIndex + -1) {
    *charListPtr = nullptr;
    charListPtr = charListPtr + 1;
  }
  sceneArrayPtr = &this->toggleableWindows[0];
  for (sceneIndex = 7; sceneIndex != 0; sceneIndex = sceneIndex + -1) {
    *sceneArrayPtr = -1;
    sceneArrayPtr = sceneArrayPtr + 1;
  }

  for (loopCounter = 0; loopCounter < 20; loopCounter = loopCounter + 1) {
    this->initializedGW0s[loopCounter].coords[3] = 0;
    this->initializedGW0s[loopCounter].coords[2] = 0;
    this->initializedGW0s[loopCounter].coords[1] = 0;
    this->initializedGW0s[loopCounter].coords[0] = 0;
    this->initializedGW0s[loopCounter].windowAddress = -1;
  }

  this->initializedGW0s[0].coords[2] = 640;
  this->initializedGW0s[0].coords[1] = 0;
  this->initializedGW0s[0].coords[0] = 145;
  this->initializedGW0s[0].coords[3] = 480;
}
