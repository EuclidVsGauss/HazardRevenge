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
  int32_t TalkboxTextFontRelated(char* screenPixels, int32_t referenceHeight, char* stringText, int32_t lengthString);
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

  __forceinline void InitializeObject_0x7d11(intptr_t param_2);
  __forceinline void UseItem_0x7d05(intptr_t param_2);
  __forceinline void CancelOrCloseWindow_0x7d0c();
  __forceinline void HandleMouseInput_0x7d0e(intptr_t param_2);
  __forceinline void ResolveItemConflict_0x7d2c(intptr_t param_2, intptr_t param_3);
  __forceinline void ForwardToSceneHandler_0x7d37_0x7d0a(int32_t switchParam, intptr_t param_2, intptr_t param_3);
  __forceinline void DrawObject_0x7d3b();
  __forceinline void RunTick_0x7d3c();
};

#endif
