#ifndef HAZARD_COREGAMECLASS_HPP
#define HAZARD_COREGAMECLASS_HPP

#include "HazardClasses/RunTickClass.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardStructs/SceneWrapper.hpp"
#include "HazardStructs/WindowReference.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
class RunTickClass;
struct SceneWrapper;
struct GameState;
struct ImageVectorWithHeader;
struct InventoryItemStruct;
struct WindowReference;

class CoreGameClass : public SceneHandler, public RunTickClass {

public:
  CoreGameClass(GameState*);
  virtual ~CoreGameClass();
  virtual int32_t runTick() override;
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  void InitializeNewGameConstants();
  void CallsLoadSceneEtc();

  int32_t init0;
  int32_t toggleableWindows[7];
  int32_t unused1;
  int32_t unused2;
  int32_t unused3;
  int32_t frameNormal;
  int32_t frameGo;
  int32_t frameDontGo;
  int32_t frameSelect;
  int32_t frameAttack;
  int32_t frameCtrl;
  int32_t frameBoard;
  int32_t frameOutOfSight;
  int32_t frameMagic;
  int32_t frameTalk;
  int32_t frameGet;
  int32_t frameOpen;
  int32_t frameWarp;
  int32_t ununsed[6];
  int32_t frameStep;
  int32_t currentMusicIndex;
  int32_t callSceneCounter;
  int32_t RunTickSwitchIntegerResult;
  int32_t counterDrawObjects;
  CoreActClass* actCursor;
  CoreActClass* actWin8;
  ImageVectorWithHeader* cursorSprite;
  float float_600000;
  SceneWrapper activeAndCachedScenes[12];
  SceneWrapper dummy;
  WindowReference initializedGW0s[20];
  int32_t unnamed1;
  int32_t unnamed2;
  int32_t unnamed3;
  int32_t unnamed4;
  int32_t unnamed5;

  __forceinline void SelectActiveTeamMember_0x7d01(int32_t innerSwitchParam);
  __forceinline void CloseWindowAndSelectUnits_0x7d07(GameWindowBase* gameWindow, GameWindowBase** selectableUnits);
  __forceinline void PlaySoundEffect_0x7d0a(int32_t innerSwitchParam);
  __forceinline void PrepareSoundtrack_0x7d0b(int32_t innerSwitchParam);
  __forceinline void CancelOrCloseWindow_0x7d0c(GameWindowBase* param_2);
  __forceinline void RemoveGameWindow_0x7d10(GameWindowBase* param_2);
  __forceinline void ToggleGameWindow_0x7d14(intptr_t param_2, intptr_t param_3);
  __forceinline void SetWindow_0x7d16(int32_t windowRelatedIndex, WindowReference* windowReference);
  __forceinline void SetCursorSprite_0x7d17(intptr_t param_2, intptr_t param_3);
  __forceinline void OpenDialogueWindow_0x7d18(int32_t innerSwitchParam, GameWindowBase* param_3);
  __forceinline void SetRunTickSwitchResult_0x7d1d(int32_t innerSwitchParam);
  __forceinline void SetCameraPosition_0x7d21(int32_t coord1, int32_t coord2);
  __forceinline void ResetRngAndAsyncKeys_0x7d25();
  __forceinline void TriggerObjectInitialization_0x7d27(GameWindowBase* param_2);
  __forceinline void RegisterSceneInstance_0x7d28(SceneHandler* param_2, char* param3AsSceneName);
  __forceinline void ResolveItemConflict_0x7d2c(int32_t switchParameter, intptr_t param_2, intptr_t param_3);
  __forceinline void PlaceInEitherWindow_0x7d2e(InventoryItemStruct* param_2);
  __forceinline void SetLoadingMarkerCount_0x7d31(int32_t innerSwitchParam);
  __forceinline void DrawText_0x7d35(int32_t switchParameter, intptr_t param_2, intptr_t param_3);
  __forceinline void GenerateItemStats_0x7d37(int32_t itemTypeId, InventoryItemStruct* itemStruct);
  __forceinline void ShowGameOverWindow_0x7d39();
};

#endif
