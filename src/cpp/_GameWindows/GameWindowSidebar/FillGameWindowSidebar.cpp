#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowSidebar.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardExterns/GameWindowSidebar.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

GameWindowSidebar::GameWindowSidebar() {
  CoreActClass* win0act;
  int32_t* actionIndicesPtr;
  int32_t* actionIndex;

  win0act = new CoreActClass(s_win0_act);
  actionIndicesPtr = &this->actMain;
  this->win0act = win0act;
  actionIndex = actionIndicesPtr;
  for (int32_t i = 20; i != 0; i--) {
    *actionIndex = -1;
    actionIndex++;
  }

  char** labels = ListOfSidebarActions;
  int32_t* dst = actionIndicesPtr;
  char** labelsEnd = ListOfSidebarActions + 19;

  while (labels < labelsEnd) {
    char* label = *labels;
    int32_t offset = this->win0act->GetActionIndexByName(label);
    *dst = offset;
    labels++;
    dst++;
  }

  this->sidebarTextLine2[0] = '\0';
  this->sidebarTextLine1[0] = '\0';
  this->sidebarHighlight = nullptr;
  this->currentlyActiveScene = nullptr;
}
