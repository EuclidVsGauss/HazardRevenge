#include "HazardClasses/SceneClassUser.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"

ActiveCharacter* __fastcall GameWindowBase::GetCharacterObject() {
  int32_t teamIndex;

  for (teamIndex = 0; TeamCharacterList[teamIndex] != nullptr; teamIndex++) {
    if (TeamCharacterList[teamIndex]->sceneClassUser == this) {
      break;
    }
  }
  return TeamCharacterList[teamIndex];
}
