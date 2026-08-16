#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/CoreStartMenu.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/SfxObject.hpp"
#include "HazardGlobals.hpp"

CoreStartMenu::~CoreStartMenu() {
  CoreActClass* cursorActObject;
  GameWindow* windowPtr;

  cursorActObject = this->cursorAct;
  if (cursorActObject != nullptr) {
    delete cursorActObject;
  }

  cursorActObject = this->mainmenuAct;
  if (cursorActObject != nullptr) {
    delete cursorActObject;
  }

  windowPtr = this->windowPtr;
  if (windowPtr != nullptr) {
    delete windowPtr;
  }
  PixelCalculations_DirectDrawSurface(8, 0);
  PtrSfxObject->CallRuntimeFunction(this->menuSnd_psblyLPDIRECTSOUNDBUF);
}
