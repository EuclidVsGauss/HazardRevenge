#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardGlobals.hpp"

void GridHandler::InitializeGridMaps(int32_t mapWidth, int32_t mapHeight) {
  int32_t lineOfSight;
  int32_t i;
  int32_t j;
  int32_t k;
  int32_t halfVisibilityRows;
  int32_t halfVisibilityCols;
  int32_t visibilityTotalSize;

  this->mapWidthTilesPlusPadding = mapWidth;
  this->mapHeightTilesPlusPadding = mapHeight;
  if (this->PaddedGridMap_Collision != nullptr) {
    delete[] (this->PaddedGridMap_Collision);
  }
  if (this->PaddedGridMap_TileAttributes != nullptr) {
    delete[] this->PaddedGridMap_TileAttributes;
  }
  if (this->PaddedGridMap_Visibility != nullptr) {
    delete[] this->PaddedGridMap_Visibility;
  }
  if (this->PaddedGridMap_LineOfSight != nullptr) {
    delete[] this->PaddedGridMap_LineOfSight;
  }

  this->PaddedGridMap_Collision = (int16_t**)new byte[((this->mapWidthTilesPlusPadding + 2) * this->mapHeightTilesPlusPadding * sizeof(int16_t*))];
  this->PaddedGridMap_TileAttributes = (byte**)new byte[((this->mapWidthTilesPlusPadding + sizeof(int16_t*)) * this->mapHeightTilesPlusPadding)];
  halfVisibilityRows = (this->mapHeightTilesPlusPadding / 2) + 3;
  halfVisibilityCols = (this->mapWidthTilesPlusPadding / 2) + 3;
  visibilityTotalSize = (halfVisibilityRows * sizeof(byte*)) + (halfVisibilityRows * halfVisibilityCols * sizeof(byte));
  this->PaddedGridMap_Visibility = (byte**)new byte[visibilityTotalSize];

  halfVisibilityRows = (this->mapHeightTilesPlusPadding / 2) + 3;
  halfVisibilityCols = (this->mapWidthTilesPlusPadding / 2) + 3;
  visibilityTotalSize = (halfVisibilityRows * sizeof(byte*)) + (halfVisibilityRows * halfVisibilityCols * sizeof(byte));
  this->PaddedGridMap_LineOfSight = (byte**)new byte[visibilityTotalSize];

  j = this->mapHeightTilesPlusPadding;

  for (i = 0; i < j; i = i + 1) {
    this->PaddedGridMap_Collision[i] = ((int16_t*)&this->PaddedGridMap_Collision[j]) + (i * this->mapWidthTilesPlusPadding);
    this->PaddedGridMap_TileAttributes[i] = ((byte*)&this->PaddedGridMap_TileAttributes[this->mapHeightTilesPlusPadding]) + (i * this->mapWidthTilesPlusPadding);

    for (j = 0; j < this->mapWidthTilesPlusPadding; j = j + 1) {
      this->PaddedGridMap_Collision[i][j] = -1;
      this->PaddedGridMap_TileAttributes[i][j] = 5;
    }
    j = this->mapHeightTilesPlusPadding;
  }

  for (i = 0; i < (this->mapHeightTilesPlusPadding / 2) + 3; i++) {
    this->PaddedGridMap_Visibility[i] = (byte*)&this->PaddedGridMap_Visibility[(this->mapHeightTilesPlusPadding / 2) + 3] + (((this->mapWidthTilesPlusPadding / 2) + 3) * i);
    this->PaddedGridMap_LineOfSight[i] = (byte*)&this->PaddedGridMap_LineOfSight[(this->mapHeightTilesPlusPadding / 2) + 3] + (((this->mapWidthTilesPlusPadding / 2) + 3) * i);
    for (k = 0; k < (this->mapWidthTilesPlusPadding / 2) + 3; k = k + 1) {
      this->PaddedGridMap_Visibility[i][k] = 0;
      if ((((k <= 0) || (k >= this->mapWidthTilesPlusPadding / 2)) || (i <= 0)) || (i >= this->mapHeightTilesPlusPadding / 2)) {
        lineOfSight = 1;
      }
      else {
        lineOfSight = 0;
      }
      this->PaddedGridMap_LineOfSight[i][k] = lineOfSight;
    }
  }
}
