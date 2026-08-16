#ifndef HAZARD_GRIDHANDLER_HPP
#define HAZARD_GRIDHANDLER_HPP

#include "HazardTypedef.hpp"

class SceneClassCameraBase;

class GridHandler {

public:
  GridHandler();
  virtual ~GridHandler();

  void InitializeGridMaps(int32_t, int32_t);
  int32_t HasVisibileTileInRectangularRegion(int32_t param_1, int32_t param_2, int32_t param_3, int32_t param_4);
  void SetCollisionValueInRectangularRegion(int32_t coord1, int32_t coord2, int32_t length1, int32_t length2, int16_t trackCounter);
  int32_t HasUnoccupiedTileInRectangularRegion(int32_t param_1, int32_t param_2, int32_t param_3, int32_t param_4);
  int32_t HasUnoccupiedTileExcludingTypeInRectangularRegion(int32_t pos1, int32_t pos2, int32_t const1, int32_t const2, int32_t const3);
  int32_t GetCollisionMapValueAtCoordindate(int32_t param_1, int32_t param_2);
  void SetVisibilityAtPosition(int32_t param_1, int32_t param_2, int32_t param_3);
  void UpdateVisibilityRendering(uint32_t param_1, uint32_t param_2, SceneClassCameraBase* cameraBase, int32_t param_4);

  byte** PaddedGridMap_Visibility;
  byte** PaddedGridMap_TileAttributes;
  byte** PaddedGridMap_LineOfSight;
  int16_t** PaddedGridMap_Collision;
  int32_t mapWidthTilesPlusPadding;
  int32_t mapHeightTilesPlusPadding;
};

#endif
