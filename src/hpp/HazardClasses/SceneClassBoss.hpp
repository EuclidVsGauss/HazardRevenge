#ifndef HAZARD_SCENECLASSBOSS_HPP
#define HAZARD_SCENECLASSBOSS_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
class CoreGameClass;
struct ImageVectorWithHeader;

class SceneClassBoss : public GameWindowBase {

public:
  SceneClassBoss(char* actName, int32_t position1, int32_t position2, int32_t gameFlag1, int32_t gameFlag2);

  void(RunSceneClassBoss)(int32_t param_1, CoreGameClass* param_2);
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  int32_t gameFlagindex1;
  int32_t gameFlagindex2;
  int32_t actionType;
  int32_t switchTrigger;
  int32_t coordX;
  int32_t coordY;
  int32_t stand1;
  int32_t stand2;
  int32_t stand3;
  int32_t stand4;
  int32_t unused1;
  int32_t attack1;
  int32_t attack2;
  int32_t attack3;
  int32_t unused2;
  int32_t change1;
  int32_t change2;
  int32_t change3;
  int32_t unused[8];
  int32_t spriteFrame;
  CoreActClass* combatRelatedAct;
  ImageVectorWithHeader* bossSprite;
};

#endif
