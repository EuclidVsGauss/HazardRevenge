#ifndef HAZARD_GAMEWINDOWSAVE_HPP
#define HAZARD_GAMEWINDOWSAVE_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardStructs/GameState.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
class GameWindowDialogue;
struct GameState;
struct ImageVectorWithHeader;

class GameWindowSave : public GameWindowBase {

public:
  GameWindowSave(GameWindowDialogue* param_1, char* saveDescription, char* sceneName, int32_t coord1, int32_t coord2);
  virtual ~GameWindowSave();
  virtual void primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) override;

  void SaveGameToFile(int32_t slotIndex);
  void DrawText(int32_t param_1, int32_t param_2, char* param_3, int32_t param_4);

  GameState gameStateAddr[7];
  GameWindowDialogue* gameWindow4;
  CoreActClass* actWin9;
  ImageVectorWithHeader* fillZero;
  char saveDescription[20];
  char saveSceneName[20];
  int32_t frame;
  int32_t button;
  int32_t str0;
  int32_t str1;
  int32_t str2;
  int32_t str3;
  int32_t str4;
  int32_t str5;
  int32_t str6;
  int32_t stra;
  int32_t strb;
  int32_t strc;
  int32_t strd;
  int32_t stre;
  int32_t strf;
  int32_t strg;
  int32_t unused[4];
  int32_t selectedSaveSlot;
  int32_t savePointCoordX;
  int32_t savePointCoordY;
};

#endif
