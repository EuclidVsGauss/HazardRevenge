#include "HazardClasses/GridHandler.hpp"
#include "HazardGlobals.hpp"

int32_t GridHandler::HasUnoccupiedTileInRectangularRegion(int32_t startCol, int32_t startRow, int32_t width, int32_t height) {
  int32_t colOffset;
  int32_t rowOffset;
  int16_t value;

  for (rowOffset = 0; rowOffset < height; rowOffset = rowOffset + 1) {
    for (colOffset = 0; colOffset < width; colOffset = colOffset + 1) {
      value = this->PaddedGridMap_Collision[startRow + rowOffset][colOffset + startCol];
      if (value == -1) {
        return 1;
      }
    }
  }
  return 0;
}
