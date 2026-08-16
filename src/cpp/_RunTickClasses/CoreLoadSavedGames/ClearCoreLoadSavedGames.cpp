#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/CoreLoadSavedGames.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/MusicObjectBase.hpp"

CoreLoadSavedGames::~CoreLoadSavedGames() {
  CoreActClass* actObject;
  GameWindow* gameWindow;

  actObject = this->cursor_Act;
  if (actObject != nullptr) {
    delete actObject;
  }
  actObject = this->mainMenu_Act;
  if (actObject != nullptr) {
    delete actObject;
  }
  gameWindow = this->windowStruct;
  if (gameWindow != nullptr) {
    delete gameWindow;
  }
  PixelCalculations_DirectDrawSurface(8, 0);
}
