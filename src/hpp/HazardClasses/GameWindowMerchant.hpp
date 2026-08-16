#ifndef HAZARD_GAMEWINDOWMERCHANT_HPP
#define HAZARD_GAMEWINDOWMERCHANT_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
class GameWindowDialogue;

class GameWindowMerchant : public GameWindowBase {

public:
  GameWindowMerchant(GameWindowDialogue*);
  virtual ~GameWindowMerchant();
  virtual void primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) override;

  GameWindowDialogue* dialogueWindow;
  CoreActClass* actWin5;
  int32_t frame;
  int32_t button;
  int32_t unusedActSlots[18];
  int32_t selectedButtonIndex;
};

#endif
