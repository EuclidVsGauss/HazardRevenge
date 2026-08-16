#include "HazardPatches.hpp"
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/MusicObjectBase.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardClasses/UnpackedFileBitmap.hpp"
#include "HazardExterns/GameWindowDialogue.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/TextBuffer.hpp"

GameWindowDialogue::GameWindowDialogue(int32_t scriptId, GameWindowBase* teamMember) {
  UnpackedFileBase* ptrEfont;
  UnpackedFileBitmap* ptrTalkbox;
  CoreActClass* actWin4;
  int32_t colorIndex;
  int16_t* colorPtr;
  int32_t* martArrayPtr;
  int32_t* actionArrayPtr;
  int32_t redValue;
  int32_t blueValue;
  int32_t greenValue;
  GameWindowBase* gameWindowAbstract;
  int32_t arrayCount;

  this->teamMember = teamMember;
  this->init0_5 = 0;
  this->flag_mouseclick = -1;
  this->screen_480x640x2 = new char[61440];
  this->struct94kb_1 = new TextBuffer;
  this->struct94kb_2 = new TextBuffer;
  this->dialogueIndex = scriptId;
  this->initZero_posPtr = nullptr;
  martArrayPtr = this->martItemIndexes;
  for (arrayCount = 18; arrayCount != 0; arrayCount = arrayCount + -1) {
    *martArrayPtr = 0;
    martArrayPtr = martArrayPtr + 1;
  }
  if (FontPixelMap == nullptr) {
#if PATCH_USE_KOREAN_FONT
    ptrEfont = UnpackedFileBase::LoadFileFromArchive(s_font_fnt, 0x20000);
    FontPixelMap = (int32_t*)new byte[0x3d00];
    ptrEfont->readFile(FontPixelMap, 0x3d00);
#else
    ptrEfont = UnpackedFileBase::LoadFileFromArchive(s_efont_fnt, 0x20000);
    FontPixelMap = (int32_t*)new byte[0x1000];
    ptrEfont->readFile(FontPixelMap, 0x1000);
#endif
    if (ptrEfont != nullptr) {
      delete ptrEfont;
    }

    ptrTalkbox = UnpackedFileBitmap::ParseBmpFile(s_talkbox_bmp);
    TalkboxImageVector = Create16BitImageFromPalette(ptrTalkbox->imageAddress, ptrTalkbox->length1, ptrTalkbox->length2, ptrTalkbox->shortColorMapAddress);
    delete ptrTalkbox;
  }
  redValue = 0;
  blueValue = 0;
  arrayCount = 0;
  colorPtr = this->coloredScale;
  greenValue = 0;
  do {
    colorIndex = arrayCount + 256;
    arrayCount = (int32_t)(arrayCount + (arrayCount >> 31 & 31U)) >> 5;
    colorPtr[-0x20] = (int16_t)((arrayCount >> ((byte)InvBlueOffset & 31)) << ((byte)BlueOffset1 & 0x1f)) + (int16_t)((arrayCount >> ((byte)InvGreenOffset & 31)) << ((byte)GreenOffset1 & 0x1f)) + (int16_t)((arrayCount >> ((byte)InvRedOffset & 31)) << ((byte)RedOffset1 & 0x1f));
    arrayCount = blueValue + (blueValue >> 31 & 31U);
    blueValue = blueValue + 142;
    *colorPtr = (int16_t)((((int32_t)((greenValue >> 0x1f & 0x1fU) + greenValue) >> 5) >> ((byte)InvBlueOffset & 0x1f)) << ((byte)BlueOffset1 & 0x1f)) + (int16_t)(((arrayCount >> 5) >> ((byte)InvGreenOffset & 0x1f)) << ((byte)GreenOffset1 & 0x1f)) + (int16_t)((((int32_t)(redValue + (redValue >> 0x1f & 0x1fU)) >> 5) >> ((byte)InvRedOffset & 0x1f)) << ((byte)RedOffset1 & 0x1f));
    redValue = redValue + 225;
    arrayCount = colorIndex;
    colorPtr = colorPtr + 1;
    greenValue = greenValue + 66;
  } while (colorIndex < 0x2000);

  actWin4 = new CoreActClass(s_win4_act);
  this->win4Act = actWin4;
  actionArrayPtr = &this->faceFrame;
  for (arrayCount = 20; arrayCount != 0; arrayCount = arrayCount + -1) {
    *actionArrayPtr = -1;
    actionArrayPtr = actionArrayPtr + 1;
  }

  arrayCount = this->win4Act->GetActionIndexByName(s_face);
  this->faceFrame = arrayCount;
  arrayCount = this->win4Act->GetActionIndexByName(s_yesno);
  gameWindowAbstract = this->teamMember;
  this->yesnoFrame = arrayCount;
  this->portraitSprite = nullptr;
  this->saveGameWindow = nullptr;
  this->saveGameWindowCopy = nullptr;
  this->yesNoHighlight = nullptr;
  if (gameWindowAbstract != nullptr) {
    gameWindowAbstract->primarySwitchSingleParam(0x7d06, 0x0, 0x0);
  }
  this->init0_5 = 0;
}
