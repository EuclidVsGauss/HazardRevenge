#ifndef HAZARD_GAMEWINDOWREGROUP_HPP
#define HAZARD_GAMEWINDOWREGROUP_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
class GameWindowDialogue;
struct ActiveCharacter;
struct ImageVectorWithHeader;

class GameWindowRegroup : public GameWindowBase {

public:
  GameWindowRegroup(GameWindowDialogue* dialogueWindow, SceneHandler* sceneHandler, int32_t coord1, int32_t coord2);
  virtual ~GameWindowRegroup();
  virtual void primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) override;

  void DisplayCharacterValues(int32_t textCoord1, int32_t textCoord2, GameWindowBase* charInventory);
  void DisplayValueInWindow(int32_t position1, int32_t position2, int32_t displayValue, int32_t valueIndex);

  ActiveCharacter* teamCharacterInventories[5];
  int32_t teamCharacterInventoriesExtra;
  GameWindowDialogue* gameWindow4;
  SceneHandler* mainSceneHandlerCopy;
  CoreActClass* winaAct;
  ImageVectorWithHeader* sprite;
  int32_t frame;
  int32_t button;
  int32_t face;
  int32_t name;
  int32_t lv;
  int32_t displayExpRelated;
  int32_t displayCurrentHpRelated;
  int32_t displayMaxHpRelated;
  int32_t displayCurrentMpRelated;
  int32_t displayMaxMpRelated;
  int32_t unused[10];
  int32_t partyCoord1;
  int32_t partyCoord2;
  int32_t counter;
  GameWindowBase* allCharacterInventories[10];
  int32_t allCharacterInventories11;
  int32_t allCharacterInventories12;
};

#endif
