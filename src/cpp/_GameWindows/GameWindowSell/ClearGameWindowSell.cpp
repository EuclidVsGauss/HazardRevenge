#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowSell.hpp"

GameWindowSell::~GameWindowSell() {
  CoreActClass* actObject;

  actObject = this->actWin7;
  if (actObject != nullptr) {
    delete actObject;
  }
}
