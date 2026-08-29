#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardGlobals.hpp"

int32_t SceneHandler::StoreAndInitializeObject(GameWindowBase* gameWindowBase) {

  int32_t freeSlot = 0;
  while (freeSlot < this->gameWindowsCounter && this->gameWindowsArray[freeSlot] != nullptr) {
    freeSlot++;
  }

  int32_t newCount = freeSlot + 1;
  int32_t count = newCount >= this->gameWindowsCounter ? newCount : this->gameWindowsCounter;
  this->gameWindowsCounter = count;
  this->gameWindowsArray[freeSlot] = gameWindowBase;
  this->gameWindowsArray[freeSlot]->primarySwitchSingleParam_InitializeObject_0x7d11(this, this->mapType);
  return freeSlot;
}
