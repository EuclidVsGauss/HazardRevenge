#include "HazardClasses/AnimationSpell.hpp"
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/GameWindowBase.hpp"
#include "HazardClasses/GameWindowDialogue.hpp"
#include "HazardClasses/GameWindowMerchant.hpp"
#include "HazardClasses/GameWindowRegroup.hpp"
#include "HazardClasses/GameWindowSave.hpp"
#include "HazardClasses/GridHandler.hpp"
#include "HazardClasses/MusicObjectBase.hpp"
#include "HazardClasses/SceneClassAnimatedBackground.hpp"
#include "HazardClasses/SceneClassBoss.hpp"
#include "HazardClasses/SceneClassBox.hpp"
#include "HazardClasses/SceneClassButton.hpp"
#include "HazardClasses/SceneClassCameraBase.hpp"
#include "HazardClasses/SceneClassCloud.hpp"
#include "HazardClasses/SceneClassDoor.hpp"
#include "HazardClasses/SceneClassGate.hpp"
#include "HazardClasses/SceneClassMoveTile.hpp"
#include "HazardClasses/SceneClassNoise.hpp"
#include "HazardClasses/SceneClassSwitch.hpp"
#include "HazardClasses/SceneClassUser.hpp"
#include "HazardClasses/SceneHandler.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardEnums/MapType.hpp"
#include "HazardEnums/ScriptCommand.hpp"
#include "HazardExterns/GameWindowDialogue.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardStructs/InventoryItemStruct.hpp"
#include "HazardStructs/ObjectWrapper.hpp"
#include "HazardStructs/StringIntegerMap.hpp"
#include "HazardStructs/TextBuffer.hpp"

void GameWindowDialogue::ParseScriptTxt() {
  GameWindowBase* thisgwb;
  GameWindowBase* previousSceneWindow;
  byte currentCharByte;
  uint32_t nextCharByte;
  int32_t scriptCmdIndex;
  WORD* flagWordPtr;
  SceneClassUser* newSceneUser;
  InventoryItemStruct* currentItem;
  GameWindowBase* newSceneObject;
  GameWindowBase* ptrAct_size172struct;
  int32_t equipSlotIndex;
  int32_t countdownTimer;
  int32_t scriptVarValue;
  char* scriptVarStrPtr;
  int32_t startsWithExclamationMark;
  int32_t portraitId;
  ImageVectorWithHeader* portraitFrame;
  char output1[16];
  char output2[200];

  if (this->saveGameWindow != nullptr) {
    this->initZero_posPtr = nullptr;
    return;
  }
  {
    thisgwb = this->saveGameWindowCopy;
    if (thisgwb != nullptr) {
      delete thisgwb;
      this->saveGameWindowCopy = nullptr;
    }
    if (((this->flag_mouseclick != 1) && (countdownTimer = this->init0_5, this->init0_5 = countdownTimer + -1, countdownTimer <= 0)) || (this->saveGameWindow != nullptr)) {
      while (true) {
        ReadInterpolatableString(this->ptrScriptTxt, InterpolatableString, output2);
        if (output2[0] == ';') {
          nextCharByte = this->ptrScriptTxt->readByte();
          while (nextCharByte != '\n') {
            nextCharByte = this->ptrScriptTxt->readByte();
          }
          if (output2[0] == ';') {
            continue;
          }
        }
        if (output2[0] == '#') {
          this->mainSceneHandler->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(this, 0x0);
          return;
        }
        for (scriptCmdIndex = 0; ScriptCommand_ARRAY[scriptCmdIndex].Key != nullptr; scriptCmdIndex = scriptCmdIndex + 1) {
          if (strcmp(ScriptCommand_ARRAY[scriptCmdIndex].Key, output2) == 0) {
            break;
          }
        }

        switch ((char)ScriptCommand_ARRAY[scriptCmdIndex].Value) {
        case ScriptCommand::script_if:
          ReadInterpolatableString(this->ptrScriptTxt, InterpolatableString, output1);
          startsWithExclamationMark = output1[0] == '!';
          scriptVarStrPtr = output1 + startsWithExclamationMark;

          if ((atoi(scriptVarStrPtr) > 0) && (atoi(scriptVarStrPtr) <= 10)) {
            for (scriptCmdIndex = 0; TeamCharacterList[scriptCmdIndex] != nullptr; scriptCmdIndex = scriptCmdIndex + 1) {
              if (this->teamMember == TeamCharacterList[scriptCmdIndex]->sceneClassUser) {
                break;
              }
            }
            flagWordPtr = ((TeamCharacterList[scriptCmdIndex] != nullptr) && (TeamCharacterList[scriptCmdIndex]->characterId + 1 == atoi(scriptVarStrPtr))) ? (WORD*)Script_0_0 : (WORD*)Scrip_1_0;
            *(int16_t*)scriptVarStrPtr = *flagWordPtr;
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }
          else if (atoi(scriptVarStrPtr) == 0) {
            ReadInterpolatableString(this->ptrScriptTxt, InterpolatableString, output1);
            startsWithExclamationMark = output1[0] == '!';
            scriptVarStrPtr = output1 + startsWithExclamationMark;

            flagWordPtr = ((int32_t)GoldAmount < atoi(scriptVarStrPtr)) ? (WORD*)Scrip_1_0 : (WORD*)Script_0_0;
            *(int16_t*)scriptVarStrPtr = *flagWordPtr;
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          if (atoi(scriptVarStrPtr) == 0xb) {
            flagWordPtr = (GoldAmount == 0) ? (WORD*)Scrip_1_0 : (WORD*)Script_0_0;
            *(int16_t*)scriptVarStrPtr = *flagWordPtr;
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          if (atoi(scriptVarStrPtr) == 0xc) {
            this->flag_mouseclick = 1;
            return;
          }

          if (atoi(scriptVarStrPtr) == 0xd) {
            for (scriptCmdIndex = 0; TeamCharacterList[scriptCmdIndex] != nullptr; scriptCmdIndex = scriptCmdIndex + 1) {
            }
            for (scriptVarValue = 0; scriptVarValue < 5; scriptVarValue = scriptVarValue + 1) {
              if (ActiveTeamCharacterSlots[scriptVarValue] != nullptr) {
                scriptCmdIndex = scriptCmdIndex + 1;
              }
            }
            flagWordPtr = (scriptCmdIndex == 5) ? (WORD*)Script_0_0 : (WORD*)Scrip_1_0;
            *(int16_t*)scriptVarStrPtr = *flagWordPtr;
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          if (atoi(scriptVarStrPtr) == 0xe) {
            for (scriptCmdIndex = 0; TeamCharacterList[scriptCmdIndex] != nullptr; scriptCmdIndex = scriptCmdIndex + 1) {
              if (TeamCharacterList[scriptCmdIndex]->sceneClassUser->mainSceneHandler->mapType == MapType::Field) {
                break;
              }
            }
            flagWordPtr = (TeamCharacterList[scriptCmdIndex] == nullptr) ? (WORD*)Script_0_0 : (WORD*)Scrip_1_0;
            *(int16_t*)scriptVarStrPtr = *flagWordPtr;
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          if (atoi(scriptVarStrPtr) == 0xf) {
            scriptVarValue = 0;
            equipSlotIndex = 0;
            while (TeamCharacterList[scriptVarValue] != nullptr) {
              currentItem = (InventoryItemStruct*)&TeamCharacterList[scriptVarValue]->charEquip + equipSlotIndex;
              if ((currentItem->typeId == 0xae) && (currentItem->quantity > 0)) {
                break;
              }
              equipSlotIndex = equipSlotIndex + 1;
              if (equipSlotIndex >= 0x2c) {
                scriptVarValue = scriptVarValue + 1;
                equipSlotIndex = 0;
              }
            }
            if (TeamCharacterList[scriptVarValue] == nullptr) {
              scriptVarValue = 0;
              equipSlotIndex = 0;
              while (BenchedCharacterList[scriptVarValue] != nullptr) {
                currentItem = (InventoryItemStruct*)&BenchedCharacterList[scriptVarValue]->charEquip + equipSlotIndex;
                if ((currentItem->typeId == 0xae) && (currentItem->quantity > 0)) {
                  break;
                }
                equipSlotIndex = equipSlotIndex + 1;
                if (equipSlotIndex >= 0x2c) {
                  scriptVarValue = scriptVarValue + 1;
                  equipSlotIndex = 0;
                }
              }
              flagWordPtr = (BenchedCharacterList[scriptVarValue] == nullptr) ? (WORD*)Scrip_1_0 : (WORD*)Script_0_0;
              *(int16_t*)scriptVarStrPtr = *flagWordPtr;
            }
            else {
              *(int16_t*)scriptVarStrPtr = *(WORD*)Script_0_0;
            }
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          if (atoi(scriptVarStrPtr) == 0x10) {
            scriptVarValue = 0;
            equipSlotIndex = 0;
            while (TeamCharacterList[scriptVarValue] != nullptr) {
              currentItem = (InventoryItemStruct*)&TeamCharacterList[scriptVarValue]->charEquip + equipSlotIndex;
              if ((currentItem->typeId == 0xb0) && (currentItem->quantity > 0)) {
                break;
              }
              equipSlotIndex = equipSlotIndex + 1;
              if (equipSlotIndex >= 0x2c) {
                scriptVarValue = scriptVarValue + 1;
                equipSlotIndex = 0;
              }
            }
            if (TeamCharacterList[scriptVarValue] == nullptr) {
              scriptVarValue = 0;
              equipSlotIndex = 0;
              while (BenchedCharacterList[scriptVarValue] != nullptr) {
                currentItem = (InventoryItemStruct*)&BenchedCharacterList[scriptVarValue]->charEquip + equipSlotIndex;
                if ((currentItem->typeId == 0xb0) && (currentItem->quantity > 0)) {
                  break;
                }
                equipSlotIndex = equipSlotIndex + 1;
                if (equipSlotIndex >= 0x2c) {
                  scriptVarValue = scriptVarValue + 1;
                  equipSlotIndex = 0;
                }
              }
              flagWordPtr = (BenchedCharacterList[scriptVarValue] == nullptr) ? (WORD*)Scrip_1_0 : (WORD*)Script_0_0;
              *(int16_t*)scriptVarStrPtr = *flagWordPtr;
            }
            else {
              *(int16_t*)scriptVarStrPtr = *(WORD*)Script_0_0;
            }
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          if (atoi(scriptVarStrPtr) < 0) {
            for (scriptCmdIndex = 0; scriptCmdIndex < 32; scriptCmdIndex = scriptCmdIndex + 1) {
              if ((0 < ItemInventory[scriptCmdIndex].quantity) && (ItemInventory[scriptCmdIndex].typeId == -atoi(scriptVarStrPtr))) {
                break;
              }
            }
            flagWordPtr = (scriptCmdIndex == 0x20) ? (WORD*)Scrip_1_0 : (WORD*)Script_0_0;
            *(WORD*)scriptVarStrPtr = *flagWordPtr;
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          if (GameFlags[atoi(scriptVarStrPtr)] == startsWithExclamationMark) {
            scriptCmdIndex = 0;
            do {
              ReadInterpolatableString(this->ptrScriptTxt, InterpolatableString, output2);
              if (output2[0] == ';') {
                nextCharByte = this->ptrScriptTxt->readByte();
                while (nextCharByte != '\n') {
                  nextCharByte = this->ptrScriptTxt->readByte();
                }
              }
              if ((output2[0] == '\"') && (output2[strlen(output2) - 1] != '\"')) {
                nextCharByte = this->ptrScriptTxt->readByte();
                while (nextCharByte != '\"') {
                  nextCharByte = this->ptrScriptTxt->readByte();
                }
              }

              scriptVarValue = strcmp(output2, s_if);
              if (scriptVarValue == 0) {
                scriptCmdIndex = scriptCmdIndex + 1;
              }

              scriptVarValue = strcmp(output2, s_endif);
              if (scriptVarValue == 0) {
                scriptCmdIndex = scriptCmdIndex + -1;
              }

              scriptVarValue = strcmp(output2, s_elseif);
            } while (((scriptVarValue != 0) || (scriptCmdIndex != 0)) && (scriptCmdIndex >= 0));
          }
          continue;

        case ScriptCommand::script_elseif:
          scriptCmdIndex = 0;
          do {
            ReadInterpolatableString(this->ptrScriptTxt, InterpolatableString, output2);
            if (output2[0] == ';') {
              nextCharByte = this->ptrScriptTxt->readByte();
              while (nextCharByte != '\n') {
                nextCharByte = this->ptrScriptTxt->readByte();
              }
            }

            scriptVarValue = strcmp(output2, s_if);
            if (scriptVarValue == 0) {
              scriptCmdIndex = scriptCmdIndex + 1;
            }

            scriptVarValue = strcmp(output2, s_endif);
            if (scriptVarValue == 0) {
              scriptCmdIndex = scriptCmdIndex + -1;
            }
          } while (scriptCmdIndex >= 0);

        case ScriptCommand::script_endif:
          continue;

        default:
          WrapperMessageBoxA((LPCSTR)output2, s_talkbox__wrong_message);
          continue;

        case ScriptCommand::script_say2:
          nextCharByte = this->ptrScriptTxt->readByte();
          while (nextCharByte != '"') {
            nextCharByte = this->ptrScriptTxt->readByte();
          }
          scriptCmdIndex = 0;
          currentCharByte = (byte)this->ptrScriptTxt->readByte();
          output2[0] = currentCharByte;
          while (currentCharByte != '"') {
            scriptCmdIndex = scriptCmdIndex + 1;
            currentCharByte = (byte)this->ptrScriptTxt->readByte();
            output2[scriptCmdIndex] = currentCharByte;
          }
          output2[scriptCmdIndex] = 0;
          this->Talkbox(output2, 1);
          this->init0_5 = 640;
          this->flag_mouseclick = 0;
          return;

        case ScriptCommand::script_door: {
          int32_t coord1;
          int32_t coord2;
          int32_t orientation;
          int32_t gameFlag;
          char actFilename[16];

          ReadInterpolatableString(this->ptrScriptTxt, s__s__d__d__d__d, actFilename, &coord1, &coord2, &orientation, &gameFlag);
          if (this->teamMember == nullptr) {
            continue;
          }
          newSceneObject = new SceneClassDoor(coord1, coord2, orientation, gameFlag, actFilename);
          break;
        }

        case ScriptCommand::script_button: {
          int32_t coord1;
          int32_t coord2;
          int32_t orientation;
          int32_t gameFlag;
          char actFilename[14];

          ReadInterpolatableString(this->ptrScriptTxt, s__s__d__d__d__d, actFilename, &coord1, &coord2, &orientation, &gameFlag);
          if (this->teamMember == nullptr) {
            continue;
          }
          newSceneObject = new SceneClassButton(coord1, coord2, orientation, gameFlag, actFilename);
          break;
        }

        case ScriptCommand::script_movetile: {
          int32_t tileCoord1;
          int32_t tileCoord2;
          int32_t tileCoord3;
          int32_t tileCoord4;
          int32_t tileCoord5;
          int32_t tileCoord6;
          int32_t tileCoord7;
          char actFilename[16];

          ReadInterpolatableString(this->ptrScriptTxt, s__s__d__d__d__d__d__d__d, actFilename, &tileCoord1, &tileCoord2, &tileCoord3, &tileCoord4, &tileCoord5, &tileCoord6, &tileCoord7);
          if (this->teamMember != nullptr) {
            ptrAct_size172struct = new SceneClassMoveTile(actFilename, tileCoord1, tileCoord2, tileCoord3, tileCoord4, tileCoord5, tileCoord6, tileCoord7);
            goto label_store_scene_object_noise;
          }
          continue;
          break;
        }

        case ScriptCommand::script_check: {
          int32_t gameFlagIndex;
          int32_t gameFlagValue;

          ReadInterpolatableString(this->ptrScriptTxt, s__d__d, &gameFlagIndex, &gameFlagValue);
          GameFlags[gameFlagIndex] = gameFlagValue;
          continue;
          break;
        }

        case ScriptCommand::script_viewport: {
          int32_t isViewportEnabled;

          ReadInterpolatableString(this->ptrScriptTxt, s__d, &isViewportEnabled);
          if (this->teamMember != nullptr) {
            this->teamMember->mainSceneHandler->isViewportEnabled = isViewportEnabled;
          }
          continue;
          break;
        }

        case ScriptCommand::script_magic: {
          int32_t isMagicEnabled;

          ReadInterpolatableString(this->ptrScriptTxt, s__d, &isMagicEnabled);
          if (this->teamMember != nullptr) {
            this->teamMember->mainSceneHandler->isMagicEnabled = isMagicEnabled;
          }
          continue;
          break;
        }

        case ScriptCommand::script_gate: {
          int32_t gatePos1Lower;
          int32_t gatePos2Lower;
          int32_t gatePos1Upper;
          int32_t gatePos2Upper;
          int32_t newPos1;
          int32_t newPos2;
          char gateSceneName[20];

          ReadInterpolatableString(this->ptrScriptTxt, s__d__d__d__d__s__d__d, &gatePos1Lower, &gatePos2Lower, &gatePos1Upper, &gatePos2Upper, gateSceneName, &newPos1, &newPos2);
          if (this->teamMember != nullptr) {
            ptrAct_size172struct = new SceneClassGate(gatePos1Lower, gatePos2Lower, gatePos1Upper, gatePos2Upper, gateSceneName, newPos1, newPos2);
            goto label_store_scene_object_noise;
          }
          continue;
          break;
        }

        case ScriptCommand::script_anibg: {
          int32_t coord1;
          int32_t coord2;
          int32_t layerOffset;
          char actFilename[16];
          char actionName[16];

          ReadInterpolatableString(this->ptrScriptTxt, s__s__s__d__d__d, actFilename, actionName, &coord1, &coord2, &layerOffset);
          if (this->teamMember == nullptr) {
            continue;
          }
          newSceneObject = new SceneClassAnimatedBackground(actFilename, actionName, coord1, coord2, layerOffset);
          break;
        }

        case ScriptCommand::script_cloud: {
          int32_t cloudParam1;
          int32_t cloudParam2;
          int32_t cloudParam3;
          int32_t cloudParam4;
          int32_t cloudParam5;
          char cloudString1[16];
          char cloudString2[16];

          ReadInterpolatableString(this->ptrScriptTxt, s__s__s__d__d__d__d__d, cloudString1, cloudString2, &cloudParam1, &cloudParam2, &cloudParam3, &cloudParam4, &cloudParam5);
          if (this->teamMember != nullptr) {
            ptrAct_size172struct = new SceneClassCloud(cloudString1, cloudString2, cloudParam1, cloudParam2, cloudParam3, cloudParam4, cloudParam5);
            goto label_store_scene_object_noise;
          }
          continue;
          break;
        }

        case ScriptCommand::script_user: {
          int32_t userParam1;
          int32_t userParam2;
          int32_t userParam3;
          char userString[20];

          ReadInterpolatableString(this->ptrScriptTxt, s__s__d__d__x, userString, &userParam1, &userParam2, &userParam3);
          if (this->teamMember != nullptr) {
            newSceneUser = new SceneClassUser(userParam1, userParam2, userString, userParam3, 0, 0);
            goto label_store_scene_user_user0;
          }
          continue;
          break;
        }

        case ScriptCommand::script_talker: {
          int32_t coord1;
          int32_t coord2;
          int32_t userFlags;
          int32_t scriptIndex;
          char actFilename[20];

          ReadInterpolatableString(this->ptrScriptTxt, s__s__d__d__x__d, actFilename, &coord1, &coord2, &userFlags, &scriptIndex);
          if (this->teamMember != nullptr) {
            newSceneUser = new SceneClassUser(coord1, coord2, actFilename, userFlags, scriptIndex, 0);
            if (newSceneUser != nullptr) {
              this->teamMember->mainSceneHandler->StoreAndInitializeObject(newSceneUser);
            }
            else {
              this->teamMember->mainSceneHandler->StoreAndInitializeObject(nullptr);
            }
          }
          continue;
          break;
        }

        case ScriptCommand::script_box0: {
          int32_t boxParam1;
          int32_t boxParam2;
          int32_t boxParam3;
          int32_t boxParam4;
          char actFilename[16];

          ReadInterpolatableString(this->ptrScriptTxt, s__s__d__d__d__d, actFilename, &boxParam1, &boxParam2, &boxParam3, &boxParam4);
          if (this->teamMember == nullptr) {
            continue;
          }
          newSceneObject = new SceneClassBox(boxParam1, boxParam2, boxParam4, boxParam3, actFilename);
          break;
        }

        case ScriptCommand::script_box: {
          int32_t boxParam1;
          int32_t boxParam2;
          int32_t boxParam3;
          char actFilename[16];

          ReadInterpolatableString(this->ptrScriptTxt, s__s__d__d__d, actFilename, &boxParam1, &boxParam2, &boxParam3);
          if (this->teamMember == nullptr) {
            continue;
          }
          newSceneObject = new SceneClassBox(boxParam1, boxParam2, 0, boxParam3, actFilename);
          break;
        }

        case ScriptCommand::script_noise: {
          int32_t noiseValue;

          ReadInterpolatableString(this->ptrScriptTxt, s__d, &noiseValue);
          if (this->teamMember != nullptr) {
            ptrAct_size172struct = new SceneClassNoise((int16_t)noiseValue);
          label_store_scene_object_noise:
            this->teamMember->mainSceneHandler->StoreAndInitializeObject(ptrAct_size172struct);
          }
          continue;
          break;
        }

        case ScriptCommand::script_item: {
          char itemString1[20];
          char itemUndef1[16];
          int32_t itemParam1;
          int32_t itemParam2;

          ReadInterpolatableString(this->ptrScriptTxt, s__s__s__d__d__d, itemString1, itemUndef1, &itemParam1, &itemParam2, &itemParam2);
          continue;
          break;
        }

        case ScriptCommand::script_switch: {
          int32_t coord1;
          int32_t coord2;
          int32_t directionIndex;
          int32_t gameFlagIndex;
          int32_t isPermanent;
          char actName[16];

          ReadInterpolatableString(this->ptrScriptTxt, s__s__d__d__d__d__d, actName, &coord1, &coord2, &directionIndex, &gameFlagIndex, &isPermanent);
          if (this->teamMember == nullptr) {
            continue;
          }
          newSceneObject = new SceneClassSwitch(coord1, coord2, directionIndex, gameFlagIndex, actName, isPermanent);
          break;
        }
        case ScriptCommand::script_draw:
          ReadInterpolatableString(this->ptrScriptTxt, s__d, &portraitId);
          if (portraitId == 0) {
            for (scriptCmdIndex = 0; TeamCharacterList[scriptCmdIndex] != nullptr; scriptCmdIndex = scriptCmdIndex + 1) {
              if (this->teamMember == TeamCharacterList[scriptCmdIndex]->sceneClassUser) {
                portraitId = TeamCharacterList[scriptCmdIndex]->characterId + 1;
                goto label_validate_portrait_id;
              }
            }
          label_assign_portrait_sprite:
            portraitFrame = this->win4Act->__InlineGetSolidSpriteFrameForAction(this->faceFrame, portraitId - 1);
          }
          else {
          label_validate_portrait_id:
            if (0 <= portraitId) {
              goto label_assign_portrait_sprite;
            }
            portraitFrame = nullptr;
          }
          this->portraitSprite = portraitFrame;
          continue;

        case ScriptCommand::script_give: {
          uint32_t giveAmount;

          ReadInterpolatableString(this->ptrScriptTxt, s__d, &giveAmount);
          previousSceneWindow = this->teamMember;
          if (previousSceneWindow != nullptr) {
            previousSceneWindow->primarySwitchSingleParam_0x7d05(giveAmount, 0x0);
          }
          continue;
          break;
        }

        case ScriptCommand::script_say:
          nextCharByte = this->ptrScriptTxt->readByte();
          while (nextCharByte != '"') {
            nextCharByte = this->ptrScriptTxt->readByte();
          }
          scriptCmdIndex = 0;
          currentCharByte = (byte)this->ptrScriptTxt->readByte();
          output2[0] = currentCharByte;
          while (currentCharByte != '"') {
            scriptCmdIndex = scriptCmdIndex + 1;
            currentCharByte = (byte)this->ptrScriptTxt->readByte();
            output2[scriptCmdIndex] = currentCharByte;
          }
          output2[scriptCmdIndex] = 0;
          this->Talkbox(output2, 0);
          this->init0_5 = 640;
          this->flag_mouseclick = 0;
          return;

        case ScriptCommand::script_mart: {
          int32_t* itemIndexPtr;
          int32_t itemLoopCount;
          GameWindowBase* merchantWindow;

          ReadInterpolatableString(this->ptrScriptTxt, s__d__d__d, &this->storeType, &this->buyFactor, &this->sellFactor);
          itemIndexPtr = this->martItemIndexes;
          for (itemLoopCount = 0; itemLoopCount < 18; itemLoopCount = itemLoopCount + 1) {
            ReadInterpolatableString(this->ptrScriptTxt, s__d, &itemIndexPtr[itemLoopCount]);
          }
          merchantWindow = new GameWindowMerchant(this);
          this->saveGameWindow = merchantWindow;
          return;
          break;
        }

        case ScriptCommand::script_delobj: {
          int32_t delObjCoord1;
          int32_t delObjCoord2;
          int32_t objIndex;
          GameWindowBase* objPtr;

          ReadInterpolatableString(this->ptrScriptTxt, s__d__d, &delObjCoord1, &delObjCoord2);
          objIndex = (int32_t)(this->teamMember->mainSceneHandler->PaddedGridMap_Collision[delObjCoord2][delObjCoord1]);
          if ((0 <= objIndex) && (objPtr = ObjectList[objIndex].sceneClassObjectPointer, objPtr != nullptr)) {
            objPtr->primarySwitchSingleParam_CancelOrCloseWindow_0x7d0c(nullptr, 0);
          }
          continue;
          break;
        }

        case ScriptCommand::script_move: {
          int32_t moveFromX;
          int32_t moveFromY;
          int32_t moveToX;
          int32_t moveToY;
          int32_t objIndex;
          GameWindowBase* objPtr;

          ReadInterpolatableString(this->ptrScriptTxt, s__d__d__d__d, &moveFromX, &moveFromY, &moveToX, &moveToY);
          objIndex = (int32_t)(this->teamMember->mainSceneHandler->PaddedGridMap_Collision[moveFromY][moveFromX]);
          if ((0 <= objIndex) && (objPtr = ObjectList[objIndex].sceneClassObjectPointer, objPtr != nullptr)) {
            objPtr->primarySwitchSingleParam_0x7d00(moveToX, moveToY);
          }
          continue;
          break;
        }

        case ScriptCommand::script_user0: {
          int32_t user0Coord1;
          int32_t user0Coord2;
          int32_t user0Flags;
          int32_t user0ScriptIdx;
          char user0String[20];

          ReadInterpolatableString(this->ptrScriptTxt, s__s__d__d__x__d, user0String, &user0Coord1, &user0Coord2, &user0Flags, &user0ScriptIdx);
          if (this->teamMember != nullptr) {
            newSceneUser = new SceneClassUser(user0Coord1, user0Coord2, user0String, user0Flags, 0, user0ScriptIdx);
          label_store_scene_user_user0:
            if (newSceneUser != nullptr) {
              this->teamMember->mainSceneHandler->StoreAndInitializeObject(newSceneUser);
            }
            else {
              this->teamMember->mainSceneHandler->StoreAndInitializeObject(nullptr);
            }
          }
          continue;
          break;
        }

        case ScriptCommand::script_money: {
          int32_t moneyFlagIndex;
          int32_t moneyOperation;

          ReadInterpolatableString(this->ptrScriptTxt, s__d__d, &moneyFlagIndex, &moneyOperation);
          if (moneyOperation == 1) {
            GoldAmount = GoldAmount + GameFlags[moneyFlagIndex];
          }
          else {
            GameFlags[moneyFlagIndex] = GoldAmount;
            GoldAmount = 0;
          }
          continue;
          break;
        }

        case ScriptCommand::script_receive: {
          int32_t removeItemId;
          int32_t itemIndex;

          ReadInterpolatableString(this->ptrScriptTxt, s__d, &removeItemId);
          for (itemIndex = 0; itemIndex < 32; itemIndex = itemIndex + 1) {
            if ((0 < ItemInventory[itemIndex].quantity) && (ItemInventory[itemIndex].typeId == removeItemId)) {
              ItemInventory[itemIndex].quantity = ItemInventory[itemIndex].quantity + -1;
              break;
            }
          }
          continue;
          break;
        }

        case ScriptCommand::script_save: {
          int32_t saveParam1;
          int32_t saveParam2;
          char saveString1[20];
          char saveString2[22];
          GameWindowBase* saveWindow;

          ReadInterpolatableString(this->ptrScriptTxt, s__s__s__d__d, saveString1, saveString2, &saveParam1, &saveParam2);
          saveWindow = new GameWindowSave(this, saveString1, saveString2, saveParam1, saveParam2);
          this->saveGameWindow = saveWindow;
          return;
          break;
        }

        case ScriptCommand::script_party: {
          int32_t partyParam1;
          int32_t partyParam2;
          GameWindowBase* partyWindow;

          ReadInterpolatableString(this->ptrScriptTxt, s__d__d, &partyParam1, &partyParam2);
          if (this->teamMember == nullptr) {
            return;
          }
          partyWindow = new GameWindowRegroup(this, this->teamMember->mainSceneHandler, partyParam1, partyParam2);
          this->saveGameWindow = partyWindow;
          return;
          break;
        }

        case ScriptCommand::script_group: {
          int32_t coord1;
          int32_t coord2;
          char sceneName[22];
          SceneHandler* nextSceneObjectPtr;
          SceneHandler* currentScenePtr;
          ActiveCharacter** charPtrIter;
          ActiveCharacter** nextCharPtrIter;

          ReadInterpolatableString(this->ptrScriptTxt, s__s__d__d, sceneName, &coord1, &coord2);
          if (this->teamMember != nullptr) {
            this->mainSceneHandler->primarySwitchSingleParam(0x7d08, (intptr_t)sceneName, (intptr_t)&nextSceneObjectPtr);
            currentScenePtr = this->teamMember->mainSceneHandler;
            nextSceneObjectPtr->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((GameWindowBase*)nullptr, 0x0);
            nextSceneObjectPtr->primarySwitchSingleParam(0x7d07, (intptr_t)nullptr, 0x0);
            if (TeamCharacterList[0] != nullptr) {
              charPtrIter = TeamCharacterList;
              do {
                if ((*charPtrIter)->sceneClassUser->mainSceneHandler == currentScenePtr) {
                  (*charPtrIter)->sceneClassUser->primarySwitchSingleParam_PrepareMapForUnit_0x7d12(0x0, 0x0);
                  (*charPtrIter)->sceneClassUser->primarySwitchSingleParam_SetUserLocationOnScene_0x7d13(coord1, coord2);
                  nextSceneObjectPtr->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27((*charPtrIter)->sceneClassUser, 0x0);
                  nextSceneObjectPtr->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((*charPtrIter)->sceneClassUser, 0);
                  nextSceneObjectPtr->primarySwitchSingleParam(0x7d07, (intptr_t)(*charPtrIter)->sceneClassUser, 0x0);
                }
                nextCharPtrIter = charPtrIter + 1;
                charPtrIter = charPtrIter + 1;
              } while (*nextCharPtrIter != nullptr);
            }
          }
          continue;
          break;
        }

        case ScriptCommand::script_heal: {
          ActiveCharacter** healCharPtr;
          ActiveCharacter** nextHealCharPtr;

          if ((this->teamMember != nullptr) && (TeamCharacterList[0] != nullptr)) {
            healCharPtr = TeamCharacterList;
            do {
              if ((*healCharPtr)->sceneClassUser->mainSceneHandler == this->teamMember->mainSceneHandler) {
                (*healCharPtr)->sceneClassUser->primarySwitchSingleParam(0x7d34, 0x0, 0x0);
              }
              nextHealCharPtr = healCharPtr + 1;
              healCharPtr = healCharPtr + 1;
            } while (*nextHealCharPtr != nullptr);
          }
          continue;
          break;
        }

        case ScriptCommand::script_gang: {
          int32_t deductGoldAmount;

          ReadInterpolatableString(this->ptrScriptTxt, s__d, &deductGoldAmount);
          GoldAmount = (((int32_t)(GoldAmount - deductGoldAmount) < 0) - 1) & (GoldAmount - deductGoldAmount);
          continue;
          break;
        }

        case ScriptCommand::script_deluser: {
          int32_t characterId;
          ActiveCharacter** delUserCharPtr;
          int32_t slotIndex;
          GameWindowBase* userToDelete;

          ReadInterpolatableString(this->ptrScriptTxt, s__d, &characterId);
          if (TeamCharacterList[0] != nullptr) {
            delUserCharPtr = TeamCharacterList;
            do {
              if ((*delUserCharPtr)->characterId == characterId + -1) {
                userToDelete = (*delUserCharPtr)->sceneClassUser;
                if (userToDelete != nullptr) {
                  delete userToDelete;
                }
                for (slotIndex = 0; slotIndex < 5; slotIndex = slotIndex + 1) {
                  if (ActiveTeamCharacterSlots[slotIndex] == *delUserCharPtr) {
                    ActiveTeamCharacterSlots[slotIndex] = nullptr;
                  }
                }
                delUserCharPtr = delUserCharPtr + -1;
              }
              delUserCharPtr = delUserCharPtr + 1;
            } while (*delUserCharPtr != nullptr);
          }
          if (BenchedCharacterList[0] != nullptr) {
            delUserCharPtr = BenchedCharacterList;
            do {
              if ((*delUserCharPtr)->characterId == characterId + -1) {
                userToDelete = (*delUserCharPtr)->sceneClassUser;
                if (userToDelete != nullptr) {
                  delete userToDelete;
                }
                delUserCharPtr = delUserCharPtr + -1;
              }
              delUserCharPtr = delUserCharPtr + 1;
            } while (*delUserCharPtr != nullptr);
          }
          continue;
          break;
        }

        case ScriptCommand::script_visual: {
          int32_t movieId;

          ReadInterpolatableString(this->ptrScriptTxt, s__d, &movieId);
          this->mainSceneHandler->primarySwitchSingleParam(0x7d1d, movieId, 0x0);
          continue;
        }

        case ScriptCommand::script_action: {
          int32_t actionCoord1;
          int32_t actionCoord2;
          char actionUndef[16];
          int32_t actionObjIndex;
          GameWindowBase* actionObj;

          ReadInterpolatableString(this->ptrScriptTxt, s__d__d__s, &actionCoord1, &actionCoord2, actionUndef);
          actionObjIndex = (int32_t)(this->teamMember->mainSceneHandler->PaddedGridMap_Collision[actionCoord2][actionCoord1]);
          if ((0 <= actionObjIndex) && (actionObj = ObjectList[actionObjIndex].sceneClassObjectPointer, actionObj != nullptr)) {
            actionObj->primarySwitchSingleParam_0x7d3a(actionUndef, 0);
          }
          continue;
        }

        case ScriptCommand::script_effect: {
          int32_t coord1;
          int32_t coord2;
          char actFilename[16];
          AnimationSpell* spellEffect;

          ReadInterpolatableString(this->ptrScriptTxt, s__s__d__d, actFilename, &coord1, &coord2);
          if (this->teamMember != nullptr) {
            spellEffect = new AnimationSpell(actFilename, coord1, coord2);
            this->teamMember->mainSceneHandler->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27(spellEffect, 0x0);
          }
          continue;
        }

        case ScriptCommand::script_scroll: {
          int32_t scrollX;
          int32_t scrollY;
          SceneClassCameraBase* sceneCamera;

          ReadInterpolatableString(this->ptrScriptTxt, s__d__d, &scrollX, &scrollY);
          sceneCamera = this->teamMember->mainSceneHandler->sceneCamera;
          sceneCamera->primarySwitchSingleParam(0x7d21, scrollX, scrollY);
          continue;
        }

        case ScriptCommand::script_boss: {
          int32_t bossParam1;
          int32_t bossParam2;
          int32_t bossParam3;
          int32_t bossParam4;
          char bossString[16];

          ReadInterpolatableString(this->ptrScriptTxt, s__s__d__d__d__d, bossString, &bossParam1, &bossParam2, &bossParam3, &bossParam4);
          newSceneObject = new SceneClassBoss(bossString, bossParam1, bossParam2, bossParam3, bossParam4);
          break;
        }

        case ScriptCommand::script_sfx: {
          int32_t sfxId;

          ReadInterpolatableString(this->ptrScriptTxt, s__d, &sfxId);
          this->mainSceneHandler->primarySwitchSingleParam_PlaySoundEffect_0x7d0a(sfxId, nullptr);
          continue;
        }
        }
        this->teamMember->mainSceneHandler->StoreAndInitializeObject(newSceneObject);
      }
    }
  }
}
