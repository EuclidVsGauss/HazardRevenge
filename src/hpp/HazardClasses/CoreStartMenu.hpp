#ifndef HAZARD_CORESTARTMENU_HPP
#define HAZARD_CORESTARTMENU_HPP

#include <windows.h>
#include <dsound.h>
#include "HazardClasses/RunTickClass.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
class GameWindow;
class RunTickClass;
struct ImageVectorWithHeader;

class CoreStartMenu : public RunTickClass {

public:
  CoreStartMenu();
  virtual ~CoreStartMenu();
  virtual int32_t runTick() override;

  void __fastcall StartMenuAnimationAndSound();
  void __fastcall RenderStartMenu();

  GameWindow* windowPtr;
  CoreActClass* mainmenuAct;
  CoreActClass* cursorAct;
  ImageVectorWithHeader* counter;
  int32_t mainmenuFrame;
  int32_t mainmenuStringIndex;
  int32_t cursorNormal;
  int32_t selectedMainMenuOption;
  int32_t timeResolutionRelated;
  int32_t cursorX;
  int32_t cursorY;
  int32_t mouseInput;
  LPDIRECTSOUNDBUFFER menuSnd_psblyLPDIRECTSOUNDBUF;
};

#endif
