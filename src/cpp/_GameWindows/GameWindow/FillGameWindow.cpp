#include "HazardClasses/BareGameWindow.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/RenderArrays.hpp"
#include "HazardGlobals.hpp"

GameWindow::GameWindow(int32_t origin1, int32_t origin2, int32_t windowWidth, int32_t windowHeight) : BareGameWindow(), RenderArrays(windowWidth, windowHeight) {

  this->copyOrigin1 = origin1;
  this->copyOrigin2 = origin2;
  this->copyWindowWidth = windowWidth;
  this->copyWindowHeight = windowHeight;
}
