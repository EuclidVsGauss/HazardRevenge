#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/SceneClassBoss.hpp"
#include "HazardExterns/SceneClassBoss.hpp"
#include "HazardGlobals.hpp"

SceneClassBoss::SceneClassBoss(char* actName, int32_t position1, int32_t position2, int32_t gameFlag1, int32_t gameFlag2) {
  this->combatRelatedAct = new CoreActClass(actName);

  this->stand1 = this->combatRelatedAct->GetActionIndexByName(s_stand1);
  this->stand2 = this->combatRelatedAct->GetActionIndexByName(s_stand2);
  this->stand3 = this->combatRelatedAct->GetActionIndexByName(s_stand3);
  this->stand4 = this->combatRelatedAct->GetActionIndexByName(s_stand4);
  this->attack1 = this->combatRelatedAct->GetActionIndexByName(s_attack1);
  this->attack2 = this->combatRelatedAct->GetActionIndexByName(s_attack2);
  this->attack3 = this->combatRelatedAct->GetActionIndexByName(s_attack3);
  this->change1 = this->combatRelatedAct->GetActionIndexByName(s_change1);
  this->change2 = this->combatRelatedAct->GetActionIndexByName(s_change2);
  this->change3 = this->combatRelatedAct->GetActionIndexByName(s_change3);

  this->gameFlagindex1 = gameFlag1;
  this->spriteFrame = 0;
  this->gameFlagindex2 = gameFlag2;
  this->coordX = (position1 + 1) * 0x10;
  this->switchTrigger = 0;
  this->actionType = 0;
  this->coordY = (position2 + 1) * 0x10;
}
