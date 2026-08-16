#ifndef HAZARD_SCENECLASSDOOR_HPP
#define HAZARD_SCENECLASSDOOR_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardEnums/DoorState.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;

class SceneClassDoor : public GameWindowBase {

public:
  SceneClassDoor(int32_t coord1, int32_t coord2, int32_t orientation, int32_t gameFlag, char* fileName);
  virtual ~SceneClassDoor();
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t counter;
  int32_t doorUnlockType;
  DoorStateEnum currentState;
  int32_t actStand;
  int32_t gameFlag;
  CoreActClass* actClass;

  __forceinline void HandleCase_0x7d11(intptr_t param2);
  __forceinline void HandleCase_0x7d3b();
  __forceinline void HandleCase_0x7d3c();
  __forceinline void HandleCase_0x7d04(intptr_t param2);
  __forceinline void HandleCase_0x7d30();
};

#endif
