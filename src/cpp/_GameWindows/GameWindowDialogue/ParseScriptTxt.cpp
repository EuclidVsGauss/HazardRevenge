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
  byte* scriptCmdKeyBytes;
  int32_t scriptCmdIndex;
  WORD* flagWordPtr;
  ActiveCharacter* currentCharacter;
  GameWindowBase* ptrAct_size172struct;
  GameWindowBase* newSceneUser;
  InventoryItemStruct* currentItem;
  ActiveCharacter** nextCharPtr;
  GameWindowBase* newSceneObject;
  int32_t itemTypeId;
  int32_t countdownTimer;
  int32_t scriptVarValue;
  char* scriptVarStrPtr;
  byte* strCmpBytePtr;
  ActiveCharacter** nextTempPtr;
  StringIntegerMap* scriptCommand;
  char flagColorScale;
  bool startsWithExclamationMark;
  int32_t portraitId;
  char output1[16];
  byte string[80];
  char output2[256] = {0};

  if (this->saveGameWindow == nullptr) {
    thisgwb = this->saveGameWindowCopy;
    if (thisgwb != nullptr) {
      delete thisgwb;
      this->saveGameWindowCopy = nullptr;
    }
    if (((this->flag_mouseclick != 1) && (countdownTimer = this->init0_5, this->init0_5 = countdownTimer + -1, countdownTimer < 1)) || (this->saveGameWindow != nullptr)) {
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
        scriptCmdIndex = 0;
        if (ScriptCommand_ARRAY[0].Key != nullptr) {
          scriptCommand = ScriptCommand_ARRAY;
          scriptCmdKeyBytes = (byte*)ScriptCommand_ARRAY[0].Key;
          do {
            strCmpBytePtr = (byte*)output2;
            scriptVarValue = strcmp((char*)scriptCmdKeyBytes, (char*)strCmpBytePtr);

            if (scriptVarValue == 0) {
              break;
            }
            scriptCmdKeyBytes = (byte*)scriptCommand[1].Key;
            scriptCommand = scriptCommand + 1;
            scriptCmdIndex = scriptCmdIndex + 1;
          } while (scriptCmdKeyBytes != nullptr);
        }

        switch (ScriptCommand_ARRAY[scriptCmdIndex].Value) {
        case ScriptCommand::script_if:
          ReadInterpolatableString(this->ptrScriptTxt, InterpolatableString, output1);
          startsWithExclamationMark = output1[0] == '!';
          scriptVarStrPtr = output1 + (int32_t)startsWithExclamationMark;
          scriptCmdIndex = atoi(scriptVarStrPtr);

          if ((scriptCmdIndex < 1) || 10 < scriptCmdIndex) {
            if (scriptCmdIndex == 0) {
              ReadInterpolatableString(this->ptrScriptTxt, InterpolatableString, output1);
              startsWithExclamationMark = output1[0] == '!';
              scriptVarStrPtr = output1 + (int32_t)startsWithExclamationMark;
              scriptVarValue = atoi(scriptVarStrPtr);

              flagWordPtr = (WORD*)Scrip_1_0;
              if (scriptVarValue <= (int32_t)GoldAmount) {
                flagWordPtr = (WORD*)Script_0_0;
              }
              *(int16_t*)scriptVarStrPtr = *flagWordPtr;
              GameFlags[1] = 0;
              GameFlags[0] = 1;
            }
          }
          else {
            scriptCmdIndex = 0;
            if (TeamCharacterList[0] != nullptr) {
              nextTempPtr = TeamCharacterList;
              currentCharacter = TeamCharacterList[0];
              do {
                if (this->teamMember == currentCharacter->shiftedSceneClassUser0x48) {
                  break;
                }
                currentCharacter = nextTempPtr[1];
                nextTempPtr = nextTempPtr + 1;
                scriptCmdIndex = scriptCmdIndex + 1;
              } while (currentCharacter != nullptr);
            }
            if (TeamCharacterList[scriptCmdIndex] == nullptr) {
            label_set_script_flag_default:
              flagWordPtr = (WORD*)Scrip_1_0;
            }
            else {
              scriptVarValue = atoi(scriptVarStrPtr);
              flagWordPtr = (WORD*)Script_0_0;
              if (TeamCharacterList[scriptCmdIndex]->characterId + 1 != scriptVarValue) {
                goto label_set_script_flag_default;
              }
            }
            *(int16_t*)scriptVarStrPtr = *flagWordPtr;
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          scriptCmdIndex = atoi(scriptVarStrPtr);
          if (scriptCmdIndex == 0xb) {
            flagWordPtr = (WORD*)Scrip_1_0;
            if (GoldAmount != 0) {
              flagWordPtr = (WORD*)Script_0_0;
            }
            *(int16_t*)scriptVarStrPtr = *flagWordPtr;
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          scriptCmdIndex = atoi(scriptVarStrPtr);
          if (scriptCmdIndex == 0xc) {
            this->flag_mouseclick = 1;
            return;
          }

          scriptCmdIndex = atoi(scriptVarStrPtr);
          if (scriptCmdIndex == 0xd) {
            scriptCmdIndex = 0;
            if (TeamCharacterList[0] != nullptr) {
              nextTempPtr = TeamCharacterList;
              do {
                nextCharPtr = nextTempPtr + 1;
                nextTempPtr = nextTempPtr + 1;
                scriptCmdIndex = scriptCmdIndex + 1;
              } while (*nextCharPtr != nullptr);
            }
            nextTempPtr = ActiveTeamCharacterSlots;
            do {
              if (*nextTempPtr != nullptr) {
                scriptCmdIndex = scriptCmdIndex + 1;
              }
              nextTempPtr = nextTempPtr + 1;
            } while (nextTempPtr < ActiveTeamCharacterSlots + 5);
            flagWordPtr = (WORD*)Script_0_0;
            if (scriptCmdIndex != 5) {
              flagWordPtr = (WORD*)Scrip_1_0;
            }
            *(int16_t*)scriptVarStrPtr = *flagWordPtr;
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          scriptCmdIndex = atoi(scriptVarStrPtr);
          if (scriptCmdIndex == 0xe) {
            scriptCmdIndex = 0;
            if (TeamCharacterList[0] != nullptr) {
              nextTempPtr = TeamCharacterList;
              currentCharacter = TeamCharacterList[0];
              do {
                if (currentCharacter->shiftedSceneClassUser0x48->mainSceneHandler->mapType == MapType::Field) {
                  break;
                }
                currentCharacter = nextTempPtr[1];
                nextTempPtr = nextTempPtr + 1;
                scriptCmdIndex = scriptCmdIndex + 1;
              } while (currentCharacter != nullptr);
            }
            flagWordPtr = (WORD*)Script_0_0;
            if (TeamCharacterList[scriptCmdIndex] != nullptr) {
              flagWordPtr = (WORD*)Scrip_1_0;
            }
            *(int16_t*)scriptVarStrPtr = *flagWordPtr;
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          scriptCmdIndex = atoi(scriptVarStrPtr);
          if (scriptCmdIndex == 0xf) {
            scriptVarValue = 0;
            while (TeamCharacterList[scriptVarValue] != nullptr) {
              if (TeamCharacterList[scriptVarValue]->characterId != 0) {
                break;
              }
              scriptVarValue++;
            }
            if (TeamCharacterList[scriptVarValue] == nullptr) {
              scriptVarValue = 0;
              while (BenchedCharacterList[scriptVarValue] != nullptr) {
                if (BenchedCharacterList[scriptVarValue]->characterId != 0) {
                  break;
                }
                scriptVarValue++;
              }
              flagWordPtr = (WORD*)Scrip_1_0;
              if (BenchedCharacterList[scriptVarValue] != nullptr) {
                flagWordPtr = (WORD*)Script_0_0;
              }
              *(int16_t*)scriptVarStrPtr = *flagWordPtr;
            }
            else {
              *(int16_t*)scriptVarStrPtr = *(WORD*)Script_0_0;
            }
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          scriptCmdIndex = atoi(scriptVarStrPtr);
          if (scriptCmdIndex == 0x10) {
            scriptVarValue = 0;
            while (TeamCharacterList[scriptVarValue] != nullptr) {
              if (TeamCharacterList[scriptVarValue]->characterId != 0) {
                break;
              }
              scriptVarValue++;
            }
            if (TeamCharacterList[scriptVarValue] == nullptr) {
              scriptVarValue = 0;
              while (BenchedCharacterList[scriptVarValue] != nullptr) {
                if (BenchedCharacterList[scriptVarValue]->characterId != 0) {
                  break;
                }
                scriptVarValue++;
              }
              flagWordPtr = (WORD*)Scrip_1_0;
              if (BenchedCharacterList[scriptVarValue] != nullptr) {
                flagWordPtr = (WORD*)Script_0_0;
              }
              *(int16_t*)scriptVarStrPtr = *flagWordPtr;
            }
            else {
              *scriptVarStrPtr = *(WORD*)Script_0_0;
            }
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          scriptCmdIndex = atoi(scriptVarStrPtr);
          if (scriptCmdIndex < 0) {
            scriptCmdIndex = 0;
            currentItem = ItemInventory;
            do {
              if (0 < currentItem->quantity) {
                scriptVarValue = atoi(scriptVarStrPtr);
                itemTypeId = currentItem->typeId;

                if (itemTypeId == -scriptVarValue) {
                  break;
                }
              }
              currentItem = currentItem + 1;
              scriptCmdIndex = scriptCmdIndex + 1;
            } while (currentItem < ItemInventory + 32);
            flagWordPtr = (WORD*)Scrip_1_0;
            if (scriptCmdIndex != 0x20) {
              flagWordPtr = (WORD*)Script_0_0;
            }
            *(WORD*)scriptVarStrPtr = *flagWordPtr;
            GameFlags[1] = 0;
            GameFlags[0] = 1;
          }

          scriptCmdIndex = atoi(scriptVarStrPtr);
          if (GameFlags[scriptCmdIndex] == (int32_t)startsWithExclamationMark) {
            scriptCmdIndex = 0;
            do {
              ReadInterpolatableString(this->ptrScriptTxt, InterpolatableString, output2);
              if (output2[0] == ';') {
                nextCharByte = this->ptrScriptTxt->readByte();
                while (nextCharByte != '\n') {
                  nextCharByte = this->ptrScriptTxt->readByte();
                }
              }
              if (output2[0] == '\"') {
                nextCharByte = 0xffffffff;
                scriptCmdKeyBytes = string + 2;
                do {
                  if (nextCharByte == 0) {
                    break;
                  }
                  nextCharByte = nextCharByte - 1;
                  currentCharByte = *scriptCmdKeyBytes;
                  scriptCmdKeyBytes = scriptCmdKeyBytes + 1;
                } while (currentCharByte != 0);
                if (string[~nextCharByte] != '\"') {
                  nextCharByte = this->ptrScriptTxt->readByte();
                  while (nextCharByte != '\"') {
                    nextCharByte = this->ptrScriptTxt->readByte();
                  }
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
            } while (((scriptVarValue != 0) || (scriptCmdIndex != 0)) && (-1 < scriptCmdIndex));
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
          } while (-1 < scriptCmdIndex);

        case ScriptCommand::script_endif:
          continue;

        default:
          WrapperMessageBoxA((LPCSTR)output2, s_talkbox__wrong_message);
          continue;

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
            this->teamMember->mainSceneHandler->StoreAndInitializeObject(ptrAct_size172struct);
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
            this->teamMember->mainSceneHandler->StoreAndInitializeObject(ptrAct_size172struct);
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
            this->teamMember->mainSceneHandler->StoreAndInitializeObject(ptrAct_size172struct);
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
            if (newSceneUser == nullptr) {
              this->teamMember->mainSceneHandler->StoreAndInitializeObject(nullptr);
            }
            else {
              this->teamMember->mainSceneHandler->StoreAndInitializeObject(newSceneUser);
            }
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
            if (newSceneUser == nullptr) {
              this->teamMember->mainSceneHandler->StoreAndInitializeObject(nullptr);
            }
            else {
              this->teamMember->mainSceneHandler->StoreAndInitializeObject(newSceneUser);
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
            this->teamMember->mainSceneHandler->StoreAndInitializeObject(ptrAct_size172struct);
          }
          continue;
          break;
        }

        case ScriptCommand::script_item: {
          char itemString1[20];
          char itemUndef1[16];
          void* itemPtr;
          byte itemUndef2[4];
          byte itemUndef3[4];

          ReadInterpolatableString(this->ptrScriptTxt, s__s__s__d__d__d, itemString1, itemUndef1, &itemPtr, itemUndef2, itemUndef3);
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
            scriptCmdIndex = 0;
            if (TeamCharacterList[0] != nullptr) {
              nextTempPtr = TeamCharacterList;
              currentCharacter = TeamCharacterList[0];
              do {
                if (this->teamMember == currentCharacter->shiftedSceneClassUser0x48) {
                  portraitId = TeamCharacterList[scriptCmdIndex]->characterId + 1;
                  goto label_validate_portrait_id;
                }
                currentCharacter = nextTempPtr[1];
                nextTempPtr = nextTempPtr + 1;
                scriptCmdIndex = scriptCmdIndex + 1;
              } while (currentCharacter != nullptr);
            }
          label_assign_portrait_sprite:
            this->portraitSprite = __InlineGetSolidSpriteFrameForAction(this->faceFrame, this->win4Act, portraitId - 1);

            continue;
          }
          else {
          label_validate_portrait_id:
            if (-1 < portraitId) {
              goto label_assign_portrait_sprite;
            }
          }
          this->portraitSprite = nullptr;
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
          nextCharByte = this->ptrScriptTxt->readByte();
          output2[0] = (byte)nextCharByte;
          scriptCmdIndex = 0;
          currentCharByte = (byte)output2[0];
          while (currentCharByte != '"') {
            nextCharByte = this->ptrScriptTxt->readByte();
            currentCharByte = (byte)nextCharByte;
            output2[scriptCmdIndex + 1] = currentCharByte;
            scriptCmdIndex = scriptCmdIndex + 1;
          }
          output2[scriptCmdIndex] = 0;
          flagColorScale = '\0';
          this->Talkbox(output2, flagColorScale);
          this->init0_5 = 640;
          this->flag_mouseclick = 0;
          return;

        case ScriptCommand::script_mart: {
          int32_t* itemIndexPtr;
          int32_t itemLoopCount;
          GameWindowBase* merchantWindow;

          ReadInterpolatableString(this->ptrScriptTxt, s__d__d__d, &this->storeType, &this->buyFactor, &this->sellFactor);
          itemIndexPtr = this->martItemIndexes;
          itemLoopCount = 18;
          do {
            ReadInterpolatableString(this->ptrScriptTxt, s__d, itemIndexPtr);
            itemIndexPtr = itemIndexPtr + 1;
            itemLoopCount = itemLoopCount + -1;
          } while (itemLoopCount != 0);
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
          if ((-1 < objIndex) && (objPtr = ObjectList[objIndex].sceneClassObjectPointer, objPtr != nullptr)) {
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
          if ((-1 < objIndex) && (objPtr = ObjectList[objIndex].sceneClassObjectPointer, objPtr != nullptr)) {
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
          GameWindowBase* userObj;

          ReadInterpolatableString(this->ptrScriptTxt, s__s__d__d__x__d, user0String, &user0Coord1, &user0Coord2, &user0Flags, &user0ScriptIdx);
          if (this->teamMember != nullptr) {
            userObj = new SceneClassUser(user0Coord1, user0Coord2, user0String, user0Flags, 0, user0ScriptIdx);
            if (userObj == nullptr) {
              this->teamMember->mainSceneHandler->StoreAndInitializeObject(nullptr);
            }
            else {
              this->teamMember->mainSceneHandler->StoreAndInitializeObject(userObj);
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
          InventoryItemStruct* itemPtr;

          ReadInterpolatableString(this->ptrScriptTxt, s__d, &removeItemId);
          itemIndex = 0;
          itemPtr = ItemInventory;
          do {
            if ((0 < itemPtr->quantity) && (itemPtr->typeId == removeItemId)) {
              ItemInventory[itemIndex].quantity = ItemInventory[itemIndex].quantity + -1;
              break;
            }
            itemPtr = itemPtr + 1;
            itemIndex = itemIndex + 1;
          } while (itemPtr < ItemInventory + 32);
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
                if ((*charPtrIter)->shiftedSceneClassUser0x48->mainSceneHandler == currentScenePtr) {
                  (*charPtrIter)->shiftedSceneClassUser0x48->primarySwitchSingleParam_PrepareMapForUnit_0x7d12(0x0, 0x0);
                  (*charPtrIter)->shiftedSceneClassUser0x48->primarySwitchSingleParam_SetUserLocationOnScene_0x7d13(coord1, coord2);
                  nextSceneObjectPtr->primarySwitchSingleParam_TriggerObjectInitialization_0x7d27((*charPtrIter)->shiftedSceneClassUser0x48, 0x0);
                  nextSceneObjectPtr->primarySwitchSingleParam_UpdateSelectedUnits_0x7d1a((*charPtrIter)->shiftedSceneClassUser0x48, 0);
                  nextSceneObjectPtr->primarySwitchSingleParam(0x7d07, (intptr_t)(*charPtrIter)->shiftedSceneClassUser0x48, 0x0);
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
              if ((*healCharPtr)->shiftedSceneClassUser0x48->mainSceneHandler == this->teamMember->mainSceneHandler) {
                (*healCharPtr)->shiftedSceneClassUser0x48->primarySwitchSingleParam(0x7d34, 0x0, 0x0);
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
          ActiveCharacter** nextDelUserCharPtr;
          GameWindowBase* userToDelete;

          ReadInterpolatableString(this->ptrScriptTxt, s__d, &characterId);
          if (TeamCharacterList[0] != nullptr) {
            delUserCharPtr = TeamCharacterList;
            do {
              if ((*delUserCharPtr)->characterId == characterId + -1) {
                userToDelete = (*delUserCharPtr)->shiftedSceneClassUser0x48;
                if (userToDelete != nullptr) {
                  delete userToDelete;
                }

                nextDelUserCharPtr = ActiveTeamCharacterSlots;
                do {

                  if (*nextDelUserCharPtr == *delUserCharPtr) {
                    *nextDelUserCharPtr = nullptr;
                  }
                  nextDelUserCharPtr = nextDelUserCharPtr + 1;
                } while (nextDelUserCharPtr < ActiveTeamCharacterSlots + 5);

                break;
              }

              delUserCharPtr = delUserCharPtr + 1;

            } while (*delUserCharPtr != nullptr);
          }
          if (BenchedCharacterList[0] != nullptr) {
            delUserCharPtr = BenchedCharacterList;
            do {
              if ((*delUserCharPtr)->characterId == characterId + -1) {
                userToDelete = (*delUserCharPtr)->shiftedSceneClassUser0x48;
                if (userToDelete != nullptr) {
                  delete userToDelete;
                }
                delUserCharPtr = delUserCharPtr + -1;
              }
              nextDelUserCharPtr = delUserCharPtr + 1;
              delUserCharPtr = delUserCharPtr + 1;
            } while (*nextDelUserCharPtr != nullptr);
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
          if ((-1 < actionObjIndex) && (actionObj = ObjectList[actionObjIndex].sceneClassObjectPointer, actionObj != nullptr)) {
            actionObj->primarySwitchSingleParam(0x7d3a, (intptr_t)actionUndef, 0);
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
        case ScriptCommand::script_say2:
          nextCharByte = this->ptrScriptTxt->readByte();
          while (nextCharByte != 0x22) {
            nextCharByte = this->ptrScriptTxt->readByte();
          }
          nextCharByte = this->ptrScriptTxt->readByte();
          output2[0] = (byte)nextCharByte;
          scriptCmdIndex = 0;
          currentCharByte = (byte)output2[0];
          while (currentCharByte != 0x22) {
            nextCharByte = this->ptrScriptTxt->readByte();
            currentCharByte = (byte)nextCharByte;
            output2[scriptCmdIndex + 1] = currentCharByte;
            scriptCmdIndex = scriptCmdIndex + 1;
          }
          output2[scriptCmdIndex] = 0;
          flagColorScale = '\x01';
          this->Talkbox(output2, flagColorScale);
          this->init0_5 = 640;
          this->flag_mouseclick = 0;
          return;
        }
        this->teamMember->mainSceneHandler->StoreAndInitializeObject(newSceneObject);
      }
    }
  }
  else {
    this->initZero_posPtr = nullptr;
  }
}
