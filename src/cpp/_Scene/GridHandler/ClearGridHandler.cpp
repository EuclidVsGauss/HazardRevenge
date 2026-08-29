#include "HazardClasses/GridHandler.hpp"

GridHandler::~GridHandler() {
  if (this->PaddedGridMap_LineOfSight != nullptr) {
    delete[] this->PaddedGridMap_LineOfSight;
  }
  if (this->PaddedGridMap_Visibility != nullptr) {
    delete[] this->PaddedGridMap_Visibility;
  }
  if (this->PaddedGridMap_TileAttributes != nullptr) {
    delete[] this->PaddedGridMap_TileAttributes;
  }
  if (this->PaddedGridMap_Collision != nullptr) {
    delete[] this->PaddedGridMap_Collision;
  }
}
