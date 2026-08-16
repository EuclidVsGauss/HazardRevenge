#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowMenu.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardEnums/SoundEffect.hpp"
#include "HazardExterns/GameWindowMenu.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ClickableRectangle1.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/WindowReference.hpp"

const int32_t Menu_Slider_LowerY_251 = 251;
const int32_t Menu_Slider_CenterY_326 = 326;
const int32_t Menu_Width_640 = 640;
const int32_t Menu_Height_480 = 480;

__forceinline void GameWindowMenu::Case_0x7d11(intptr_t param2) {
  WindowReference windowReference;
  windowReference.coords[0] = 0;
  windowReference.coords[1] = 0;
  windowReference.coords[2] = Menu_Width_640;
  windowReference.coords[3] = Menu_Height_480;
  windowReference.windowAddress = (intptr_t)this;
  this->mainSceneHandler = (SceneHandler*)param2;
  this->mainSceneHandler->primarySwitchSingleParam_SetWindow_0x7d16(8, &windowReference);
}

__forceinline void GameWindowMenu::Case_0x7d3b() {
  ImageVectorWithHeader* pSprite;
  int32_t index;
  if (this->showQuitGameMenu != 0) {
    pSprite = __InlineGetSolidSpriteFrameForAction(this->actFrame2, this->menuAct, 0);
    GameWindowRightSide->RenderClippedSprite(-0x91, 0, pSprite, DrawLayer::Layer0xFFFC);
  }
  else {
    pSprite = __InlineGetSolidSpriteFrameForAction(this->actFrame, this->menuAct, 0);
    GameWindowRightSide->RenderClippedSprite(-0x91, 0, pSprite, DrawLayer::Layer0xFFFC);
    pSprite = __InlineGetSolidSpriteFrameForAction(this->actString, this->menuAct, 2);
    index = (TimeResolution_45or15 - 32) * 140;
    GameWindowRightSide->RenderClippedSprite((index / 32) - 215, 0, pSprite, DrawLayer::Layer0xFFFC);
  }
  if (this->highlightedTextSprite != nullptr) {
    GameWindowRightSide->RenderClippedSprite(-0x91, 0, this->highlightedTextSprite, DrawLayer::Layer0xFFFC);
    return;
  }
}

__forceinline void GameWindowMenu::Case_0x7d0e(intptr_t param2) {
  int32_t index;

  if (param2 != 0x0) {
    this->mainSceneHandler->primarySwitchSingleParam_0x7d17(0, 0x0);
    if (this->showQuitGameMenu != 0) {
      for (index = 0; index < 2; index++) {
        if (((CursorXCoord >= MenuWindowClickBoxes[index].lowerX) && (CursorXCoord <= MenuWindowClickBoxes[index].upperX)) && (CursorYCoord >= MenuWindowClickBoxes[index].lowerY && (CursorYCoord <= MenuWindowClickBoxes[index].upperY))) {
          if (this->highlightedTextSprite == nullptr) {
            this->mainSceneHandler->primarySwitchSingleParam(0x7d0a, SoundEffect::MenuClick, (intptr_t)nullptr);
          }
          this->highlightedTextSprite = __InlineGetSolidSpriteFrameForAction(this->actString2, this->menuAct, MenuWindowClickBoxes[index].short1);
          break;
        }
      }
      if (index == 2) {
        this->highlightedTextSprite = nullptr;
      }
      if ((InputStates128[68] & 0x11U) != 1) {
        if ((MouseButtonClick & 0x11) != 1) {
          return;
        }
        if (index == 0) {
          this->mainSceneHandler->primarySwitchSingleParam(0x7d1d, 0, 0x0);
          this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
          return;
        }
        this->showQuitGameMenu = 0;
        return;
      }
      this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
      return;
    }
    else {
      index = CursorYCoord - Menu_Slider_LowerY_251;
      if (index < 0) {
        index = -index;
      }
      if (index <= 8) {
        index = (0x20 - TimeResolution_45or15) * 0x8e;
        index = ((int32_t)(index + (index >> 0x1f & 0x1fU)) >> 5) - Menu_Slider_CenterY_326 + CursorXCoord;
        if (index < 0) {
          index = -index;
        }
        if ((index <= 0x10) && ((MouseButtonClick & 0x11) == 1)) {
          this->sliderIsHeld = 1;
        }
      }
      if (this->sliderIsHeld != 0) {
        TimeResolution_45or15 = (((CursorXCoord - Menu_Slider_CenterY_326) * 32) / 142) + 32;
        if (TimeResolution_45or15 > 64) {
          TimeResolution_45or15 = 64;
        }
        else if (TimeResolution_45or15 < 32) {
          TimeResolution_45or15 = 32;
        }
        if ((MouseButtonClick & 0x11) == 0x10) {
          this->sliderIsHeld = 0;
          return;
        }
      }
      else {
        for (index = 0; index < 2; index++) {
          if ((((CursorXCoord >= MenuWindowClickBoxes_ConfirmQuit[index].lowerX) && (CursorXCoord <= MenuWindowClickBoxes_ConfirmQuit[index].upperX)) && (CursorYCoord >= MenuWindowClickBoxes_ConfirmQuit[index].lowerY)) && (CursorYCoord <= MenuWindowClickBoxes_ConfirmQuit[index].upperY)) {
            if (this->highlightedTextSprite == nullptr) {
              this->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(0x42, nullptr);
            }
            this->highlightedTextSprite = __InlineGetSolidSpriteFrameForAction(this->actString, this->menuAct, MenuWindowClickBoxes_ConfirmQuit[index].short1);
            break;
          }
        }
        if (index == 2) {
          this->highlightedTextSprite = nullptr;
        }
        if ((InputStates128[68] & 0x11U) != 1) {
          if ((MouseButtonClick & 0x11) != 1) {
            return;
          }
          if (index == 0) {
            this->showQuitGameMenu = 1;
            return;
          }
          this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
          return;
        }
        this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)this, 0x0);
        return;
      }
    }
  }
}

__forceinline void GameWindowMenu::Case_0x7d20() {
  this->mainSceneHandler->primarySwitchSingleParam(0x7d0c, (intptr_t)nullptr, 0x0);
}

void GameWindowMenu::primarySwitchSingleParam(int32_t param_1, intptr_t param2, intptr_t param3) {

  (void)param3;
  switch (param_1) {
  case 0x7d11:
    Case_0x7d11(param2);
    return;
  case 0x7d3b:
    Case_0x7d3b();
    return;
  case 0x7d0e:
    Case_0x7d0e(param2);
    break;
  case 0x7d20:
  case 0x7d0c:
    Case_0x7d20();
    break;
  }
}
