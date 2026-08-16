#include "HazardClasses/GridHandler.hpp"

GridHandler::GridHandler() {
  this->PaddedGridMap_Collision = nullptr;
  this->PaddedGridMap_LineOfSight = nullptr;
  this->PaddedGridMap_TileAttributes = nullptr;
  this->PaddedGridMap_Visibility = nullptr;
  this->mapWidthTilesPlusPadding = 0;
  this->mapHeightTilesPlusPadding = 0;
}
