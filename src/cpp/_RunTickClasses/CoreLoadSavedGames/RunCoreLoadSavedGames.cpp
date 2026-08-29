#include "HazardClasses/CoreLoadSavedGames.hpp"
#include "HazardGlobals.hpp"

int32_t CoreLoadSavedGames::runTick() {
  int32_t tickAsyncState;

  this->LoadGameAnimationAndSound();
  tickAsyncState = GetTickCountsAndAsyncStates(&this->xCoord, &this->yCoord, &this->mouseClick);
  if (tickAsyncState != 0) {
    this->RenderLoadGameScreen();
  }
  return this->init2;
}
