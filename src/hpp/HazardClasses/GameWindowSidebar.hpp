#ifndef HAZARD_GAMEWINDOWSIDEBAR_HPP
#define HAZARD_GAMEWINDOWSIDEBAR_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
struct ImageVectorWithHeader;

class GameWindowSidebar : public GameWindowBase {

public:
  GameWindowSidebar();
  virtual ~GameWindowSidebar();
  virtual void primarySwitchSingleParam(int32_t switchParam, intptr_t param_3, intptr_t dummy) override;

  void DrawStringForImage(int32_t widthRelated, int32_t heightRelated, char* param_3);

  ImageVectorWithHeader* sidebarHighlight;
  CoreActClass* win0act;
  SceneHandler* currentlyActiveScene;
  char sidebarTextLine1[11];
  char sidebarTextLine2[11];
  char sidebarTextLine3[26];
  int32_t actMain;
  int32_t actNumber;
  int32_t actFrame;
  int32_t actName;
  int32_t actLv;
  int32_t actLvNum;
  int32_t actHp;
  int32_t actMp;
  int32_t actTime;
  int32_t actFace;
  int32_t actSelect;
  int32_t actButton;
  int32_t actStr0;
  int32_t actStr1;
  int32_t actStr2;
  int32_t actStr3;
  int32_t actStr4;
  int32_t actStr5;
  int32_t actStr6;
  int32_t actUndefined;

  __forceinline void Case_0x7d11(intptr_t param_2);
  __forceinline void Case_0x7d3b();
  __forceinline void Case_0x7d07(intptr_t param_2);
  __forceinline void Case_0x7d35(intptr_t param_2);
  __forceinline void Case_0x7d0e(intptr_t param_2);
};

#endif
