#include <memory.h>
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowCharacter.hpp"
#include "HazardExterns/GameWindowCharacter.hpp"
#include "HazardTypedef.hpp"

GameWindowCharacter::GameWindowCharacter() {
  CoreActClass* actObject;

  int32_t actionIndexCounter;

  actObject = new CoreActClass(s_win1_act);
  this->win1Act = actObject;

  FillMemory(&this->actFrame, sizeof(this->actFrame) * 20, 0xff);

  actionIndexCounter = 0;
  for (char** actionNamePointer = ListOfCharacterWindowActions; actionNamePointer < ListOfCharacterWindowActions + 9; actionNamePointer++) {
    (&this->actFrame)[actionIndexCounter] = this->win1Act->GetActionIndexByName(*actionNamePointer);
    actionIndexCounter++;
  }

  this->staticXBoundary = 0;
  this->dynamicYBoundary = -288;
  this->boolHoldToShowNextLevelExp = 0;
  this->hideOpenCloseFlag = 0;
}
