#ifndef HAZARD_GAMEWINDOWBASE_HPP
#define HAZARD_GAMEWINDOWBASE_HPP

#include "HazardClasses/CoreActClass.hpp"
#include "HazardEnums/MapType.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardTypedef.hpp"

struct InventoryItemStruct;
struct WindowReference;

class SceneHandler;
class GameWindow;
class BloodObject;

class GameWindowBase {

public:
  GameWindowBase();
  virtual ~GameWindowBase();

  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) {}

  void UpdateObjectOnGrid(int32_t position1, int32_t position2);
  int32_t __fastcall TrackObjects(uint32_t userFlags);

  SceneHandler* mainSceneHandler;
  int32_t matrixIndexXTimes16;
  int32_t matrixIndexYTimes16;
  GameWindowBase* nextObject;
  GameWindowBase* previousObject;
  int32_t matrixIndexX;
  int32_t matrixIndexY;

  static __forceinline ImageVectorWithHeader* __InlineGetSolidSpriteFrameForAction(int32_t actionId, CoreActClass* actClass, int32_t currentFrame) {
    ImageVectorWithHeader* sprite;
    if (actionId >= 0) {
      ActContent* txtContent = actClass->txtContent;
      ActContent* pContent = &txtContent[actionId];
      int32_t frameCount = pContent->numberFrames;
      if (frameCount > 0) {
        uint16_t count = currentFrame;
        sprite = actClass->solidSpriteMap[pContent->ptrFrameStart[count % frameCount]];
      }
      else {
        sprite = nullptr;
      }
    }
    else {
      sprite = nullptr;
    }
    return sprite;
  }

  static __forceinline ImageVectorWithHeader* __InlineGetShadowSpriteFrameForAction(int32_t actionId, CoreActClass* actClass, int32_t currentFrame) {
    ImageVectorWithHeader* sprite;
    if (actionId >= 0) {
      ActContent* txtContent = actClass->txtContent;
      ActContent* pContent = &txtContent[actionId];
      int32_t frameCount = pContent->numberFrames;
      if (frameCount > 0) {
        uint16_t count = currentFrame;
        sprite = actClass->shadowSpriteMap[pContent->ptrFrameStart[count % frameCount]];
      }
      else {
        sprite = nullptr;
      }
    }
    else {
      sprite = nullptr;
    }
    return sprite;
  }

  static __forceinline ImageVectorWithHeader* __InlineGetSolidSpriteFrameForActionWithOrientation(int32_t actionId, CoreActClass* actClass, byte orientation, uint16_t currentFrame) {
    ImageVectorWithHeader* sprite;
    int32_t maxNumberFrames;
    if (actionId >= 0) {
      maxNumberFrames = actClass->txtContent[actionId].numberFrames;
      if (maxNumberFrames > 0) {
        int32_t directionalOffset = (orientation & 7) * actClass->numberSprFrames;
        int32_t frameOffset = actClass->txtContent[actionId].ptrFrameStart[currentFrame % maxNumberFrames];
        sprite = actClass->solidSpriteMap[frameOffset + directionalOffset];
      }
      else {
        sprite = nullptr;
      }
    }
    else {
      sprite = nullptr;
    }
    return sprite;
  }

  static __forceinline ImageVectorWithHeader* __InlineGetShadowSpriteFrameForActionWithOrientation(int32_t actionId, CoreActClass* actClass, byte orientation, uint16_t currentFrame) {
    ImageVectorWithHeader* sprite;
    int32_t maxNumberFrames;
    if (actionId >= 0) {
      maxNumberFrames = actClass->txtContent[actionId].numberFrames;
      if (maxNumberFrames > 0) {
        int32_t directionalOffset = (orientation & 7) * actClass->numberSprFrames;
        int32_t frameOffset = actClass->txtContent[actionId].ptrFrameStart[currentFrame % maxNumberFrames];
        sprite = actClass->shadowSpriteMap[frameOffset + directionalOffset];
      }
      else {
        sprite = nullptr;
      }
    }
    else {
      sprite = nullptr;
    }
    return sprite;
  }

  __forceinline void primarySwitchSingleParam_InitializeObject_0x7d11(SceneHandler* p1, MapTypeEnum p2) { primarySwitchSingleParam(0x7d11, (intptr_t)p1, (int32_t)p2); }

  __forceinline void primarySwitchSingleParam_SetWindow_0x7d16(int32_t p1, WindowReference* windowReference) { primarySwitchSingleParam(0x7d16, (intptr_t)p1, (intptr_t)windowReference); }

  __forceinline void primarySwitchSingleParam_TriggerInteraction_0x7d04(int32_t gameObjectId, int32_t null2) { primarySwitchSingleParam(0x7d04, gameObjectId, null2); }

  __forceinline void primarySwitchSingleParam_LoadSceneObject_0x7d08(char* sceneName, GameWindowBase** sceneObject) { primarySwitchSingleParam(0x7d08, (intptr_t)sceneName, (intptr_t)sceneObject); }

  __forceinline void primarySwitchSingleParam_PlaySoundEffect_0x7d0a(int32_t trackId, GameWindowBase* p2) { primarySwitchSingleParam(0x7d0a, trackId, (intptr_t)p2); }

  __forceinline void primarySwitchSingleParam_PrepareSoundtrack_0x7d0b(int32_t trackId, int32_t null2) { primarySwitchSingleParam(0x7d0b, trackId, null2); }

  __forceinline void primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(GameWindowBase* p1, int32_t null2) { primarySwitchSingleParam(0x7d0c, (intptr_t)p1, (intptr_t)null2); }

  __forceinline void primarySwitchSingleParam_PrepareMapForUnit_0x7d12(int32_t null1, int32_t null2) { primarySwitchSingleParam(0x7d12, null1, null2); }

  __forceinline void primarySwitchSingleParam_SetUserLocationOnScene_0x7d13(int32_t coord1, int32_t coord2) { primarySwitchSingleParam(0x7d13, coord1, coord2); }

  __forceinline void primarySwitchSingleParam_CreateControllableUnit_0x7d24(MapTypeEnum p1, int32_t p2) { primarySwitchSingleParam(0x7d24, (int32_t)p1, p2); }

  __forceinline void primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(GameWindowBase* obj, int32_t null2) { primarySwitchSingleParam(0x7d27, (intptr_t)obj, null2); }

  __forceinline void primarySwitchSingleParam_CreateItem_0x7d2b(int32_t itemId, int32_t slot) { primarySwitchSingleParam(0x7d2b, itemId, slot); }

  __forceinline void primarySwitchSingleParam_DrawObject_0x7d3b(int32_t p1, int32_t p2) { primarySwitchSingleParam(0x7d3b, p1, p2); }

  __forceinline void primarySwitchSingleParam_LoadingMarkers_0x7d31(int32_t numberOfDots, int32_t null2) { primarySwitchSingleParam(0x7d31, numberOfDots, null2); }

  __forceinline void primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a(GameWindowBase* obj, int32_t null2) { primarySwitchSingleParam(0x7d1a, (intptr_t)obj, null2); }

  __forceinline void primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a(SceneHandler* obj, int32_t null2) { primarySwitchSingleParam(0x7d1a, (intptr_t)obj, null2); }

  __forceinline void primarySwitchSingleParam_0x7d35(void* obj, int32_t null2) { primarySwitchSingleParam(0x7d35, (intptr_t)obj, (intptr_t)null2); }

  __forceinline void primarySwitchSingleParam_0x7d05(int32_t amount, int32_t null2) { primarySwitchSingleParam(0x7d05, (intptr_t)amount, (intptr_t)null2); }

  __forceinline void primarySwitchSingleParam_0x7d00(int first, int second) { primarySwitchSingleParam(0x7d00, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d01(int first, int second) { primarySwitchSingleParam(0x7d01, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d02(int first, int second) { primarySwitchSingleParam(0x7d02, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d03(void* first, int second) { primarySwitchSingleParam(0x7d03, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d04(int first, int second) { primarySwitchSingleParam(0x7d04, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d06(int first, int second) { primarySwitchSingleParam(0x7d06, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d07(GameWindowBase* first, GameWindowBase** second) { primarySwitchSingleParam(0x7d07, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d0b(int first, int second) { primarySwitchSingleParam(0x7d0b, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d0c(int first, int second) { primarySwitchSingleParam(0x7d0c, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d0d(int first, int second) { primarySwitchSingleParam(0x7d0d, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d0e(int first, int second) { primarySwitchSingleParam(0x7d0e, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d10(GameWindowBase* first, int second) { primarySwitchSingleParam(0x7d10, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d14(int first, int second) { primarySwitchSingleParam(0x7d14, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d15(void* first, int second) { primarySwitchSingleParam(0x7d15, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d16(int first, int second) { primarySwitchSingleParam(0x7d16, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d17(int first, int second) { primarySwitchSingleParam(0x7d17, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d19(int first, int second) { primarySwitchSingleParam(0x7d19, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d1b(int first, int second) { primarySwitchSingleParam(0x7d1b, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d1c(int first, int second) { primarySwitchSingleParam(0x7d1c, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d1d(int first, int second) { primarySwitchSingleParam(0x7d1d, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d1e(int first, int second) { primarySwitchSingleParam(0x7d1e, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d20(int first, int second) { primarySwitchSingleParam(0x7d20, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d22(int first, int second) { primarySwitchSingleParam(0x7d22, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d23(int first, int second) { primarySwitchSingleParam(0x7d23, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d24(int first, int second) { primarySwitchSingleParam(0x7d24, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d26(int first, int second) { primarySwitchSingleParam(0x7d26, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d28(void* first, void* second) { primarySwitchSingleParam(0x7d28, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d29(int first, void* second) { primarySwitchSingleParam(0x7d29, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d2b(int first, int second) { primarySwitchSingleParam(0x7d2b, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d2c(void* first, int second) { primarySwitchSingleParam(0x7d2c, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d2d(int first, int second) { primarySwitchSingleParam(0x7d2d, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d2e(void* first, int second) { primarySwitchSingleParam(0x7d2e, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d2f(int first, int second) { primarySwitchSingleParam(0x7d2f, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d30(int first, int second) { primarySwitchSingleParam(0x7d30, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d34(int first, int second) { primarySwitchSingleParam(0x7d34, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d36(int first, int second) { primarySwitchSingleParam(0x7d36, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d37(InventoryItemStruct* first, InventoryItemStruct* second) { primarySwitchSingleParam(0x7d37, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d38(int first, int second) { primarySwitchSingleParam(0x7d38, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d39(int first, int second) { primarySwitchSingleParam(0x7d39, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d3a(int first, int second) { primarySwitchSingleParam(0x7d3a, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d3c(int first, int second) { primarySwitchSingleParam(0x7d3c, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d3d(void* first, int second) { primarySwitchSingleParam(0x7d3d, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d3e(int first, int second) { primarySwitchSingleParam(0x7d3e, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d3f(int first, int second) { primarySwitchSingleParam(0x7d3f, (intptr_t)first, (intptr_t)second); }

  __forceinline void primarySwitchSingleParam_0x7d41(int first, int second) { primarySwitchSingleParam(0x7d41, (intptr_t)first, (intptr_t)second); }
};

#endif
