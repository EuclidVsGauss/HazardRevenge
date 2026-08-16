#ifndef HAZARD_TILEMAP_HPP
#define HAZARD_TILEMAP_HPP

#include "HazardTypedef.hpp"

struct TmpObjectHuge;
struct TileColorMaps;

class Tilemap {
public:
  Tilemap();
  virtual ~Tilemap();

  int32_t visibleWidthTiles;
  int32_t visibleHeightTiles;
  uint32_t currentRowIndex;
  uint32_t currentColumnIndex;
  uint32_t tileCacheIndex;
  TmpObjectHuge* tileCacheData;
  TileColorMaps* uniqueTilesArray;
  int16_t** tileMatrix;

  void InitialiseTilemap(int32_t mapWidthTiles, int32_t mapHeightTiles);
  void ScrollRight(int32_t param_1, uint8_t* param_2);
  void ScrollLeft(int32_t param_1, int32_t param_2);
  void ScrollUpDown(int32_t param_1, int32_t param_2);
  void __fastcall BuildTileCache(uint32_t tileWidthPixels, int32_t tileLenghtPixels);
};

#endif
