#ifndef HAZARD_GLOBALS_H
#define HAZARD_GLOBALS_H

#include <windows.h>
#include <dsound.h>
#include "HazardClasses/MusicObject.hpp"
#include "HazardClasses/RunTickClass.hpp"
#include "HazardClasses/SfxObject.hpp"
#include "HazardStructs/ActiveCharacter.hpp"
#include "HazardStructs/ErrorEntry.hpp"
#include "HazardStructs/FileHandleComponent.hpp"
#include "HazardStructs/GameState.hpp"
#include "HazardStructs/IntegerVirtualKeyPair.hpp"
#include "HazardStructs/ItemReferenceCollection.hpp"
#include "HazardStructs/ObjectWrapper.hpp"
#include "HazardStructs/PathfindingDirection.hpp"
#include "HazardStructs/PathfindingNodesBlock.hpp"
#include "HazardStructs/UnpackedFilePakStruct.hpp"

extern int32_t ReadFileFlag;

extern float ExpIncreasePerLevel;

extern float ExpRequirementLevel4;

extern float Fixed1000;

extern float Fixed500;

extern double GlobalThreshold;

extern const char* PTR_s_frame[9];

extern char s_str6[];

extern char s_str5[];

extern char s_str4[];

extern char s_str3[];

extern char s_str2[];

extern char s_str1[];

extern char s_str0[];

extern char s_button[];

extern char s_select[];

extern char s_face[];

extern char s_frame[];

extern char s_strg[];

extern char s_strf[];

extern char s_stre[];

extern char s_strd[];

extern char s_strc[];

extern char s_strb[];

extern char s_stra[];

extern char s__s_d[];

extern char s_string[];

extern char s__d_act[];

extern char s_magic[];

extern char s_endif[];

extern char s_elseif[];

extern char s_if[];

extern char s__d__d__d[];

extern char s__s__d__d__d__d__d[];

extern char s__s__d__d__d[];

extern char s__s__d__d__x__d[];

extern char s__s__d__d__x[];

extern char s__s__s__d__d__d__d__d[];

extern char s__s__s__d__d__d[];

extern char s__d__d__d__d__s__d__d[];

extern char s__d[];

extern char s__d__d[];

extern char s__s__d__d__d__d__d__d__d[];

extern char s__s__d__d__d__d[];

extern char InterpolatableString[];

extern char s_title[];

extern char s__d_GOLD[];

extern char s_wb[];

extern const char s_EMPTY[];

extern char s_hazard_sav[];

extern char s_rb[];

extern char s_debug[];

extern int32_t RedOffset1;

extern int32_t RedOffset2;

extern int32_t InvRedOffset;

extern int32_t GreenOffset1;

extern int32_t GreenOffset2;

extern int32_t InvGreenOffset;

extern int32_t BlueOffset1;

extern int32_t BlueOffset2;

extern int32_t InvBlueOffset;

extern uint16_t RgbMask;

extern char s_Fail_to_get_pixel_format[];

extern char s_Your_DirectDraw_Device_doesn_t_c[];

extern char s_Time_to_error[];

extern char s_Your_direct_draw_device_doesn_t_i[];

extern char s_Direct_X_isn_t_installed[];

extern char s_Time_to_Stop[];

extern char s_Error[];

extern char Flag_ParseBmp_14[];

extern char s_normal[];

extern char s_cursor_act[];

extern char s_scene_txt[];

extern int32_t FlagGameIsRunning;

extern int32_t TimeResolution_45or15;

extern IntegerVirtualKeyPair InputCodes[22];

extern char s__d__s__d[];

extern char s_sfx_txt[];

extern char s__HAZARD__Pumpkin_Soft[];

extern char s_hpatch_002[];

extern char s_hpatch_001[];

extern char s_music_pak[];

extern char s_hazard_pak[];

extern char s_visual_pak[];

extern char s__visual_pa_[];

extern char s__Please_Insert_a_Hazard_CD_Disk[];

extern char s_c___hazard_pa_[];

extern char s_PumpkinSoft[];

extern char s_c__[];

extern uint32_t GoldAmount;

extern InventoryItemStruct ItemInventory[32];

extern char s_stand[];

extern char s__sfx[];

extern char s__item[];

extern char s_mainmenu_act[];

extern int32_t RngSeed;

extern int32_t WriteErrorLogConfig;

extern ErrorEntry LowerUpperErrorDictionary[45];

extern int32_t* FontPixelMap;

extern IDirectDrawSurface* DirectDrawSurface;

extern int32_t PauseState;

extern IDirectDraw* DirectDrawObject;

extern MusicObject* PtrMusicObject;

extern SfxObject* PtrSfxObject;

extern LPDIRECTSOUND DirectSoundObject;

extern PathfindingDirection* PathfindingLatestDirection;

extern PathfindingNodesBlock* WrapperRelated;

extern GameState GlobalHazGameState;

extern HWND GameFullscreenWindow;

extern uint32_t FlagRelatedToLoadingSfx;

extern char InputStates128[128];

extern int32_t GameStateFlag;

extern RunTickClass* CurrentRunTickClass;

extern uint32_t MouseInput;

extern float GatedTick;

extern LPCSTR lpCaption;

extern int32_t MouseButtonClick;

extern int32_t CursorXCoord;

extern int32_t CursorYCoord;

extern ActiveCharacter* TeamCharacterList[12];

extern ActiveCharacter* BenchedCharacterList[12];

extern ActiveCharacter* ActiveTeamCharacterSlots[5];

extern LPDIRECTSOUNDBUFFER ListOfSfxBuffers[100];

extern int32_t* GameFlags;

extern CoreActClass* Item00Act;

extern ItemReferenceCollection* ItemStruct12k;

extern GameWindow* GameWindowRightSide;

extern GameWindow* GameWindowLeftSidebar;

extern int32_t IncrementGradually;

extern UnpackedFilePakStruct* GlobalUnpackedFilePakStruct;

extern int32_t HandlesUpperValue;

extern int32_t HandlesLowerValue;

extern uint32_t ReadFileRelated;

extern char* s_[4];

extern FileHandleComponent* FileHandleComponentAddresses[64];

extern UINT uNumber;

extern ObjectWrapper* ObjectList;

extern PathfindingDirection PathfindingDirectionLookup[8];

extern char s_exp[4];

extern char s_body[8];

extern char s_time[8];

extern char s_mp[4];

extern char s_hp[4];

extern char s_lvnum[8];

extern char s_main[8];

extern char s_say2[8];

extern char s_sfx[4];

extern char s_boss[8];

extern char s_scroll[8];

extern char s_effect[8];

extern char s_action[8];

extern char s_visual[8];

extern char s_deluser[8];

extern char s_gang[8];

extern char s_heal[8];

extern char s_group[8];

extern char s_party[8];

extern char s_save[8];

extern char s_receive[8];

extern char s_money[8];

extern char s_user0[8];

extern char s_move[8];

extern char s_delobj[8];

extern char s_mart[8];

extern char s_say[4];

extern char s_give[8];

extern char s_draw[8];

extern char s_switch[8];

extern char s_item[8];

extern char s_noise[8];

extern char s_box[4];

extern char s_box0[8];

extern char s_talker[8];

extern char s_user[8];

extern char s_map[4];

extern char s_cloud[8];

extern char s_anibg[8];

extern char s_gate[8];

extern char s_viewport[12];

extern char s_type[8];

extern char s_music[8];

extern char s_check[8];

extern char s_movetile[12];

extern char s_door[8];

extern char s_talkbox[8];

extern char s_camera[8];

extern char s_command[8];

extern char s_snaik[8];

extern char s_varcu[8];

extern char s_dov[4];

extern char s_sha[4];

extern char s_aris[8];

extern char s_enlike[8];

extern char s_meil[8];

extern char s_bar[4];

extern char s_armi[8];

extern char s_rick[8];

extern char s_ropen[8];

extern char s_lopen[8];

extern char s_bopen[8];

extern char s_ropened[8];

extern char s_lopened[8];

extern char s_bopened[8];

extern char s_rstand[8];

extern char s_lstand[8];

extern char s_bstand[8];

extern char s_m_shasha_act[16];

extern char s_m_aris_act[12];

extern char s_m_armi_act[12];

extern char s_catt5_2[8];

extern char s_catt5_1[8];

extern char s_catt4_2[8];

extern char s_catt4_1[8];

extern char s_catt3_2[8];

extern char s_catt3_1[8];

extern char s_catt2_2[8];

extern char s_catt2_1[8];

extern char s_catt1_2[8];

extern char s_catt1_1[8];

extern char s_snaik4t_act[12];

extern char s_snaik4b_act[12];

extern char s_snaik3t_act[12];

extern char s_snaik3b_act[12];

extern char s_snaik2t_act[12];

extern char s_snaik2b_act[12];

extern char s_snaik1t_act[12];

extern char s_snaik1b_act[12];

extern char s_varcu3t_act[12];

extern char s_varcu3b_act[12];

extern char s_varcu2t_act[12];

extern char s_varcu2b_act[12];

extern char s_varcu1t_act[12];

extern char s_varcu1b_act[12];

extern char s_dov3t_act[12];

extern char s_dov3b_act[12];

extern char s_dov2t_act[12];

extern char s_dov2b_act[12];

extern char s_dov1t_act[12];

extern char s_dov1b_act[12];

extern char s_sha3t_act[12];

extern char s_sha3b_act[12];

extern char s_sha2t_act[12];

extern char s_sha2b_act[12];

extern char s_sha1t_act[12];

extern char s_sha1b_act[12];

extern char s_aris3t_act[12];

extern char s_aris3b_act[12];

extern char s_aris2t_act[12];

extern char s_aris2b_act[12];

extern char s_aris1t_act[12];

extern char s_aris1b_act[12];

extern char s_enli3t_act[12];

extern char s_enli3b_act[12];

extern char s_enli2t_act[12];

extern char s_enli2b_act[12];

extern char s_enli1t_act[12];

extern char s_enli1b_act[12];

extern char s_meil3t_act[12];

extern char s_meil3b_act[12];

extern char s_meil2t_act[12];

extern char s_meil2b_act[12];

extern char s_meil1t_act[12];

extern char s_meil1b_act[12];

extern char s_bar3t_act[12];

extern char s_bar3b_act[12];

extern char s_bar2t_act[12];

extern char s_bar2b_act[12];

extern char s_bar1t_act[12];

extern char s_bar1b_act[12];

extern char s_armi3t_act[12];

extern char s_armi3b_act[12];

extern char s_armi2t_act[12];

extern char s_armi2b_act[12];

extern char s_armi1t_act[12];

extern char s_armi1b_act[12];

extern char s_rickbt_act[12];

extern char s_rick4b_act[12];

extern char s_rick3t_act[12];

extern char s_rick3b_act[12];

extern char s_rick2t_act[12];

extern char s_rick2b_act[12];

extern char s_rick1t_act[12];

extern char s_rick1b_act[12];

extern char s_rect[8];

extern char s_gate0[8];

#endif
