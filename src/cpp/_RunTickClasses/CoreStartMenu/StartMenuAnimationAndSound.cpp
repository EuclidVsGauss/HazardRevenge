#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreStartMenu.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SfxObject.hpp"
#include "HazardExterns/CoreStartMenu.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void __fastcall CoreStartMenu::StartMenuAnimationAndSound() {

  int32_t cursorIndex;
  int32_t index;

  if (this->timeResolutionRelated % (TimeResolution_45or15 * 90) == 0) {
    PtrSfxObject->RunPlay(this->menuSnd_psblyLPDIRECTSOUNDBUF, 255, 128);
  }

  this->timeResolutionRelated = this->timeResolutionRelated + 1;
  for (index = 0; index < 4; index++) {
    if (!(((this->cursorX < StartMenuClickBoxes[index].lowerX || (this->cursorX > StartMenuClickBoxes[index].upperX)) || (this->cursorY < StartMenuClickBoxes[index].lowerY)) || (this->cursorY > StartMenuClickBoxes[index].upperY))) {
      if (this->counter == nullptr) {
        PtrSfxObject->RunPlay(ListOfSfxBuffers[66], 255, 128);
      }
      this->counter = this->mainmenuAct->__InlineGetSolidSpriteFrameForAction(this->mainmenuStringIndex, ((StartMenuClickBoxes[index].actionFrame << 1) + 1));
      break;
    }
  }

  if (index == 4) {
    this->counter = nullptr;
  }

  if ((((this->mouseInput & 0x11) == 1) && (this->counter != nullptr)) && (cursorIndex = StartMenuClickBoxes[index].switchCommand, this->selectedMainMenuOption = cursorIndex, cursorIndex != 0x3)) {
    PtrSfxObject->RunPlay(ListOfSfxBuffers[61], 255, 128);
  }
}
