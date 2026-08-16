#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneClassMoveTile.hpp"
#include "HazardGlobals.hpp"

SceneClassMoveTile::SceneClassMoveTile(char* name, int32_t gridX, int32_t gridY, int32_t coord1Related, int32_t coord2Related, int32_t flagId1, int32_t flagId2, int32_t flagId3) {
  CoreActClass* coreAct;

  coreAct = new CoreActClass(name);
  this->actObject = coreAct;
  this->StandFrameObject = coreAct->GetActionIndexByName(s_stand);

  this->gameFlagPartialTrigger1 = flagId1;
  this->gameFlagPartialTrigger2 = flagId2;
  this->gameFlagFullTrigger = flagId3;

  this->tmpCoord1 = gridX;
  this->tmpCoord2 = gridY;

  this->switchParameter = 0;
  this->counter = 0;
  this->coord1Related = coord1Related;
  this->coord2Related = coord2Related;

  this->moveTileCoord1 = gridX << 4;
  this->moveTileCoord2 = gridY << 4;

  this->UpdateObjectOnGrid(gridX << 4, gridY << 4);
}
