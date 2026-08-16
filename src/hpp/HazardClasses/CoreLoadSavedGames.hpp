#ifndef HAZARD_CORELOADSAVEDGAMES_HPP
#define HAZARD_CORELOADSAVEDGAMES_HPP

#include "HazardClasses/RunTickClass.hpp"
#include "HazardStructs/GameState.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
class GameWindow;
struct GameState;
struct ImageVectorWithHeader;

class CoreLoadSavedGames : public RunTickClass {

public:
  CoreLoadSavedGames();
  virtual ~CoreLoadSavedGames();

  virtual int32_t runTick() override;

  void PrintSaveFileText(int32_t param_1, int32_t param_2, char* param_3, int32_t param_4);
  void __fastcall RenderLoadGameScreen();
  void __fastcall LoadGameAnimationAndSound();

  GameWindow* windowStruct;
  CoreActClass* mainMenu_Act;
  CoreActClass* cursor_Act;
  CoreActClass* winB_Act;
  ImageVectorWithHeader* frameEndSprite;
  int32_t frameBegin;
  int32_t normal;
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
  int32_t frameEnd;
  int32_t unused1;
  int32_t unused2;
  int32_t unused3;
  int32_t init2;
  int32_t init0_1;
  int32_t initiallyMax;
  int32_t xCoord;
  int32_t yCoord;
  int32_t mouseClick;
  int32_t init0_3;
  GameState SaveSlot1;
  GameState SaveSlot2;
  GameState SaveSlot3;
  GameState SaveSlot4;
  GameState SaveSlot5;
  GameState SaveSlot6;
  GameState SaveSlot7;
};

#endif
