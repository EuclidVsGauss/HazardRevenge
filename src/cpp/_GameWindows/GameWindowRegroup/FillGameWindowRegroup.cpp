#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/GameWindowRegroup.hpp"
#include "HazardExterns/GameWindowRegroup.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

GameWindowRegroup::GameWindowRegroup(GameWindowDialogue* dialogueWindow, SceneHandler* sceneHandler, int32_t coord1, int32_t coord2) {
  CoreActClass* winaAct;
  int32_t frameElementInit;
  int32_t* framePtr;
  int32_t actionIndexIterator;
  int32_t teamOrBenchedIndex;

  framePtr = &this->frame;
  for (frameElementInit = 20; frameElementInit != 0; frameElementInit = frameElementInit + -1) {
    *framePtr = -1;
    framePtr = framePtr + 1;
  }

  this->gameWindow4 = dialogueWindow;
  this->mainSceneHandlerCopy = sceneHandler;
  this->sprite = nullptr;
  this->partyCoord1 = coord1;
  this->partyCoord2 = coord2;
  winaAct = new CoreActClass(s_wina_act);
  this->winaAct = winaAct;
  this->frame = winaAct->GetActionIndexByName(s_frame);
  this->button = this->winaAct->GetActionIndexByName(s_button);
  this->face = this->winaAct->GetActionIndexByName(s_face);
  this->name = this->winaAct->GetActionIndexByName(s_name);
  this->lv = this->winaAct->GetActionIndexByName(s_lv);
  this->displayExpRelated = this->winaAct->GetActionIndexByName(s_number1);
  this->displayCurrentHpRelated = this->winaAct->GetActionIndexByName(s_hp1);
  this->displayMaxHpRelated = this->winaAct->GetActionIndexByName(s_hp2);
  this->displayCurrentMpRelated = this->winaAct->GetActionIndexByName(s_mp1);
  this->displayMaxMpRelated = this->winaAct->GetActionIndexByName(s_mp2);

  for (actionIndexIterator = 0; actionIndexIterator < 5; actionIndexIterator++) {
    ActiveTeamCharacterSlots[actionIndexIterator] = nullptr;
  }

  teamOrBenchedIndex = 0;
  this->counter = 0;

  for (actionIndexIterator = 0; TeamCharacterList[actionIndexIterator] != nullptr; actionIndexIterator++) {
    this->teamCharacterInventories[actionIndexIterator] = TeamCharacterList[actionIndexIterator];
    this->allCharacterInventories[teamOrBenchedIndex] = TeamCharacterList[actionIndexIterator]->shiftedSceneClassUser0x48;
    teamOrBenchedIndex++;
    this->counter++;
  }

  for (actionIndexIterator = 0; BenchedCharacterList[actionIndexIterator] != nullptr; actionIndexIterator++) {
    this->allCharacterInventories[teamOrBenchedIndex] = BenchedCharacterList[actionIndexIterator]->shiftedSceneClassUser0x48;
    teamOrBenchedIndex++;
  }

  this->allCharacterInventories[teamOrBenchedIndex] = nullptr;
}
