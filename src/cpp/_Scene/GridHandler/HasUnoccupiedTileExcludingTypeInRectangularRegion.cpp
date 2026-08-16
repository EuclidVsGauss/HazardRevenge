#include "HazardClasses/GridHandler.hpp"
#include "HazardGlobals.hpp"

int32_t GridHandler::HasUnoccupiedTileExcludingTypeInRectangularRegion(int32_t startCol, int32_t startRow, int32_t width, int32_t height, int32_t excludeValue) {
  for (int32_t rowOffset = 0; rowOffset < height; rowOffset++) {
    for (int32_t colOffset = 0; colOffset < width; colOffset++) {
      int32_t tileValue = this->PaddedGridMap_Collision[startRow + rowOffset][startCol + colOffset];
      if (tileValue >= 0 && tileValue != excludeValue) {
        return tileValue;
      }
    }
  }
  return -1;
}
