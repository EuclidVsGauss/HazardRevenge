#ifndef HAZARD_GAMEWINDOWDIALOGUE_HPP
#define HAZARD_GAMEWINDOWDIALOGUE_HPP

#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardTypedef.hpp"

class CoreActClass;
class UnpackedFile8248;
struct ImageVectorWithHeader;
struct TextBuffer;

class GameWindowDialogue : public GameWindowBase {

public:
  GameWindowDialogue(int32_t scriptId, GameWindowBase* teamMember);
  virtual ~GameWindowDialogue();

  virtual void primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) override;
  void Talkbox(char* textString, char flagColorScale);
  void ParseScriptTxt();

  UnpackedFileBase* ptrScriptTxt;
  int16_t grayScale[32];
  int16_t coloredScale[32];
  GameWindowBase* teamMember;
  GameWindowBase* saveGameWindow;
  GameWindowBase* saveGameWindowCopy;
  CoreActClass* win4Act;
  ImageVectorWithHeader* portraitSprite;
  ImageVectorWithHeader* yesNoHighlight;
  char* screen_480x640x2;
  TextBuffer* initZero_posPtr;
  TextBuffer* struct94kb_1;
  TextBuffer* struct94kb_2;
  int32_t init0_5;
  int32_t dialogueIndex;
  int32_t martItemIndexes[20];
  int32_t faceFrame;
  int32_t yesnoFrame;
  int32_t unusedActions[18];
  int32_t flag_mouseclick;
  int32_t storeType;
  int32_t buyFactor;
  int32_t sellFactor;
};

#endif
