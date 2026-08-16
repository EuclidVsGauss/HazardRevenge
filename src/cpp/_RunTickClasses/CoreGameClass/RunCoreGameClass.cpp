#include <stdio.h>
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/CoreGameClass.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/MusicObject.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardEnums/DrawLayer.hpp"
#include "HazardExterns/CoreGameClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/WindowReference.hpp"

const int32_t Sidebar_Width_145 = 145;

int32_t CoreGameClass::runTick() {
  GameWindowBase* gameWindowAbstract;
  int32_t frameIdx;
  ImageVectorWithHeader* spriteToRender;
  FILE* screenshotFile;
  int32_t gameWindowIdx;
  int32_t offsetX;

  int32_t tickCount = GetTickCountsAndAsyncStates(&CursorXCoord, &CursorYCoord, &MouseButtonClick);
  PtrMusicObject->UpdateSoundBuffer();
  this->CallsLoadSceneEtc();

  if (tickCount != 0) {
    GameWindowRightSide->PrepareRenderArrays();
    GameWindowLeftSidebar->PrepareRenderArrays();

    for (gameWindowIdx = 9; gameWindowIdx > -1; gameWindowIdx--) {
      int32_t windowAddress = this->initializedGW0s[gameWindowIdx].windowAddress;
      if (windowAddress != -1) {
        gameWindowAbstract = this->gameWindowsArray[windowAddress];
        gameWindowAbstract->primarySwitchSingleParam_DrawObject_0x7d3b(0x0, 0x0);
      }
    }

    GameWindowLeftSidebar->RenderClippedSprite(CursorXCoord, CursorYCoord, this->cursorSprite, DrawLayer::Layer0xFFFD);
    GameWindowRightSide->RenderClippedSprite(CursorXCoord - Sidebar_Width_145, CursorYCoord, this->cursorSprite, DrawLayer::Layer0xFFFD);

    int32_t drawCount = 0;
    if (0 < this->counterDrawObjects) {
      offsetX = -145;
      do {
        frameIdx = this->frameStep;
        CoreActClass* actWin = this->actWin8;
        spriteToRender = nullptr;
        if (frameIdx >= 0) {
          ActContent* content = actWin->txtContent;
          int32_t numFrames = content[frameIdx].numberFrames;
          if (numFrames > 0) {
            spriteToRender = actWin->solidSpriteMap[content[frameIdx].ptrFrameStart[0 % numFrames]];
          }
        }
        (GameWindowRightSide->RenderClippedSprite)(offsetX, 0, spriteToRender, DrawLayer::Layer0xFFFC);
        drawCount = drawCount + 1;
        offsetX = offsetX + -0xd;
      } while (drawCount < this->counterDrawObjects);
    }
    (GameWindowRightSide->RenderWithDirectDrawSurface)();
    (GameWindowLeftSidebar->RenderWithDirectDrawSurface)();
  }

  if ((InputStates128[87] & 17U) == 1) {
    while (true) {
      int32_t saveIdx = ScreenshotCounter;
      ScreenshotCounter = ScreenshotCounter + 1;

      sprintf(ScreenshotFilename, s_haz__d_bmp, saveIdx);
      screenshotFile = fopen(ScreenshotFilename, s_rb);
      if (screenshotFile == nullptr) {
        break;
      }
      fclose(screenshotFile);
    }
    SaveScreenshot(ScreenshotFilename);
  }
  return this->RunTickSwitchIntegerResult;
  return 0;
}
