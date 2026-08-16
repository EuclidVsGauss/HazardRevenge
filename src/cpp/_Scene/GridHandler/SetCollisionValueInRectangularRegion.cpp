#include "HazardClasses/GridHandler.hpp"
#include "HazardGlobals.hpp"

void GridHandler::SetCollisionValueInRectangularRegion(int32_t startRow, int32_t startCol, int32_t numRows, int32_t numCols, int16_t trackCounter) {
  int32_t row = startCol;
  for (int32_t colsRemaining = numCols; colsRemaining > 0; colsRemaining--) {
    int32_t col = startRow;
    for (int32_t rowsRemaining = numRows; rowsRemaining > 0; rowsRemaining--) {
      this->PaddedGridMap_Collision[row][col] = trackCounter;
      col++;
    }
    row++;
  }
}
