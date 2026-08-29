#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameOverWindow.hpp"
#include "HazardExterns/GameOverWindow.hpp"
#include "HazardGlobals.hpp"

GameOverWindow::GameOverWindow() {
  CoreActClass* coreAct;
  int32_t loopCount;
  int32_t* framePtr;

  coreAct = new CoreActClass(s_winc_act);
  this->runGWC_Counter_Max3839 = 0;
  this->wincAct = coreAct;
  framePtr = &this->frame;
  for (loopCount = 20; loopCount != 0; loopCount = loopCount + -1) {
    *framePtr = -1;
    framePtr = framePtr + 1;
  }
  loopCount = this->wincAct->GetActionIndexByName(s_frame);
  this->frame = loopCount;
}
