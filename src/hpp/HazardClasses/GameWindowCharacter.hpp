#ifndef HAZARD_GAMEWINDOWCHARACTER_HPP
#define HAZARD_GAMEWINDOWCHARACTER_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardEnums/WindowToggle.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;

class GameWindowCharacter : public GameWindowBase {

public:
  GameWindowCharacter();
  virtual ~GameWindowCharacter();
  virtual void primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) override;

  void DisplayNumericalValue(int32_t coordX, int32_t coordY, int32_t displayValue, int32_t mostlyField33);

  CoreActClass* win1Act;
  int32_t actFrame;
  int32_t actBody;
  int32_t actExp;
  int32_t actNumber1;
  int32_t actHp1;
  int32_t actHp2;
  int32_t actMp1;
  int32_t actMp2;
  int32_t actLvNum;
  int32_t actUndefined[11];
  WindowToggleEnum hideOpenCloseFlag;
  int32_t staticXBoundary;
  int32_t dynamicYBoundary;
  int32_t boolHoldToShowNextLevelExp;
};

#endif
