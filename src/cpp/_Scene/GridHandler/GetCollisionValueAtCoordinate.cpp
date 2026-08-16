#include "HazardClasses/GridHandler.hpp"
#include "HazardGlobals.hpp"

int32_t GridHandler::GetCollisionMapValueAtCoordindate(int32_t x, int32_t y) {
  return this->PaddedGridMap_Collision[y][x];
}
