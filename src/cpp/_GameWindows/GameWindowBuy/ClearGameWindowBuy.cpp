#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBuy.hpp"

GameWindowBuy::~GameWindowBuy() {
  CoreActClass* actWin;

  actWin = this->actWin6;
  if (actWin != nullptr) {
    delete actWin;
  }
}
