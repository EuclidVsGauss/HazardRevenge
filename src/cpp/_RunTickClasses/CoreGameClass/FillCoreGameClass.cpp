#include "HazardClasses/CoreActClass.hpp"
#include "HazardClasses/CoreGameClass.hpp"
#include "HazardClasses/GameWindow.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowSidebar.hpp"
#include "HazardClasses/SceneClassUser.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardExterns/CoreGameClass.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActContent.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/CharacterDetails.hpp"
#include "HazardStructs/CharacterEquipment.hpp"
#include "HazardStructs/GameState.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ItemReferenceStruct.hpp"
#include "HazardStructs/NumericalCharacterStats.hpp"

CoreGameClass::CoreGameClass(GameState* globalStruct) {

  UnpackedFileBase* sceneTxtContent;
  CoreActClass* actCursor;
  int32_t frameIndex;
  int32_t dummyFrameIndex;
  ImageVectorWithHeader* cursorSprite;
  GameWindowSidebar* sidebar;
  int32_t partyCounter;
  int32_t andIndex;
  ActiveCharacter** ppCharacter;
  ActiveCharacter* character;
  int32_t* addrGameFlags;
  CharacterDetails* charDetails;
  SceneHandler* autoHandler;
  int32_t slotIndex;
  ActiveCharacter* currentCharacter;
  int32_t i;

  for (i = 0; i < 5; i++) {
    ActiveTeamCharacterSlots[i] = nullptr;
  }

  sceneTxtContent = UnpackedFileBase::LoadFileFromArchive(s_scene_txt, 0x20000);
  ReadInterpolatableString(sceneTxtContent, InterpolatableString, CurrentSceneName);
  if (sceneTxtContent != nullptr) {
    delete sceneTxtContent;
  }
  this->InitializeNewGameConstants();
  LoadItemTxtAndAct();
  GameWindowRightSide = new GameWindow(145, 0, 495, 480);
  GameWindowLeftSidebar = new GameWindow(0, 0, 145, 480);

  this->init0 = 0;
  this->float_600000 = 600000.0;
  this->RunTickSwitchIntegerResult = 0;
  this->currentMusicIndex = 0;

  actCursor = new CoreActClass(s_cursor_act);
  this->actCursor = actCursor;

  actCursor = new CoreActClass(s_win8_act);
  this->actWin8 = actCursor;

  addrGameFlags = &this->frameNormal;
  for (i = 20; i != 0; i = i - 1) {
    *addrGameFlags = -1;
    addrGameFlags = addrGameFlags + 1;
  }

  frameIndex = this->actCursor->GetActionIndexByName(s_normal);
  actCursor = this->actCursor;
  this->frameNormal = frameIndex;

  frameIndex = actCursor->GetActionIndexByName(s_go);
  actCursor = this->actCursor;
  this->frameGo = frameIndex;

  frameIndex = actCursor->GetActionIndexByName(s_dongo);
  actCursor = this->actCursor;
  this->frameDontGo = frameIndex;

  dummyFrameIndex = actCursor->GetActionIndexByName(s_select);
  actCursor = this->actCursor;
  this->frameSelect = dummyFrameIndex;

  frameIndex = actCursor->GetActionIndexByName(s_attack);
  actCursor = this->actCursor;
  this->frameAttack = frameIndex;

  frameIndex = actCursor->GetActionIndexByName(s_ctrl);
  actCursor = this->actCursor;
  this->frameCtrl = frameIndex;

  frameIndex = actCursor->GetActionIndexByName(s_board);
  actCursor = this->actCursor;
  this->frameBoard = frameIndex;

  frameIndex = actCursor->GetActionIndexByName(s_get);
  actCursor = this->actCursor;
  this->frameGet = frameIndex;

  frameIndex = actCursor->GetActionIndexByName(s_open);
  actCursor = this->actCursor;
  this->frameOpen = frameIndex;

  frameIndex = actCursor->GetActionIndexByName(s_talk);
  actCursor = this->actCursor;
  this->frameTalk = frameIndex;

  frameIndex = actCursor->GetActionIndexByName(s_outofsight);
  actCursor = this->actCursor;
  this->frameOutOfSight = frameIndex;

  frameIndex = actCursor->GetActionIndexByName(s_magic);
  actCursor = this->actCursor;
  this->frameMagic = frameIndex;

  frameIndex = actCursor->GetActionIndexByName(s_warp);
  actCursor = this->actWin8;
  this->frameWarp = frameIndex;

  frameIndex = actCursor->GetActionIndexByName(s_step);
  actCursor = this->actCursor;
  this->frameStep = frameIndex;

  frameIndex = this->frameBoard;

  if (0 <= frameIndex && actCursor->txtContent[frameIndex].numberFrames > 0) {
    cursorSprite = actCursor->solidSpriteMap[actCursor->txtContent[frameIndex].ptrFrameStart[(0 % actCursor->txtContent[frameIndex].numberFrames)]];
  }
  else {
    cursorSprite = nullptr;
  }
  this->cursorSprite = cursorSprite;

  int32_t* charBuffer;

  for (i = 0; i < 12; i++) {
    charBuffer = (int32_t*)&this->activeAndCachedScenes[i];
    charBuffer[0] = 0;
    charBuffer[1] = 0;
    charBuffer[2] = 0;
    charBuffer[3] = 0;
    charBuffer[4] = 0;
    charBuffer[5] = 0;
    charBuffer[6] = 0;
  }

  sidebar = new GameWindowSidebar();
  this->StoreAndInitializeObject(sidebar);
  if (globalStruct == nullptr) {
    this->primarySwitchSingleParam(0x7d08, (intptr_t)CurrentSceneName, (intptr_t)&autoHandler);
    autoHandler->primarySwitchSingleParam(0x7d07, (intptr_t)nullptr, 0x0);

    for (andIndex = 2; andIndex != 0; andIndex = andIndex + -1) {
      autoHandler->primarySwitchSingleParam_0x7d2b(0x7, 0x0);
    }

    for (andIndex = 5; andIndex != 0; andIndex = andIndex + -1) {
      autoHandler->primarySwitchSingleParam_0x7d2b(11, 0x0);
    }
    autoHandler->primarySwitchSingleParam_0x7d2b(0x11, 0x0);
    ItemInventory[19].typeId = 15;
    ItemInventory[19].quantity = 1;
    ItemInventory[19].equipFlags = ItemStruct12k->itemArray[15].equipFlags;
    ItemInventory[19].actOffset = ItemStruct12k->itemArray[15].actOffset;
  }
  else {
    this->primarySwitchSingleParam(0x7d08, (intptr_t)globalStruct->sceneLocationName, (intptr_t)&autoHandler);
    autoHandler->primarySwitchSingleParam(0x7d07, (intptr_t)nullptr, 0x0);

    GoldAmount = globalStruct->goldAmount;
    memcpy(ItemInventory, globalStruct->inventoryItems, 32 * sizeof(InventoryItemStruct));
    memcpy(GameFlags, globalStruct->gameFlags, 2048 * sizeof(int32_t));

    for (slotIndex = 0; slotIndex < 10; slotIndex++) {
      charDetails = globalStruct->characterDetails + slotIndex;
      andIndex = charDetails->partyFlag;
      if (andIndex == 0) {
        break;
      }

      partyCounter = andIndex - (andIndex < 11 ? 1 : 11);
      new SceneClassUser(globalStruct->coordX, globalStruct->coordY, CharacterNames[partyCounter], charDetails->largeNumber, 0, 0);

      i = 0;
      while (TeamCharacterList[i] != nullptr) {
        if ((TeamCharacterList[i])->characterId == partyCounter) {
          character = TeamCharacterList[i];
        }
        i++;
      }

      i = 0;
      while (BenchedCharacterList[i] != nullptr) {
        if ((BenchedCharacterList[i])->characterId == partyCounter) {
          character = BenchedCharacterList[i];
        }
        i++;
      }

      memcpy(&character->charEquip, &charDetails->equipment, sizeof(CharacterEquipment));

      character->shiftedSceneClassUser0x48->primarySwitchSingleParam_0x7d3d(&charDetails->stats, 0x0);
      if (charDetails->partyFlag < 11) {
        autoHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(character->shiftedSceneClassUser0x48, 0);
        autoHandler->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a(character->shiftedSceneClassUser0x48, 0);
        autoHandler->primarySwitchSingleParam(0x7d07, (intptr_t)character->shiftedSceneClassUser0x48, 0x0);
      }
      else {
        andIndex = 0;
        currentCharacter = TeamCharacterList[0];
        while (currentCharacter != nullptr) {
          ppCharacter = TeamCharacterList + andIndex;
          if (TeamCharacterList[andIndex] == character) {
            *ppCharacter = TeamCharacterList[andIndex + 1];
            while (*ppCharacter != nullptr) {
              ppCharacter = ppCharacter + 1;
              *ppCharacter = *(ppCharacter + 1);
            }

            andIndex = 0;
            while (BenchedCharacterList[andIndex] != nullptr) {
              andIndex = andIndex + 1;
            }
            BenchedCharacterList[andIndex] = character;
            BenchedCharacterList[andIndex + 1] = nullptr;
          }
          andIndex = andIndex + 1;
          currentCharacter = TeamCharacterList[andIndex];
        }
      }
    }
  }
  ResetRngAndAsyncKeys();
}
