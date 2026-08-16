#ifndef HAZARD_GAMEOVERWINDOW_HPP
#define HAZARD_GAMEOVERWINDOW_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;

class GameOverWindow : public GameWindowBase {

public:
  GameOverWindow();
  virtual ~GameOverWindow();
  virtual void primarySwitchSingleParam(int32_t param_1, intptr_t param2, intptr_t param_3) override;

  CoreActClass* wincAct;
  int32_t frame;
  int32_t unused[19];
  int32_t runGWC_Counter_Max3839;
};

#endif
