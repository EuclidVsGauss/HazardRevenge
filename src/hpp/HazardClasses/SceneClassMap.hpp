#ifndef HAZARD_SCENECLASSMAP_HPP
#define HAZARD_SCENECLASSMAP_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/Tilemap.hpp"
#include "HazardTypedef.hpp"

struct BackgroundSpriteObject;
struct ImageVectorWithHeader;
struct TmpBackgroundSpriteInstance;
struct TileColorMaps;

class SceneClassMap : public GameWindowBase {

public:
  SceneClassMap(char* fileName, SceneHandler* param_2);
  virtual ~SceneClassMap();
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  void LoadTmpFile(char* filename);

  TileColorMaps* uniqueTileColorMaps;
  Tilemap tileLayout;
  ImageVectorWithHeader** loadedBackgroundSprites;
  ImageVectorWithHeader** loadedBackgroundShadowSprites;
  TmpBackgroundSpriteInstance* instancesOfBackgroundSprites;
  TmpBackgroundSpriteInstance*** locationOfBackgroundSprites;
  int32_t unused1;
  int32_t unused2;

private:
  __forceinline void Case_0x7d11(intptr_t param_2);
  __forceinline void Case_0x7d3b();
};

#endif
