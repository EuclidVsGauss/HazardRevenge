#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/SceneClassMap.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/Tilemap.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardExterns/SceneClassMap.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/LargeTmpObject.hpp"
#include "HazardStructs/TileColorMaps.hpp"
#include "HazardStructs/TmpBackgroundSpriteInstance.hpp"

void SceneClassMap::LoadTmpFile(char* filename) {

  UnpackedFileBase* loadedTmp;
  TileColorMaps* tmpTiles;
  TmpBackgroundSpriteInstance* tmpBackground;
  ImageVectorWithHeader* shadowSprite;
  ImageVectorWithHeader* solidSprite;
  SceneHandler* scene;
  TmpBackgroundSpriteInstance* instance;
  byte* imageStart;
  int32_t colorIndex;
  int32_t bmpY;
  int32_t x;
  int16_t spriteWidth;
  int16_t spriteHeight;
  int16_t overlayIndexRelated;
  int16_t nUniqueTiles;
  int16_t nUniqueBackgroundSprites;
  int16_t nBackgroundSpriteInstances;
  int32_t rowCounter;
  int32_t centerX;
  int16_t centerY;
  int16_t coordX;
  int16_t coordY;
  int16_t spriteIndex;
  int32_t mapHeightTiles;
  int32_t loadedTileColor;
  int16_t shortLoadedTileColor;
  int32_t mapWidthTiles;
  byte overlay;
  int16_t colorPalette[256];

  mapWidthTiles = 0;
  mapHeightTiles = 0;
  nUniqueTiles = 0;
  loadedTmp = UnpackedFileBase::LoadFileFromArchive(filename, 0x20000);
  loadedTmp->readFile(&nUniqueTiles, 2);
  loadedTmp->readFile((&mapWidthTiles), 2);
  loadedTmp->readFile((&mapHeightTiles), 2);
  this->mainSceneHandler->mapWidth = (mapWidthTiles + 2) * 16;
  this->mainSceneHandler->mapHeight = (mapHeightTiles + 2) * 16;
  tmpTiles = new TileColorMaps[nUniqueTiles];
  this->uniqueTileColorMaps = tmpTiles;
  loadedTmp->readFile(tmpTiles, nUniqueTiles * sizeof(TileColorMaps));
  colorIndex = 0;

  if (0 < nUniqueTiles << 8) {
    do {
      loadedTileColor = this->uniqueTileColorMaps->colorMap[colorIndex];
      this->uniqueTileColorMaps->colorMap[colorIndex] = (int16_t)(((((loadedTileColor & 31) << 3) >> ((byte)InvBlueOffset & 31)) << ((byte)BlueOffset1 & 31)) + (((loadedTileColor >> 3 & 0xfc) >> ((byte)InvGreenOffset & 31)) << ((byte)GreenOffset1 & 31)) + (((loadedTileColor >> 8 & 0xf8) >> ((byte)InvRedOffset & 31)) << ((byte)RedOffset1 & 31)));
      colorIndex = colorIndex + 1;
    } while (colorIndex < nUniqueTiles * 256);
  }

  colorIndex = 0;
  this->tileLayout.InitialiseTilemap(mapWidthTiles + 8, mapHeightTiles + 8);
  this->tileLayout.uniqueTilesArray = this->uniqueTileColorMaps;

  rowCounter = 0;
  if (0 < mapHeightTiles) {
    x = 1;

    do {
      loadedTmp->readFile(&shortLoadedTileColor, 2);
      colorIndex = colorIndex + 1;

      this->tileLayout.tileMatrix[x][colorIndex] = shortLoadedTileColor;
      if (mapWidthTiles <= colorIndex) {
        x = x + 1;
        rowCounter = rowCounter + 1;
        colorIndex = 0;
      }
    } while (rowCounter < mapHeightTiles);
  }

  this->tileLayout.BuildTileCache(495, 480);
  this->mainSceneHandler->InitializeGridMaps(mapWidthTiles + 4, mapHeightTiles + 4);
  colorIndex = 0;
  if (0 < mapHeightTiles) {
    centerX = 1;
    rowCounter = 1;
    do {
      x = rowCounter;
      loadedTileColor = loadedTmp->readByte();
      scene = this->mainSceneHandler;
      colorIndex = colorIndex + 1;
      scene->PaddedGridMap_TileAttributes[x][colorIndex] = (byte)loadedTileColor;
      scene->PaddedGridMap_Collision[rowCounter][colorIndex] = -1 - (uint16_t)(((byte)loadedTileColor & 3) != 1);
      if ((loadedTileColor & 3U) != 0) {
        this->mainSceneHandler->PaddedGridMap_LineOfSight[centerX >> 1][colorIndex >> 1] = 1;
      }
      if ((loadedTileColor & 0xcU) != 0) {
        this->mainSceneHandler->PaddedGridMap_LineOfSight[centerX >> 1][colorIndex >> 1] = 0;
      }
      if (mapWidthTiles <= colorIndex) {
        rowCounter = rowCounter + 1;
        centerX = centerX + 1;
        colorIndex = 0;
      }
    } while (centerX + -1 < mapHeightTiles);
  }

  loadedTmp->readFile(&nUniqueBackgroundSprites, 2);
  this->loadedBackgroundSprites = new ImageVectorWithHeader*[nUniqueBackgroundSprites + 1];
  this->loadedBackgroundShadowSprites = new ImageVectorWithHeader*[nUniqueBackgroundSprites];
  rowCounter = 0;
  if (0 < nUniqueBackgroundSprites) {
    do {
      loadedTmp->readFile(&spriteWidth, 2);
      loadedTmp->readFile(&spriteHeight, 2);
      loadedTmp->readFile((&centerX), 2);
      loadedTmp->readFile(&centerY, 2);
      loadedTmp->readFile(&overlay, 1);

      if (BackgroundSpriteObject.size < (int32_t)spriteHeight * (int32_t)spriteWidth) {
        if (BackgroundSpriteImageAddress != nullptr) {
          delete BackgroundSpriteImageAddress;
        }
        BackgroundSpriteObject.size = (int32_t)spriteHeight * (int32_t)spriteWidth;
        BackgroundSpriteImageAddress = new byte[(BackgroundSpriteObject.size) + 1];
      }

      loadedTmp->readFile(BackgroundSpriteImageAddress, (int32_t)spriteHeight * (int32_t)spriteWidth);
      loadedTmp->readFile(colorPalette, 512);
      colorIndex = rowCounter;

      for (int32_t paletteIndex = 0; paletteIndex < 256; paletteIndex++) {
        loadedTileColor = colorPalette[paletteIndex];
        colorPalette[paletteIndex] = (int16_t)(((int32_t)((loadedTileColor & 31) << 3) >> ((byte)InvBlueOffset & 31)) << ((byte)BlueOffset1 & 31)) + (int16_t)(((int32_t)(loadedTileColor >> 3 & 0xf8) >> ((byte)InvGreenOffset & 31)) << ((byte)GreenOffset1 & 31)) + (int16_t)(((int32_t)(loadedTileColor >> 8 & 0xf8) >> ((byte)InvRedOffset & 31)) << ((byte)RedOffset1 & 31));
      }

      bmpY = 0;
      this->loadedBackgroundShadowSprites[rowCounter] = nullptr;

      x = spriteWidth * spriteHeight;
      if (0 < x) {
        do {
          if (BackgroundSpriteImageAddress[bmpY] == 1) {
            shadowSprite = DecodeShadowSprite(BackgroundSpriteImageAddress, spriteWidth, spriteHeight, 1, 0, (int32_t)(int16_t)centerX, (int32_t)centerY);
            this->loadedBackgroundShadowSprites[colorIndex] = shadowSprite;
            break;
          }
          bmpY = bmpY + 1;
        } while (bmpY < x);
      }
      imageStart = BackgroundSpriteImageAddress;
      if (bmpY < spriteHeight * spriteWidth) {
        do {
          if (imageStart[bmpY] == 1) {
            imageStart[bmpY] = 0;
            imageStart = BackgroundSpriteImageAddress;
          }
          bmpY = bmpY + 1;
        } while (bmpY < spriteHeight * spriteWidth);
      }
      solidSprite = DecodeSolidSprite(imageStart, (int32_t)spriteWidth, (int32_t)spriteHeight, 0, colorPalette, centerX, (int32_t)centerY);
      rowCounter = colorIndex + 1;
      this->loadedBackgroundSprites[colorIndex] = solidSprite;
    } while (rowCounter < nUniqueBackgroundSprites);
  }
  this->loadedBackgroundSprites[rowCounter] = nullptr;

  this->locationOfBackgroundSprites = (TmpBackgroundSpriteInstance***)new byte[((this->mainSceneHandler->mapHeight >> 8) + 5) * sizeof(int32_t*)];
  scene = this->mainSceneHandler;
  x = 0;
  colorIndex = scene->mapHeight >> 8;
  if (colorIndex != -4 && -1 < colorIndex + 4) {
    do {
      this->locationOfBackgroundSprites[x] = (TmpBackgroundSpriteInstance**)new byte[((scene->mapWidth >> 8) + 4) * sizeof(int32_t*)];
      colorIndex = 0;
      bmpY = this->mainSceneHandler->mapWidth >> 8;
      if (bmpY != -4 && -1 < bmpY + 4) {
        do {
          this->locationOfBackgroundSprites[x][colorIndex] = nullptr;
          colorIndex = colorIndex + 1;
        } while (colorIndex < (this->mainSceneHandler->mapWidth >> 8) + 4);
      }
      scene = this->mainSceneHandler;
      x = x + 1;
    } while (x < (scene->mapHeight >> 8) + 4);
  }
  this->locationOfBackgroundSprites[x] = nullptr;

  loadedTmp->readFile(&nBackgroundSpriteInstances, 2);
  this->instancesOfBackgroundSprites = new TmpBackgroundSpriteInstance[nBackgroundSpriteInstances];

  for (rowCounter = 0; rowCounter < nBackgroundSpriteInstances; rowCounter = rowCounter + 1) {
    loadedTmp->readFile(&coordX, 2);
    loadedTmp->readFile(&coordY, 2);
    loadedTmp->readFile(&overlayIndexRelated, 2);
    loadedTmp->readFile(&spriteIndex, 2);
    this->instancesOfBackgroundSprites[rowCounter].coordX = coordX + 16;
    this->instancesOfBackgroundSprites[rowCounter].coordY = coordY + 16;
    if (overlayIndexRelated == 0) {
      x = coordY;
    }
    else if (overlayIndexRelated < 2) {
      x = coordY + 496;
    }
    else {
      x = coordY + 960;
    }
    this->instancesOfBackgroundSprites[rowCounter].overlayIndex = x;
    this->instancesOfBackgroundSprites[rowCounter].backgroundSprites = this->loadedBackgroundSprites[spriteIndex];
    this->instancesOfBackgroundSprites[rowCounter].backgroundShadowSprites = this->loadedBackgroundShadowSprites[spriteIndex];
    instance = this->instancesOfBackgroundSprites;
    instance[rowCounter].overlayedObject = this->locationOfBackgroundSprites[instance[rowCounter].coordY >> 8][instance[rowCounter].coordX >> 8];
    tmpBackground = (this->instancesOfBackgroundSprites + rowCounter);
    this->locationOfBackgroundSprites[tmpBackground->coordY >> 8][tmpBackground->coordX >> 8] = tmpBackground;
  }
  if (loadedTmp != nullptr) {
    delete loadedTmp;
  }
}
