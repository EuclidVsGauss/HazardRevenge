#ifndef HAZARD_SCENECLASSUSER_HPP
#define HAZARD_SCENECLASSUSER_HPP

#include "HazardClasses/EventHandler.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardEnums/UnitStatusCondition.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
class PathfindingState;
struct ActiveCharacter;
struct BackgroundSpriteObject;
struct ImageVectorWithHeader;
struct NumericalCharacterStats;

class SceneClassUser : public EventHandler, public GameWindowBase {

public:
  SceneClassUser(int32_t userCoord1, int32_t userCoord2, char* userActName, int32_t userFlags, int32_t dialogueScript, int32_t deathScript);
  virtual ~SceneClassUser();
  virtual void primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) override;

  int32_t __fastcall CreateCharacterAndInitialiseEquipment(NumericalCharacterStats* stats, int32_t characterId);
  void AutonomousSceneClassUserUpdate();
  void ResetEventCounter();
  void SetSpriteFrames(int32_t param_1, uint32_t param_2);
  ActiveCharacter* __fastcall GetCharacterObject();

  NumericalCharacterStats numericalCharacterStats;
  int32_t unusedCharacterStats[228];
  CoreActClass* genericAct;
  PathfindingState* pathfindingInputObj;
  PathfindingState* allySupportPathfinding;
  ImageVectorWithHeader* currentSolidSpriteFrame;
  ImageVectorWithHeader* currentShadowSpriteFrame;
  int32_t frameIndexRelated;
  int32_t statusInternalTimer;
  int32_t voluntaryActionSwitchFlag;
  int32_t halfIndex;
  int32_t actStand;
  int32_t actWalk;
  int32_t act1Natt1;
  int32_t act2Natt1;
  int32_t act3Natt1;
  int32_t act1Natt2;
  int32_t act2Natt2;
  int32_t act3Natt2;
  int32_t actDamage;
  int32_t actDead;
  int32_t actMagic;
  int32_t actDynamicallyLoadedFrameFromIndex;
  int32_t actSpecialAtt;
  int32_t actGuard1;
  int32_t actGuard2;
  int32_t unusedAct[5];
  float floatTimesMultiplier1;
  float floatTimesMultiplier2;
  float float1;
  float float2;
  int32_t objectListId;
  int32_t floatMultiplier1_pos1;
  int32_t floatMultiplier2_pos2;
  int32_t orientation;
  int32_t triggerScriptIdOnDeath;
  UnitStatusConditionEnum statusCondition;
  uint32_t userFlags;
  int32_t triggerScriptIdOnTalk;
  int32_t statusConditionTimeLeft;
  char* nameAsAct;
  char names[16];
  char townSpriteRelated[16];

private:
  __forceinline void Case_0x7d11(intptr_t param_2, intptr_t param_3);
  __forceinline void Case_0x7d1e(intptr_t param_2, intptr_t param_3);
  __forceinline void Case_0x7d3b();
  __forceinline void DispatchAutonomousUpdate_0x7d3c(intptr_t param_2);
  __forceinline void Case_0x7d40(intptr_t param_2, intptr_t param_3);
  __forceinline void QueueWalkPosition_0x7d00(intptr_t param_2, intptr_t param_3);
  __forceinline void Case_0x7d04(intptr_t param_2);
  __forceinline void QueueWalkToGate_0x7d15(intptr_t param_2, intptr_t param_3);
  __forceinline void QueueWalkToTalker_0x7d18(intptr_t param_2, intptr_t param_3);
  __forceinline void Case_0x7d3f(intptr_t param_2, intptr_t param_3);
  __forceinline void Case_0x7d02(intptr_t param_2);
  __forceinline void Case_0x7d03(intptr_t param_2, intptr_t param_3);
  __forceinline void Case_0x7d33(intptr_t param_2, intptr_t param_3);
  __forceinline void QueueTalkTrigger_0x7d19(intptr_t param_2, intptr_t param_3);
  __forceinline void Case_0x7d2a(intptr_t param_2);
  __forceinline void Case_0x7d1b(intptr_t param_2, intptr_t param_3);
  __forceinline void Case_0x7d1c(intptr_t param_2, intptr_t param_3);
  __forceinline void UseItem_0x7d05(intptr_t param_2);
  __forceinline void EquipItemFromInventory_0x7d2b(intptr_t param_2, intptr_t param_3);
  __forceinline void InitializeStarterEquipment_0x7d37(intptr_t param_2, intptr_t param_3);
  __forceinline void Case_0x7d41();
  __forceinline void SearchNearbyTarget_0x7d23();
  __forceinline void Case_0x7d06();
  __forceinline void Case_0x7d07();
  __forceinline void AddToSelectedUnits_0x7d1a(intptr_t param_2);
  __forceinline void Case_0x7d2e(intptr_t param_2, intptr_t param_3);
  __forceinline void Case_0x7d0c();
  __forceinline void Case_0x7d12();
  __forceinline void CalculateSpellImpact_0x7d22(intptr_t spellPower, intptr_t spellEffect);
  __forceinline void SetPosition_0x7d13(intptr_t param_2, intptr_t param_3);
  __forceinline void UpdateOrientation_0x7d38(intptr_t param_2);
  __forceinline void Case_0x7d3a(intptr_t param_2);
  __forceinline void Case_0x7d3d(intptr_t param_2);
  __forceinline void Case_0x7d36(intptr_t param_2, intptr_t param_3);
  __forceinline void RestoreFullHealth_0x7d34();
  __forceinline void UpdateAllyPathfinding_0x7d26();
  __forceinline void ResetEventCounter_0x7d32();
  __forceinline void Case_0x7d24(intptr_t param_2, intptr_t param_3);
};

#endif
