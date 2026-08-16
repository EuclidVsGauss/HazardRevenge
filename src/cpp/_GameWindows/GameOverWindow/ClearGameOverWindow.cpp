#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameOverWindow.hpp"

GameOverWindow::~GameOverWindow() {
  CoreActClass* actObject;

  actObject = wincAct;
  if (actObject != nullptr) {
    delete actObject;
  }
}
