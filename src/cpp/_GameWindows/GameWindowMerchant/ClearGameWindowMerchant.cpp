#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowMerchant.hpp"

GameWindowMerchant::~GameWindowMerchant() {
  CoreActClass* actObject;

  actObject = this->actWin5;
  if (actObject != nullptr) {
    delete actObject;
  }
}
