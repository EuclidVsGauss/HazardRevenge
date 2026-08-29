#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowRegroup.hpp"

GameWindowRegroup::~GameWindowRegroup() {
  CoreActClass* actObject;

  actObject = this->winaAct;
  if (actObject != nullptr) {
    delete actObject;
  }
}
