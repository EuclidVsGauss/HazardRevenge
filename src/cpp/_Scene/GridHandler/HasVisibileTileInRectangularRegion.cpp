#include "HazardClasses/GridHandler.hpp"
#include "HazardGlobals.hpp"

int32_t GridHandler::HasVisibileTileInRectangularRegion(int32_t startX, int32_t startY, int32_t width, int32_t height) {
  for (int32_t row = 0; row < height; row++) {
    for (int32_t col = 0; col < width; col++) {
      if (this->PaddedGridMap_Visibility[(startY + row) >> 1][(col + startX) >> 1] != 0) {
        return 1;
      }
    }
  }
  return 0;
}
