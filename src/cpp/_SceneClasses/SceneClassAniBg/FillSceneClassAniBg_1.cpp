#include <HazardFunctions.hpp>
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassAnimatedBackground.hpp"
#include "HazardGlobals.hpp"

SceneClassAnimatedBackground::SceneClassAnimatedBackground(char* actFilename, char* actioName, int32_t coord1, int32_t coord2, int32_t layerOffset) {
  int32_t adjustedCoord2;
  CoreActClass* actObject;

  actObject = new CoreActClass(actFilename);
  this->actObject = actObject;
  this->actionIndex = actObject->GetActionIndexByName(actioName);

  this->truncatedRng = PseudoRng() & 0x7f;

  if (layerOffset == 0) {
    adjustedCoord2 = coord2;
  }
  else if (layerOffset == 1) {
    adjustedCoord2 = coord2 + 30;
  }
  else {
    adjustedCoord2 = coord2 + 60;
  }
  adjustedCoord2 = adjustedCoord2 << 4;
  this->coord2WithLayerOffset = adjustedCoord2;

  this->UpdateObjectOnGrid(coord1 << 4, coord2 << 4);
}
