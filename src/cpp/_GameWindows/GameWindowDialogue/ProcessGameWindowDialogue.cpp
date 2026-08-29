#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowBuy.hpp"
#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/GameWindowMerchant.hpp"
#include "HazardClasses/GameWindowSell.hpp"
#include "HazardClasses/MusicObjectBase.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/GameWindowDialogue.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/TextBuffer.hpp"
#include "HazardStructs/WindowReference.hpp"

const int32_t DialogueWindow_YesButton_LowerX_524 = 524;
const int32_t DialogueWindow_YesButton_UpperX_574 = 574;
const int32_t DialogueWindow_NoButton_LowerX_578 = 578;
const int32_t DialogueWindow_NoButton_UpperX_628 = 628;
const int32_t DialogueWindow_Buttons_LowerY_453 = 453;
const int32_t DialogueWindow_Buttons_UpperY_469 = 469;

__forceinline void GameWindowDialogue::InitializeObject_0x7d11(intptr_t param_2) {
  WindowReference windowReference;

  GameWindowBase* teamMemberWindow;
  SceneClassCameraBase* sceneCamera;
  UnpackedFileBase* loadedScript;
  int32_t readCharacter;
  int32_t dialogueId;

  this->mainSceneHandler = (SceneHandler*)param_2;
  windowReference.coords[0] = 0;
  windowReference.coords[1] = 0;
  windowReference.coords[2] = 640;
  windowReference.coords[3] = 480;
  windowReference.windowAddress = (intptr_t)this;
  this->mainSceneHandler->primarySwitchSingleParam_SetWindow_0x7d16(5, &windowReference);
  teamMemberWindow = this->teamMember;
  if (teamMemberWindow != nullptr) {
    sceneCamera = teamMemberWindow->mainSceneHandler->sceneCamera;
    sceneCamera->primarySwitchSingleParam_SetCameraPosition_0x7d21(teamMemberWindow->matrixIndexXTimes16 << 4, teamMemberWindow->matrixIndexYTimes16 << 4);
  }
  loadedScript = UnpackedFileBase::LoadFileFromArchive(s_script_e_txt, 0x20000);
  this->ptrScriptTxt = loadedScript;
  do {
    readCharacter = this->ptrScriptTxt->readByte();
    while (readCharacter != L'#') {
      if (readCharacter < 0) {

        this->dialogueIndex = 0;
        this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
        return;
      }
      readCharacter = this->ptrScriptTxt->readByte();
    }
    ReadInterpolatableString(this->ptrScriptTxt, s__d, &dialogueId);
  } while (dialogueId != this->dialogueIndex);
}

__forceinline void GameWindowDialogue::DrawObject_0x7d3b() {
  GameWindowBase* savedWindow;
  ImageVectorWithHeader* sprite;

  if (this->dialogueIndex == 0) {
    return;
  }
  if (this->flag_mouseclick < 0) {
    return;
  }
  savedWindow = this->saveGameWindow;
  if (savedWindow != nullptr) {
    savedWindow->primarySwitchSingleParam_DrawObject_0x7d3b(0x0, 0x0);
    return;
  }
  if (this->initZero_posPtr != nullptr) {
    GameWindowRightSide->RenderClippedRectangle(0, 0x181, (int16_t*)this->initZero_posPtr->textWideBytes, 0x1ef, 0x5f, DrawLayer::Layer0xFFF8);
    if (this->portraitSprite != nullptr) {
      GameWindowRightSide->RenderClippedSprite(20, 409, this->portraitSprite, DrawLayer::Layer0xFFF9);
    }
  }
  if (this->flag_mouseclick != 1) {
    return;
  }

  sprite = this->win4Act->__InlineGetSolidSpriteFrameForAction(this->yesnoFrame, 0);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, sprite, DrawLayer::Layer0xFFF9);

  sprite = this->win4Act->__InlineGetSolidSpriteFrameForAction(this->yesnoFrame, 1);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, sprite, DrawLayer::Layer0xFFF9);
  if (this->yesNoHighlight != nullptr) {
    GameWindowRightSide->RenderClippedSprite(-145, 0, this->yesNoHighlight, DrawLayer::Layer0xFFF9);
  }
}

__forceinline void GameWindowDialogue::RunTick_0x7d3c() {
  this->ParseScriptTxt();
}

__forceinline void GameWindowDialogue::HandleMouseInput_0x7d0e(intptr_t param_2) {
  SceneHandler* sceneHandler;
  ImageVectorWithHeader* highlightSprite;
  int32_t compareResult;
  int32_t nestingDepth;
  uint32_t readCharacter;
  char readString[200];

  this->yesNoHighlight = nullptr;
  if (param_2 == 0x0) {
    return;
  }
  sceneHandler = this->mainSceneHandler;
  sceneHandler->primarySwitchSingleParam(0x7d17, 9, 0x0);
  if (this->saveGameWindow != nullptr) {
    sceneHandler = this->mainSceneHandler;
    sceneHandler->primarySwitchSingleParam(0x7d17, 0, 0x0);
    this->saveGameWindow->primarySwitchSingleParam(0x7d0e, 0x0, 0x0);
    return;
  }

  if (this->flag_mouseclick == 1) {

    if ((((DialogueWindow_YesButton_LowerX_524 < CursorXCoord) && (CursorXCoord < DialogueWindow_YesButton_UpperX_574)) && (DialogueWindow_Buttons_LowerY_453 < CursorYCoord)) && (CursorYCoord < DialogueWindow_Buttons_UpperY_469)) {
      highlightSprite = this->win4Act->__InlineGetSolidSpriteFrameForAction(this->yesnoFrame, 2);
      this->yesNoHighlight = highlightSprite;
    }

    if (((DialogueWindow_NoButton_LowerX_578 < CursorXCoord) && (CursorXCoord < DialogueWindow_NoButton_UpperX_628)) && (DialogueWindow_Buttons_LowerY_453 < CursorYCoord && (CursorYCoord < DialogueWindow_Buttons_UpperY_469))) {
      highlightSprite = this->win4Act->__InlineGetSolidSpriteFrameForAction(this->yesnoFrame, 3);
      this->yesNoHighlight = highlightSprite;
    }

    if ((MouseButtonClick & 0x11) == 1) {
      if (((DialogueWindow_YesButton_LowerX_524 < CursorXCoord) && (CursorXCoord < DialogueWindow_YesButton_UpperX_574)) && (DialogueWindow_Buttons_LowerY_453 < CursorYCoord && (CursorYCoord < DialogueWindow_Buttons_UpperY_469))) {
        this->flag_mouseclick = 0;
      }
      if ((((DialogueWindow_NoButton_LowerX_578 < CursorXCoord) && (CursorXCoord < DialogueWindow_NoButton_UpperX_628)) && (DialogueWindow_Buttons_LowerY_453 < CursorYCoord)) && (CursorYCoord < DialogueWindow_Buttons_UpperY_469)) {
        nestingDepth = 0;
        do {
          ReadInterpolatableString(this->ptrScriptTxt, InterpolatableString, readString);
          if (readString[0] == ';') {
            readCharacter = this->ptrScriptTxt->readByte();
            while (readCharacter != '\n') {
              readCharacter = this->ptrScriptTxt->readByte();
            }
          }

          compareResult = strcmp(readString, s_if);
          if (compareResult == 0) {
            nestingDepth++;
          }

          compareResult = strcmp(readString, s_endif);
          if (compareResult == 0) {
            nestingDepth--;
          }

          compareResult = strcmp(readString, s_elseif);
        } while (((compareResult != 0) || (nestingDepth != 0)) && (0 <= nestingDepth));
        this->flag_mouseclick = 0;
      }
    }
  }
  else {
    if (((MouseButtonClick & 0x22) == 2) && (8 <= this->init0_5)) {
      this->init0_5 = 8;
    }
    if (InputStates128[29] == '\0') {
      return;
    }
    this->init0_5 = this->init0_5 + -64;
    return;
  }
}

__forceinline void GameWindowDialogue::UseItem_0x7d05(intptr_t param_2) {
  GameWindowBase* teamMember;

  teamMember = this->teamMember;
  if (teamMember != nullptr) {
    teamMember->primarySwitchSingleParam_0x7d05(param_2, 0x0);
  }
}

__forceinline void GameWindowDialogue::ResolveItemConflict_0x7d2c(intptr_t param_2, intptr_t param_3) {
  SceneHandler* teamSceneHandler;
  GameWindowBase* teamMember = this->teamMember;
  if (teamMember != nullptr) {
    teamSceneHandler = this->teamMember->mainSceneHandler;
    teamSceneHandler->primarySwitchSingleParam(0x7d2c, param_2, param_3);
  }
}

__forceinline void GameWindowDialogue::ForwardToSceneHandler_0x7d37_0x7d0a(int32_t switchParam, intptr_t param_2, intptr_t param_3) {
  SceneHandler* sceneHandler;

  sceneHandler = this->mainSceneHandler;
  sceneHandler->primarySwitchSingleParam(switchParam, param_2, param_3);
}

__forceinline void GameWindowDialogue::CancelOrCloseWindow_0x7d0c() {
  this->mainSceneHandler->primarySwitchSingleParam(0x7d14, 4, 0x0);
  this->saveGameWindowCopy = this->saveGameWindow;
  this->saveGameWindow = nullptr;
}

void GameWindowDialogue::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {

  switch (switchParam) {
  case 0x7d11:
    this->InitializeObject_0x7d11(param_2);
    break;

  case 0x7d3b:
    this->DrawObject_0x7d3b();
    break;

  case 0x7d3c:
    this->RunTick_0x7d3c();
    break;

  case 0x7d0e:
    this->HandleMouseInput_0x7d0e(param_2);
    break;

  case 0x7d05:
    this->UseItem_0x7d05(param_2);
    break;

  case 0x7d2c:
    this->ResolveItemConflict_0x7d2c(param_2, param_3);
    break;

  case 0x7d37:
  case 0x7d0a:
    this->ForwardToSceneHandler_0x7d37_0x7d0a(switchParam, param_2, param_3);
    break;

  case 0x7d20: {
    SceneHandler* sceneHandler;
    SceneHandler* this00;
    int32_t merchantOption = param_2;

    if (this->saveGameWindow != nullptr) {
      this->saveGameWindowCopy = this->saveGameWindow;
      this->saveGameWindow = nullptr;
    }

    switch (merchantOption) {
    case 0x1: {
      sceneHandler = this->mainSceneHandler;
      sceneHandler->primarySwitchSingleParam(0x7d14, 3, 0x0);
      this->saveGameWindow = new GameWindowBuy(this, this->martItemIndexes, this->buyFactor, this->storeType);
      return;
    }
    case 0x2: {
      sceneHandler = this->mainSceneHandler;
      sceneHandler->primarySwitchSingleParam(0x7d14, 3, 0x0);
      this->saveGameWindow = new GameWindowSell(this, this->storeType, this->sellFactor);
      return;
    }
    case 0x3: {
      this00 = this->mainSceneHandler;
      this00->primarySwitchSingleParam(0x7d14, 4, 0x0);
      this->saveGameWindow = new GameWindowMerchant(this);
      break;
    }

    default: {
      this00 = this->mainSceneHandler;
      this00->primarySwitchSingleParam(0x7d14, 4, 0x0);
      this->saveGameWindow = nullptr;
      return;
    }
    }
  } break;

  case 0x7d0c:
    this->CancelOrCloseWindow_0x7d0c();
    break;
  }
}
