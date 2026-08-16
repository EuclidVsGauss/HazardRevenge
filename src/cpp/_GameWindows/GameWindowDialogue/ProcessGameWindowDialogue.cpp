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

__forceinline void Case_0x7d11(GameWindowDialogue* gameWindow4, intptr_t param_2) {
  WindowReference windowReference;

  GameWindowBase* teamMemberWindow;
  SceneClassCameraBase* sceneCamera;
  UnpackedFileBase* loadedScript;
  uint32_t readCharacter;
  int32_t dialogueId;

  gameWindow4->mainSceneHandler = (SceneHandler*)param_2;
  windowReference.windowAddress = (intptr_t)gameWindow4;

  windowReference.coords[0] = 0;
  windowReference.coords[3] = 480;
  windowReference.coords[2] = 640;
  windowReference.coords[1] = 0;

  gameWindow4->mainSceneHandler->primarySwitchSingleParam_SetWindow_0x7d16(5, &windowReference);
  teamMemberWindow = gameWindow4->teamMember;
  if (teamMemberWindow != nullptr) {
    sceneCamera = teamMemberWindow->mainSceneHandler->sceneCamera;
    sceneCamera->primarySwitchSingleParam(0x7d21, teamMemberWindow->matrixIndexXTimes16 << 4, teamMemberWindow->matrixIndexYTimes16 << 4);
  }
  loadedScript = UnpackedFileBase::LoadFileFromArchive(s_script_e_txt, 0x20000);
  gameWindow4->ptrScriptTxt = loadedScript;
  do {
    readCharacter = gameWindow4->ptrScriptTxt->readByte();
    while (readCharacter != L'#') {
      if ((int32_t)readCharacter < 0) {

        gameWindow4->dialogueIndex = 0;
        gameWindow4->mainSceneHandler->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(gameWindow4, 0x0);
        return;
      }
      readCharacter = gameWindow4->ptrScriptTxt->readByte();
    }
    ReadInterpolatableString(gameWindow4->ptrScriptTxt, s__d, &dialogueId);
  } while (dialogueId != gameWindow4->dialogueIndex);
}

__forceinline void Case_0x7d3b(GameWindowDialogue* gameWindow4) {
  GameWindowBase* savedWindow;
  ImageVectorWithHeader* sprite;

  if (gameWindow4->dialogueIndex == 0) {
    return;
  }
  if (gameWindow4->flag_mouseclick < 0) {
    return;
  }
  savedWindow = gameWindow4->saveGameWindow;
  if (savedWindow != nullptr) {
    savedWindow->primarySwitchSingleParam_DrawObject_0x7d3b(0x0, 0x0);
    return;
  }
  if (gameWindow4->initZero_posPtr != nullptr) {
    GameWindowRightSide->RenderClippedRectangle(0, 0x181, (int16_t*)gameWindow4->initZero_posPtr->textWideBytes, 0x1ef, 0x5f, DrawLayer::Layer0xFFF8);
    if (gameWindow4->portraitSprite != nullptr) {
      GameWindowRightSide->RenderClippedSprite(20, 409, gameWindow4->portraitSprite, DrawLayer::Layer0xFFF9);
    }
  }
  if (gameWindow4->flag_mouseclick != 1) {
    return;
  }

  sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(gameWindow4->yesnoFrame, gameWindow4->win4Act, 0);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, sprite, DrawLayer::Layer0xFFF9);

  sprite = GameWindowBase::__InlineGetSolidSpriteFrameForAction(gameWindow4->yesnoFrame, gameWindow4->win4Act, 1);
  GameWindowRightSide->RenderClippedSprite(-0x91, 0, sprite, DrawLayer::Layer0xFFF9);
  if (gameWindow4->yesNoHighlight != nullptr) {
    GameWindowRightSide->RenderClippedSprite(-145, 0, gameWindow4->yesNoHighlight, DrawLayer::Layer0xFFF9);
  }
}

__forceinline void Case_0x7d3c(GameWindowDialogue* gameWindow4) {
  gameWindow4->ParseScriptTxt();
}

__forceinline void Case_0x7d0e(GameWindowDialogue* gameWindow4, intptr_t param_2) {
  SceneHandler* sceneHandler;
  ImageVectorWithHeader* highlightSprite;

  int32_t compareResult;
  int32_t nestingDepth;

  uint32_t readCharacter;
  char readString[200];

  gameWindow4->yesNoHighlight = nullptr;
  if (param_2 == 0x0) {
    return;
  }
  sceneHandler = gameWindow4->mainSceneHandler;
  sceneHandler->primarySwitchSingleParam_0x7d17(9, 0x0);
  if (gameWindow4->saveGameWindow != nullptr) {
    sceneHandler = gameWindow4->mainSceneHandler;
    sceneHandler->primarySwitchSingleParam_0x7d17(0, 0x0);
    gameWindow4->saveGameWindow->primarySwitchSingleParam(0x7d0e, 0x0, 0x0);
    return;
  }

  if (gameWindow4->flag_mouseclick == 1) {

    if ((((DialogueWindow_YesButton_LowerX_524 < CursorXCoord) && (CursorXCoord < DialogueWindow_YesButton_UpperX_574)) && (DialogueWindow_Buttons_LowerY_453 < CursorYCoord)) && (CursorYCoord < DialogueWindow_Buttons_UpperY_469)) {
      highlightSprite = GameWindowDialogue::__InlineGetSolidSpriteFrameForAction(gameWindow4->yesnoFrame, gameWindow4->win4Act, 2);
      gameWindow4->yesNoHighlight = highlightSprite;
    }

    if (((DialogueWindow_NoButton_LowerX_578 < CursorXCoord) && (CursorXCoord < DialogueWindow_NoButton_UpperX_628)) && (DialogueWindow_Buttons_LowerY_453 < CursorYCoord && (CursorYCoord < DialogueWindow_Buttons_UpperY_469))) {
      highlightSprite = GameWindowDialogue::__InlineGetSolidSpriteFrameForAction(gameWindow4->yesnoFrame, gameWindow4->win4Act, 3);
      gameWindow4->yesNoHighlight = highlightSprite;
    }

    if ((MouseButtonClick & 0x11) == 1) {
      if (((DialogueWindow_YesButton_LowerX_524 < CursorXCoord) && (CursorXCoord < DialogueWindow_YesButton_UpperX_574)) && (DialogueWindow_Buttons_LowerY_453 < CursorYCoord && (CursorYCoord < DialogueWindow_Buttons_UpperY_469))) {
        gameWindow4->flag_mouseclick = 0;
      }
      if ((((DialogueWindow_NoButton_LowerX_578 < CursorXCoord) && (CursorXCoord < DialogueWindow_NoButton_UpperX_628)) && (DialogueWindow_Buttons_LowerY_453 < CursorYCoord)) && (CursorYCoord < DialogueWindow_Buttons_UpperY_469)) {
        nestingDepth = 0;
        do {
          ReadInterpolatableString(gameWindow4->ptrScriptTxt, InterpolatableString, readString);
          if (readString[0] == ';') {
            readCharacter = gameWindow4->ptrScriptTxt->readByte();
            while (readCharacter != '\n') {
              readCharacter = gameWindow4->ptrScriptTxt->readByte();
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
        } while (((compareResult != 0) || (nestingDepth != 0)) && (-1 < nestingDepth));
        gameWindow4->flag_mouseclick = 0;
      }
    }
  }
  else {
    if (((MouseButtonClick & 0x22) == 2) && (7 < gameWindow4->init0_5)) {
      gameWindow4->init0_5 = 8;
    }
    if (InputStates128[29] == '\0') {
      return;
    }
    gameWindow4->init0_5 = gameWindow4->init0_5 + -64;
    return;
  }
}

__forceinline void Case_0x7d05(GameWindowDialogue* gameWindow4, intptr_t param_2) {
  GameWindowBase* teamMember;

  teamMember = gameWindow4->teamMember;
  if (teamMember != nullptr) {
    teamMember->primarySwitchSingleParam_0x7d05(param_2, 0x0);
  }
}

__forceinline void Case_0x7d2c(GameWindowDialogue* gameWindow4, intptr_t param_2, intptr_t param_3) {
  SceneHandler* teamSceneHandler;

  if (gameWindow4->teamMember != nullptr) {
    teamSceneHandler = gameWindow4->teamMember->mainSceneHandler;
    teamSceneHandler->primarySwitchSingleParam_0x7d2c((void*)param_2, param_3);
  }
}

__forceinline void Case_0x7d37_0x7d0a(GameWindowDialogue* gameWindow4, int32_t switchParam, intptr_t param_2, intptr_t param_3) {
  SceneHandler* sceneHandler;

  sceneHandler = gameWindow4->mainSceneHandler;
  sceneHandler->primarySwitchSingleParam(switchParam, param_2, param_3);
}

__forceinline void Case_0x7d0c(GameWindowDialogue* gameWindow4) {
  gameWindow4->mainSceneHandler->primarySwitchSingleParam_0x7d14(4, 0x0);
  gameWindow4->saveGameWindowCopy = gameWindow4->saveGameWindow;
  gameWindow4->saveGameWindow = nullptr;
}

void GameWindowDialogue::primarySwitchSingleParam(int32_t switchParam, intptr_t param_2, intptr_t param_3) {
  GameWindowDialogue* gameWindow4 = this;

  switch (switchParam) {
  case 0x7d11:
    Case_0x7d11(gameWindow4, param_2);
    break;

  case 0x7d3b:
    Case_0x7d3b(gameWindow4);
    break;

  case 0x7d3c:
    Case_0x7d3c(gameWindow4);
    break;

  case 0x7d0e:
    Case_0x7d0e(gameWindow4, param_2);
    break;

  case 0x7d05:
    Case_0x7d05(gameWindow4, param_2);
    break;

  case 0x7d2c:
    Case_0x7d2c(gameWindow4, param_2, param_3);
    break;

  case 0x7d37:
  case 0x7d0a:
    Case_0x7d37_0x7d0a(gameWindow4, switchParam, param_2, param_3);
    break;

  case 0x7d20: {
    SceneHandler* sceneHandler;
    GameWindowBuy* buyWindow;
    GameWindowSell* sellWindow;
    GameWindowMerchant* merchantWindow;
    SceneHandler* this00;
    int32_t param3AsInt = param_2;

    if (gameWindow4->saveGameWindow != nullptr) {
      gameWindow4->saveGameWindowCopy = gameWindow4->saveGameWindow;
      gameWindow4->saveGameWindow = nullptr;
    }

    switch (param3AsInt) {
    case 0x3: {
      this00 = gameWindow4->mainSceneHandler;
      this00->primarySwitchSingleParam_0x7d14(4, 0x0);
      merchantWindow = new GameWindowMerchant(gameWindow4);
      if (merchantWindow != nullptr) {
        gameWindow4->saveGameWindow = merchantWindow;
        return;
      }
      break;
    }
    case 0x2: {
      sceneHandler = gameWindow4->mainSceneHandler;
      sceneHandler->primarySwitchSingleParam_0x7d14(3, 0x0);
      sellWindow = new GameWindowSell(gameWindow4, gameWindow4->storeType, gameWindow4->sellFactor);
      if (sellWindow != nullptr) {
        gameWindow4->saveGameWindow = sellWindow;
        return;
      }
      break;
    }
    case 0x1: {
      sceneHandler = gameWindow4->mainSceneHandler;
      sceneHandler->primarySwitchSingleParam_0x7d14(3, 0x0);
      buyWindow = new GameWindowBuy(gameWindow4, gameWindow4->martItemIndexes, gameWindow4->buyFactor, gameWindow4->storeType);
      if (buyWindow != nullptr) {
        gameWindow4->saveGameWindow = buyWindow;
        return;
      }
      break;
    }

    default: {
      this00 = gameWindow4->mainSceneHandler;
      this00->primarySwitchSingleParam_0x7d14(4, 0x0);
      gameWindow4->saveGameWindow = nullptr;
      return;
    }
    }
  } break;

  case 0x7d0c:
    Case_0x7d0c(gameWindow4);
    break;
  }
}
