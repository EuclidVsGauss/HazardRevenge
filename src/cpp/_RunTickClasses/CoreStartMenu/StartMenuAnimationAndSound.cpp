#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/CoreStartMenu.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/SfxObject.hpp"
#include "HazardExterns/CoreStartMenu.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ClickableRectangle3.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"

void __fastcall CoreStartMenu::StartMenuAnimationAndSound() {

  int32_t cursorIndex;
  int32_t index;

  if (this->timeResolutionRelated % (TimeResolution_45or15 * 90) == 0) {
    PtrSfxObject->RunPlay(this->menuSnd_psblyLPDIRECTSOUNDBUF, 255, 128);
  }

  this->timeResolutionRelated = this->timeResolutionRelated + 1;
  for (index = 0; index < 4; index++) {
    if (!(((this->cursorX < StartMenuClickBoxes[index].upperX || (this->cursorX > StartMenuClickBoxes[index].lowerX)) || (this->cursorY < StartMenuClickBoxes[index].upperY)) || (this->cursorY > StartMenuClickBoxes[index].lowerY))) {
      if (this->counter == nullptr) {
        PtrSfxObject->RunPlay(ListOfSfxBuffers[66], 255, 128);
      }
      this->counter = GameWindowBase::__InlineGetSolidSpriteFrameForAction(this->mainmenuStringIndex, this->mainmenuAct, ((StartMenuClickBoxes[index].indexLike2 << 1) + 1));
      break;
    }
  }

  if (index == 4) {
    this->counter = nullptr;
  }

  if ((((this->mouseInput & 0x11) == 1) && (this->counter != nullptr)) && (cursorIndex = StartMenuClickBoxes[index].indexLike, this->selectedMainMenuOption = cursorIndex, cursorIndex != 0x3)) {
    PtrSfxObject->RunPlay(ListOfSfxBuffers[61], 255, 128);
  }
}
