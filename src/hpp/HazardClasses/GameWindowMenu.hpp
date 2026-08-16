#ifndef HAZARD_GAMEWINDOWMENU_HPP
#define HAZARD_GAMEWINDOWMENU_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
struct ImageVectorWithHeader;

class GameWindowMenu : public GameWindowBase {

public:
  GameWindowMenu();
  virtual ~GameWindowMenu();
  virtual void primarySwitchSingleParam(int32_t, intptr_t, intptr_t) override;

  CoreActClass* menuAct;
  ImageVectorWithHeader* highlightedTextSprite;
  int32_t actFrame;
  int32_t actString;
  int32_t actFrame2;
  int32_t actString2;
  int32_t actUndefined[16];
  int32_t sliderIsHeld;
  int32_t showQuitGameMenu;

  __forceinline void Case_0x7d11(intptr_t param2);
  __forceinline void Case_0x7d3b();
  __forceinline void Case_0x7d0e(intptr_t param2);
  __forceinline void Case_0x7d20();
};

#endif
