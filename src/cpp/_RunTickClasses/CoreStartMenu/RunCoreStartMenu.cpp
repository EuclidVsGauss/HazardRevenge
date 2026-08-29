#include "HazardClasses/CoreStartMenu.hpp"
#include "HazardGlobals.hpp"

int32_t CoreStartMenu::runTick() {
  int32_t skipTick = GetTickCountsAndAsyncStates(&this->cursorX, &this->cursorY, &this->mouseInput);
  this->StartMenuAnimationAndSound();
  if (skipTick != 0) {
    this->RenderStartMenu();
  }
  return this->selectedMainMenuOption;
}
