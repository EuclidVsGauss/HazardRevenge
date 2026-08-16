#include <HazardFunctions.hpp>
#include <windows.h>
#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/EventHandler.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/PathfindingState.hpp"
#include "HazardClasses/SceneClassUser.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardClasses/UnpackedFileBitmap.hpp"
#include "HazardExterns/SceneClassUser.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/DefaultCharacterStats.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"
#include "memory.h"

SceneClassUser::SceneClassUser(int32_t userCoord1, int32_t userCoord2, char* userActName, int32_t userFlags, int32_t dialogueScript, int32_t deathScript) {
  int32_t i;

  if (HasLoadedDefaultTxt == 0) {
    UnpackedFileBase* defaultTxtContent = UnpackedFileBase::LoadFileFromArchive(s_default_txt, 0x20000);
    if (defaultTxtContent != nullptr) {
      int32_t foundIndex = 0;
      char characterName[20];

      while (true) {

        ReadInterpolatableString(defaultTxtContent, InterpolatableString, characterName);

        foundIndex = 0;
        while (foundIndex < 10) {
          if (strcmp(characterName, ListOfDefaultCharacterStats[foundIndex].NamePointer) == 0) {
            break;
          }
          foundIndex++;
        }

        if (foundIndex < 10) {

          ReadInterpolatableString(defaultTxtContent, s__d__d__d__d__d__d__d__d,
                                   &ListOfDefaultCharacterStats[foundIndex].CurrentHp,
                                   &ListOfDefaultCharacterStats[foundIndex].MaxHp,
                                   &ListOfDefaultCharacterStats[foundIndex].CurrentMp,
                                   &ListOfDefaultCharacterStats[foundIndex].MaxMp,
                                   &ListOfDefaultCharacterStats[foundIndex].Power,
                                   &ListOfDefaultCharacterStats[foundIndex].ToHit,
                                   &ListOfDefaultCharacterStats[foundIndex].Guard,
                                   &ListOfDefaultCharacterStats[foundIndex].Speed);

          ReadInterpolatableString(defaultTxtContent, s__d__d__d__d__d,
                                   &ListOfDefaultCharacterStats[foundIndex].FireResistance,
                                   &ListOfDefaultCharacterStats[foundIndex].IceResistance,
                                   &ListOfDefaultCharacterStats[foundIndex].LightningResistance,
                                   &ListOfDefaultCharacterStats[foundIndex].WindResistance,
                                   &ListOfDefaultCharacterStats[foundIndex].LandResistance);

          ReadInterpolatableString(defaultTxtContent, s__d__d__d__d__d__d__d__d__d,
                                   &ListOfDefaultCharacterStats[foundIndex].Eye,
                                   &ListOfDefaultCharacterStats[foundIndex].Barrage,
                                   &ListOfDefaultCharacterStats[foundIndex].PowerGrowth,
                                   &ListOfDefaultCharacterStats[foundIndex].ToHitGrowth,
                                   &ListOfDefaultCharacterStats[foundIndex].GuardGrowth,
                                   &ListOfDefaultCharacterStats[foundIndex].SpeedGrowth,
                                   &ListOfDefaultCharacterStats[foundIndex].Experience,
                                   &ListOfDefaultCharacterStats[foundIndex].Level,
                                   &ListOfDefaultCharacterStats[foundIndex].SpriteOutfitLevel);
        }

        if (ListOfDefaultCharacterStats[foundIndex].NamePointer == nullptr) {
          break;
        }
      }

      delete defaultTxtContent;
    }
    HasLoadedDefaultTxt = 1;
  }

  this->nameAsAct = nullptr;
  this->genericAct = nullptr;

  FillMemory(&this->actStand, sizeof(this->actStand) * 20, 0xff);

  char* actName = userActName;
  int32_t characterIndex = -1;
  for (i = 0; i < 10; i++) {
    if (strcmp(ListOfDefaultCharacterStats[i].NamePointer, actName) == 0) {
      characterIndex = i;
      break;
    }
  }

  if (characterIndex < 0 || characterIndex >= 10) {
    strcpy(this->names, actName);
    strcpy(this->townSpriteRelated, actName);
    this->primarySwitchSingleParam(0x7d24, 0, 1);
  }
  else {

    NumericalCharacterStats* stats = &this->numericalCharacterStats;
    memcpy(stats, &ListOfDefaultCharacterStats[characterIndex].CurrentHp, 96);
    this->CreateCharacterAndInitialiseEquipment(stats, ListOfDefaultCharacterStats[characterIndex].Id);

    char* nameSrc = (&ListOfDefaultCharacterStats[characterIndex].Battle1)[ListOfDefaultCharacterStats[characterIndex].SpriteOutfitLevel * 2];
    strcpy(this->names, nameSrc);

    char* townSrc = (&ListOfDefaultCharacterStats[characterIndex].Town1)[ListOfDefaultCharacterStats[characterIndex].SpriteOutfitLevel * 2];
    strcpy(this->townSpriteRelated, townSrc);

    int32_t teamIndex = 0;
    ActiveCharacter** teamList = TeamCharacterList;
    while (teamList[teamIndex] != nullptr) {
      if (teamList[teamIndex]->shiftedSceneClassUser0x48 == this) {
        break;
      }
      teamIndex++;
    }
    if (teamList[teamIndex] == nullptr) {
      __InlineQueueEvent(0x7d20);
    }
  }

  int32_t rng = PseudoRng();
  this->orientation = (rng % 9) % 8;

  this->triggerScriptIdOnTalk = dialogueScript;
  this->voluntaryActionSwitchFlag = 0x7d21;
  this->statusInternalTimer = 0;
  this->frameIndexRelated = 0;
  this->allySupportPathfinding = nullptr;
  this->pathfindingInputObj = nullptr;
  this->triggerScriptIdOnDeath = deathScript;
  this->userFlags = userFlags;
  this->objectListId = this->TrackObjects(userFlags);

  this->floatMultiplier2_pos2 = userCoord2;
  this->floatMultiplier1_pos1 = userCoord1;
  this->floatTimesMultiplier1 = (float)userCoord1 * GridMultiplier_16;
  this->floatTimesMultiplier2 = (float)userCoord2 * GridMultiplier_16;

  this->UpdateObjectOnGrid(userCoord1 << 4, userCoord2 << 4);

  this->__InlineableQueueEvent(this->floatMultiplier2_pos2);
  this->__InlineableQueueEvent(this->floatMultiplier1_pos1);
  this->__InlineableQueueEvent(0x7d1f);

  if (LoadMark2 == nullptr) {
    UnpackedFileBitmap* bmpObject = UnpackedFileBitmap::ParseBmpFile(s_mark2_bmp);
    LoadMark2 = DecodeSolidSprite(bmpObject->imageAddress, bmpObject->length1, bmpObject->length2,
                                           0, bmpObject->shortColorMapAddress, bmpObject->length1 / 2, bmpObject->length2 / 2);
    delete bmpObject;
  }

  this->statusCondition = UnitStatusCondition::Normal;
}
