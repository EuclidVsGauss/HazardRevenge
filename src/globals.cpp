#include "hpp/HazardEnums/InternalKey.hpp"
#include "hpp/HazardGlobals.hpp"
#include "hpp/HazardStructs/ClickableRectangle1.hpp"
#include "hpp/HazardStructs/ClickableRectangle2.hpp"
#include "hpp/HazardStructs/ClickableRectangle3.hpp"
#include "hpp/HazardStructs/DefaultCharacterStats.hpp"
#include "hpp/HazardStructs/DirectionOffsets.hpp"
#include "hpp/HazardStructs/DirectionalTuple.hpp"
#include "hpp/HazardStructs/GlobalStruct2048.hpp"
#include "hpp/HazardStructs/ItemRawCollection.hpp"
#include "hpp/HazardStructs/LargeTmpObject.hpp"
#include "hpp/HazardStructs/StringIntegerMap.hpp"
#include "hpp/HazardStructs/UnlockDoorTuple.hpp"
#include "hpp/HazardStructs/VisualTxtItem.hpp"
#include "hpp/HazardStructs/WeaponSlotFrame.hpp"

float ExpIncreasePerLevel = 1.200000;

float ExpRequirementLevel4 = 4000;

float MusicVolumeScaleFactor = -10000;

float Fixed0 = 0;

float Fixed1000 = 1000;

float Fixed500 = 500;

float GridMultiplier_16 = 16;

float CorpseTimer = 481.0;

double GlobalThreshold = 0;

ClickableRectangle2 SidebarWindowClickBoxes[4] = {
    {11, 370, 68, 383, 0, 0, 1},
    {73, 388, 131, 401, 1, 0, 3},
    {11, 388, 68, 401, 4, 0, 6},
    {73, 370, 131, 383, 5, 0, 2}};

char SidebarWindowSpecialCharacters_c0[15] = {'!', '/', '0', '9', ':', '@', 'A', 'Z', '[', '`', 'a', 'z', '{', '}', '\0'};

int32_t ExperienceTable_CharacterWindow[72] = {0, 2200, 3000, 4000, 666};

WeaponSlotFrame WeaponSlotFrames[44] = {
    {0x1aa, 0x2b, 0x17, 0x100},
    {0x1ab, 0x6b, 0x17, 0x200},
    {0x25b, 0x2a, 0x17, 0x300},
    {0x25a, 0x6b, 0x17, 0x400},
    {0x1ea, 0x6b, 0x15, 0x500},
    {0x21c, 0x6b, 0x15, 0x500},
    {0x1a4, 0xa3, 0xf, 0x700},
    {0x1c4, 0xa3, 0xf, 0x700},
    {0x1e4, 0xa3, 0xf, 0x700},
    {0x204, 0xa3, 0xf, 0x700},
    {0x224, 0xa3, 0xf, 0x700},
    {0x244, 0xa3, 0xf, 0x700},
    {0x264, 0xa3, 0xf, 0x700},
    {0x1a4, 0xc3, 0xf, 0x700},
    {0x1c4, 0xc3, 0xf, 0x700},
    {0x1e4, 0xc3, 0xf, 0x700},
    {0x204, 0xc3, 0xf, 0x700},
    {0x224, 0xc3, 0xf, 0x700},
    {0x244, 0xc3, 0xf, 0x700},
    {0x264, 0xc3, 0xf, 0x700},
    {0x1a4, 0xe3, 0xf, 0x700},
    {0x1c4, 0xe3, 0xf, 0x700},
    {0x1e4, 0xe3, 0xf, 0x700},
    {0x204, 0xe3, 0xf, 0x700},
    {0x224, 0xe3, 0xf, 0x700},
    {0x244, 0xe3, 0xf, 0x700},
    {0x264, 0xe3, 0xf, 0x700},
    {0x1a4, 0x103, 0xf, 0x700},
    {0x1c4, 0x103, 0xf, 0x700},
    {0x1e4, 0x103, 0xf, 0x700},
    {0x204, 0x103, 0xf, 0x700},
    {0x224, 0x103, 0xf, 0x700},
    {0x244, 0x103, 0xf, 0x700},
    {0x264, 0x103, 0xf, 0x700},
    {0x1d4, 0x1d, 0x8, 0x600},
    {0x1e7, 0x1d, 0x8, 0x600},
    {0x1fa, 0x1d, 0x8, 0x600},
    {0x20d, 0x1d, 0x8, 0x600},
    {0x220, 0x1d, 0x8, 0x600},
    {0x233, 0x1d, 0x8, 0x600},
    {0x1d7, 0x39, 0xe, 0x700},
    {0x1f4, 0x39, 0xe, 0x700},
    {0x211, 0x39, 0xe, 0x700},
    {0x22e, 0x39, 0xe, 0x700}};

char InventoryWindowSpecialCharacters[15] = "!/09:@AZ[`az{}";

ClickableRectangle1 MenuWindowClickBoxes_ConfirmQuit[2] = {
    {307, 280, 490, 300, 0, 0},
    {264, 316, 534, 335, 1, 0}};

ClickableRectangle1 MenuWindowClickBoxes[2] = {
    {
        0x14e,
        0xe0,
        0x184,
        0x102,
        0x0,
        0x0,
    },
    {
        0x1a4,
        0xe0,
        0x1cc,
        0x102,
        0x1,
        0x0,
    }};

int32_t AnimationLookup[16] = {
    0x0,
    0x1,
    -1,
    0x1,
    -1,
    0x0,
    -1,
    -1,
    0x0,
    -1,
    0x1,
    -1,
    0x1,
    0x0,
    0x1,
    0x1,
};

int32_t MpCostRelated_UnconfirmedLength[73] = {
    -1, 0x1, -1, 0x1,
    0x0, 0x1, 0x1,

    0x1e,
    0x3c, 0x64, 0xb4, 0x12c,
    0x2bc, 0x32, 0x5a, 0x96,
    0xfa, 0x1c2, 0x352,

    30, 50, 70, 100, 200, 300,
    0x46, 0x64, 0xb4, 0x12c, 0x190, 0x1f4,
    0x19, 0x28, 0x32, 0x50, 0x64, 0xc8,
    0x32, 0x64, 0x96, 0xfa, 0x1f4, 0x320,
    0x64, 0x96, 0xb4, 0xd2, 0xf0, 0x12c,
    0x32, 0x5a, 0x78, 0x96, 0xc8, 0x0,
    0x28, 0x50, 0x96, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

int32_t MagicAnimRel_Unconfirmedength[16] = {
    0, 1, -1, 1,
    -1, 0, -1, -1,
    0, -1, 1, -1,
    1, 0, 1, 1};

char s_mp2[4] = "mp2";

char s_mp1[4] = "mp1";

char s_hp2[4] = "hp2";

char s_hp1[4] = "hp1";

char s_number1[8] = "number1";

char s_exp[4] = "exp";

char s_body[8] = "body";

char s_str6[8] = "str6";

char s_str5[8] = "str5";

char s_str4[8] = "str4";

char s_str3[8] = "str3";

char s_str2[8] = "str2";

char s_str1[8] = "str1";

char s_str0[8] = "str0";

char s_button[8] = "button";

char s_select[8] = "select";

char s_face[8] = "face";

char s_time[8] = "time";

char s_mp[4] = "mp";

char s_hp[4] = "hp";

char s_lvnum[8] = "lvnum";

char s_lv[4] = "lv";

char s_name[8] = "name";

char s_frame[8] = "frame";

char s_number[8] = "number";

char s_main[8] = "main";

char s_win0_act[12] = "win0.act";

char s_win1_act[12] = "win1.act";

char s_slot[8] = "slot";

char s_win2_act[12] = "win2.act";

char s_strg[8] = "strg";

char s_strf[8] = "strf";

char s_stre[8] = "stre";

char s_strd[8] = "strd";

char s_strc[8] = "strc";

char s_strb[8] = "strb";

char s_stra[8] = "stra";

char s_win3_act[12] = "win3.act";

char s__s_d[8] = "%s%d";

char s_string2[8] = "string2";

char s_frame2[8] = "frame2";

char s_string[8] = "string";

char s_menu_act[12] = "menu.act";

char s__d_act[8] = "%d.act";

char s_winc_act[12] = "winc.act";

ClickableRectangle1 MerchantWindowClickBoxes_WindowRelated[3] = {
    {375, 209, 416, 224, 0, 0},
    {372, 228, 419, 245, 1, 0},
    {358, 250, 434, 266, 2, 0}};

ClickableRectangle2 GameWindowBuyClickBoxes[4] = {
    {500, 17, 547, 30, 2, 0, 0},
    {556, 17, 608, 30, 3, 0, 1},
    {176, 36, 608, 100, -1, -1, 2},
    {176, 102, 608, 166, -1, -1, 3}};

char BuyWindowSpecialCharacters_s___09__AZ__az__[15] = "!/09:@AZ[`az{}";

ClickableRectangle2 GameWindowSellClickBoxes[5] = {
    {500, 17, 547, 30, 2, 0, 0},
    {556, 17, 608, 30, 3, 0, 1},
    {176, 36, 608, 100, -1, -1, 2},
    {176, 102, 607, 166, -1, -1, 3},
    {0x39302f21, 0x5a41403a, 0x7a61605b, 0x7d7b, 0x2f21, 0x3930, 0x5a41403a}};

char SellWindowSpecialCharacters_s___09__AZ__az__[15] = "!/09:@AZ[`az{}";

char SaveWindowSupportedCharacterRanges[15] = "!/09:@AZ[`az{}";

char s_say2[8] = "say2";

char s_sfx[4] = "sfx";

char s_boss[8] = "boss";

char s_scroll[8] = "scroll";

char s_effect[8] = "effect";

char s_action[8] = "action";

char s_visual[8] = "visual";

char s_deluser[8] = "deluser";

char s_gang[8] = "gang";

char s_heal[8] = "heal";

char s_group[8] = "group";

char s_party[8] = "party";

char s_save[8] = "save";

char s_receive[8] = "receive";

char s_money[8] = "money";

char s_user0[8] = "user0";

char s_move[8] = "move";

char s_delobj[8] = "delobj";

char s_mart[8] = "mart";

char s_say[4] = "say";

char s_give[8] = "give";

char s_draw[8] = "draw";

char s_switch[8] = "switch";

char s_item[8] = "item";

char s_noise[8] = "noise";

char s_box[4] = "box";

char s_box0[8] = "box0";

char s_talker[8] = "talker";

char s_user[8] = "user";

char s_map[4] = "map";

char s_cloud[8] = "cloud";

char s_anibg[8] = "anibg";

char s_gate[8] = "gate";

char s_magic[8] = "magic";

char s_viewport[12] = "viewport";

char s_type[8] = "type";

char s_music[8] = "music";

char s_check[8] = "check";

char s_movetile[12] = "movetile";

char s_door[8] = "door";

char s_talkbox[8] = "talkbox";

char s_camera[8] = "camera";

char s_command[8] = "command";

char s_endif[8] = "endif";

char s_elseif[8] = "elseif";

char s_if[4] = "if";

char s_yesno[8] = "yesno";

char s_win4_act[12] = "win4.act";

char s_talkbox_bmp[12] = "talkbox.bmp";

char s_efont_fnt[12] = "efont.fnt";

char s_font_fnt[12] = "font.fnt";

char s__s__s__d__d[12] = "%s %s %d %d";

char s__d__d__d[12] = "%d %d %d";

char s_talkbox__wrong_message[24] = "talkbox::wrong-message";

char s__d__d__s[12] = "%d %d %s";

char s__s__d__d[12] = "%s %d %d";

char s__d__d__d__d[12] = "%d %d %d %d";

char s__s__d__d__d__d__d[20] = "%s %d %d %d %d %d";

char s__s__d__d__d[12] = "%s %d %d %d";

char s__s__d__d__x__d[16] = "%s %d %d %x %d";

char s__s__d__d__x[12] = "%s %d %d %x";

char s__s__s__d__d__d__d__d[24] = "%s %s %d %d %d %d %d";

char s__s__s__d__d__d[16] = "%s %s %d %d %d";

char s__d__d__d__d__s__d__d[24] = "%d %d %d %d %s %d %d";

char s__d[4] = "%d";

char s__d__d[8] = "%d %d";

char s__s__d__d__d__d__d__d__d[24] = "%s %d %d %d %d %d %d %d";

char s__s__d__d__d__d[16] = "%s %d %d %d %d";

char Scrip_1_0[2] = {'1', 0x0};

char Script_0_0[2] = {'0', 0x0};

char InterpolatableString[4] = "%s";

char s_script_e_txt[16] = "script-e.txt";

char s_win5_act[12] = "win5.act";

char s_title[8] = "title";

char s_outline[8] = "outline";

char s_win6_act[12] = "win6.act";

char s__d_GOLD[8] = "%d GOLD";

char s_win7_act[12] = "win7.act";

char s_win9_act[12] = "win9.act";

char s_wb[4] = "wb";

const char s_EMPTY[8] = "EMPTY";

char s_hazard_sav[12] = "hazard.sav";

char s_rb[4] = "rb";

char s___7s__02d__02d__02d__02d[28] = "%-7s %02d/%02d %02d:%02d";

char s_wina_act[12] = "wina.act";

char s__[4] = "?";

char s_debug[8] = "debug";

int32_t RedOffset1 = 0xa;

int32_t RedOffset2 = 0x5;

int32_t InvRedOffset = 0x3;

int32_t GreenOffset1 = 0x5;

int32_t GreenOffset2 = 0x5;

int32_t InvGreenOffset = 0x3;

int32_t BlueOffset1 = 0x0;

int32_t BlueOffset2 = 0x5;

int32_t InvBlueOffset = 0x3;

uint16_t RgbMask = 0x7bde;

char s_Fail_to_get_pixel_format[28] = "Fail to get pixel-format";

char s_Your_DirectDraw_Device_doesn_t_c[56] = "Your DirectDraw Device doesn't create a Primary Surface";

char s_Time_to_error[16] = "Time to error";

char s_Your_direct_draw_device_doesn_t_i[60] = "Your direct-draw device\ndoesn't\ninitialize 640x480xhicolor.";

char s_Direct_X_isn_t_installed[28] = "Direct X\nisn't\ninstalled";

char s_Time_to_Stop[16] = "Time to Stop";

int32_t AdpcmIndexAdjustTable[16] = {-1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8};

int32_t AdpcmStepSizeTable[89] = {
    0x7,
    0x8,
    0x9,
    0xa,
    0xb,
    0xc,
    0xd,
    0xe,
    0x10,
    0x11,
    0x13,
    0x15,
    0x17,
    0x19,
    0x1c,
    0x1f,
    0x22,
    0x25,
    0x29,
    0x2d,
    0x32,
    0x37,
    0x3c,
    0x42,
    0x49,
    0x50,
    0x58,
    0x61,
    0x6b,
    0x76,
    0x82,
    0x8f,
    0x9d,
    0xad,
    0xbe,
    0xd1,
    0xe6,
    0xfd,
    0x117,
    0x133,
    0x151,
    0x173,
    0x198,
    0x1c1,
    0x1ee,
    0x220,
    0x256,
    0x292,
    0x2d4,
    0x31c,
    0x36c,
    0x3c3,
    0x424,
    0x48e,
    0x502,
    0x583,
    0x610,
    0x6ab,
    0x756,
    0x812,
    0x8e0,
    0x9c3,
    0xabd,
    0xbd0,
    0xcff,
    0xe4c,
    0xfba,
    0x114c,
    0x1307,
    0x14ee,
    0x1706,
    0x1954,
    0x1bdc,
    0x1ea5,
    0x21b6,
    0x2515,
    0x28ca,
    0x2cdf,
    0x315b,
    0x364b,
    0x3bb9,
    0x41b2,
    0x4844,
    0x4f7e,
    0x5771,
    0x602f,
    0x69ce,
    0x7462,
    0x7fff,
};

char s_track_02d_pcm[16] = "track%02d.pcm";

char s_Direct_Sound_Error[20] = "Direct Sound Error";

char s_Error[12] = "Error";

PathfindingDirection PathfindingDirectionLookup[8] = {
    {0, 1, 0, 2, {{0, 2}, {1, 2}, {0, 0}}},
    {-1, 0, 2, 2, {{-1, 0}, {-1, 1}, {0, 0}}},
    {0, -1, 4, 2, {{0, -1}, {1, -1}, {0, 0}}},
    {1, 0, 6, 2, {{2, 0}, {2, 1}, {0, 0}}},
    {-1, 1, 1, 3, {{-1, 1}, {-1, 2}, {0, 2}}},
    {-1, -1, 3, 3, {{-1, 0}, {-1, -1}, {0, -1}}},
    {1, -1, 5, 3, {{1, -1}, {2, -1}, {2, 0}}},
    {1, 1, 7, 3, {{2, 1}, {2, 2}, {1, 2}}}};

char Flag_ParseBmp_14[4] = "BM";

char s_end[4] = "end";

int32_t FlagCursorRelated = -0x1;

char s_snaik[8] = "snaik";

char s_varcu[8] = "varcu";

char s_dov[4] = "dov";

char s_sha[4] = "sha";

char s_aris[8] = "aris";

char s_enlike[8] = "enlike";

char s_meil[8] = "meil";

char s_bar[4] = "bar";

char s_armi[8] = "armi";

char s_rick[8] = "rick";

char s_step[8] = "step";

char s_warp[8] = "warp";

char s_outofsight[12] = "outofsight";

char s_talk[8] = "talk";

char s_open[8] = "open";

char s_get[4] = "get";

char s_board[8] = "board";

char s_ctrl[8] = "ctrl";

char s_attack[8] = "attack";

char s_dongo[8] = "dongo";

char s_go[4] = "go";

char s_normal[8] = "normal";

char s_win8_act[12] = "win8.act";

char s_cursor_act[12] = "cursor.act";

char s_scene_txt[12] = "scene.txt";

char s_Wrong_Command[16] = "Wrong Command";

char s_Error_in_cFRAME[16] = "Error in cFRAME";

char s_haz__d_bmp[12] = "haz#%d.bmp";

char s_item00_act[12] = "item00.act";

char s___d[4] = "@%d";

char s_item00_error[16] = "item00:error";

char s__s__d[8] = "%s %d";

char s_item00_txt[12] = "item00.txt";

int32_t FlagGameIsRunning = 0x1;

int32_t TimeResolution_45or15 = 0x2d;

IntegerVirtualKeyPair InputCodes[22] = {
    {InternalKey::InternalKey_ESCAPE, VK_ESCAPE},
    {InternalKey::InternalKey_1, VK_1},
    {InternalKey::InternalKey_2, VK_2},
    {InternalKey::InternalKey_3, VK_3},
    {InternalKey::InternalKey_4, VK_4},
    {InternalKey::InternalKey_5, VK_5},
    {InternalKey::InternalKey_SPACE, VK_SPACE},
    {InternalKey::InternalKey_W, VK_W},
    {InternalKey::InternalKey_I, VK_I},
    {InternalKey::InternalKey_C, VK_C},
    {InternalKey::InternalKey_P, VK_P},
    {InternalKey::InternalKey_F1, VK_F1},
    {InternalKey::InternalKey_F2, VK_F2},
    {InternalKey::InternalKey_F3, VK_F3},
    {InternalKey::InternalKey_F4, VK_F4},
    {InternalKey::InternalKey_M, VK_M},
    {InternalKey::InternalKey_UP, VK_UP},
    {InternalKey::InternalKey_LEFT, VK_LEFT},
    {InternalKey::InternalKey_RIGHT, VK_RIGHT},
    {InternalKey::InternalKey_DOWN, VK_DOWN},
    {InternalKey::InternalKey_F11, VK_F11},
    {InternalKey::InternalKey_CONTROL, VK_CONTROL},
};

char s__d__s__d[12] = "%d %s %d";

char s_sfx_txt[8] = "sfx.txt";

char s__HAZARD__Pumpkin_Soft[24] = "\"HAZARD\" Pumpkin-Soft";

char s_hpatch_002[12] = "hpatch.002";

char s_hpatch_001[12] = "hpatch.001";

char s_music_pak[12] = "music.pak";

char s_hazard_pak[12] = "hazard.pak";

char s_visual_pak[12] = "visual.pak";

char s__visual_pa_[12] = "_visual.pa_";

char s__Please_Insert_a_Hazard_CD_Disk[40] = "\n Please\n Insert a Hazard CD-Disk  \n";

char s_c___hazard_pa_[16] = "c:\\_hazard.pa_";

char s_PumpkinSoft[12] = "PumpkinSoft";

char s_c__[4] = {'c', ':', '\\', '\0'};

uint32_t GoldAmount = 0x1f4;

InventoryItemStruct ItemInventory[32] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

UnlockDoorTuple UnlockDoorDirectionalTuple[8] = {{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};

char s_ropen[8] = "ropen";

char s_lopen[8] = "lopen";

char s_bopen[8] = "bopen";

char s_fopen[8] = "fopen";

char s_ropened[8] = "ropened";

char s_lopened[8] = "lopened";

char s_bopened[8] = "bopened";

char s_fopened[8] = "fopened";

char s_rstand[8] = "rstand";

char s_lstand[8] = "lstand";

char s_bstand[8] = "bstand";

char s_fstand[8] = "fstand";

char s_stand[8] = "stand";

char s_blood_act[12] = "blood.act";

char s__sfx[8] = "@sfx";

char s__item[8] = "@item";

char s_change3[8] = "change3";

char s_change2[8] = "change2";

char s_change1[8] = "change1";

char s_attack3[8] = "attack3";

char s_attack2[8] = "attack2";

char s_attack1[8] = "attack1";

char s_stand4[8] = "stand4";

char s_stand3[8] = "stand3";

char s_stand2[8] = "stand2";

char s_stand1[12] = "stand1";

DirectionalTuple DirectionalTuples[8] = {
    {0, 1},
    {-1, 1},
    {-1, 0},
    {-1, -1},
    {0, -1},
    {1, -1},
    {1, 0},
    {1, 1},
};

DirectionOffsets HitRngRelated1[8] = {
    {0, 2, 1, 2},
    {-1, 2, -1, 2},
    {-1, 1, -1, 0},
    {-1, -1, -1, -1},
    {0, -1, 1, -1},
    {2, -1, 2, -1},
    {2, 0, 2, 1},
    {2, 2, 2, 2}};

int32_t MovementLookupTable2[25] = {
    7,
    0,
    0,
    0,
    1,
    6,
    8,
    8,
    8,
    2,
    6,
    8,
    8,
    8,
    2,
    6,
    8,
    8,
    8,
    2,
    5,
    4,
    4,
    4,
    3,
};

int32_t MovementLookupTable1[25] = {
    8, 6, 8, 2,
    8, 0, 8, 8,
    8, 0, 8, 8,
    8, 8, 8, 4,
    8, 8, 8, 4,
    8, 6, 8, 2, 8};

const char* CattIndexes[10] = {
    "catt1-1",
    "catt1-2",
    "catt2-1",
    "catt2-2",
    "catt3-1",
    "catt3-2",
    "catt4-1",
    "catt4-2",
    "catt5-1",
    "catt5-2"};

int32_t FrameRelated = -0x1;

DirectionOffsets CollisionHelper_ARRAY[8] = {
    {0, 2, 1, 2},
    {-1, 2, -1, 2},
    {-1, 1, -1, 0},
    {-1, -1, -1, -1},
    {0, -1, 1, -1},
    {2, -1, 2, -1},
    {2, 0, 2, 1},
    {2, 2, 2, 2},

};

char s_m_shasha_act[16] = "m-shasha.act";

char s_m_aris_act[12] = "m-aris.act";

char s_m_armi_act[12] = "m-armi.act";

char s__res_la[8] = "@res-la";

char s__res_w[8] = "@res-w";

char s__res_li[8] = "@res-li";

char s__res_i[8] = "@res-i";

char s__res_f[8] = "@res-f";

char s_catt5_2[8] = "catt5-2";

char s_catt5_1[8] = "catt5-1";

char s_catt4_2[8] = "catt4-2";

char s_catt4_1[8] = "catt4-1";

char s_catt3_2[8] = "catt3-2";

char s_catt3_1[8] = "catt3-1";

char s_catt2_2[8] = "catt2-2";

char s_catt2_1[8] = "catt2-1";

char s_catt1_2[8] = "catt1-2";

char s_catt1_1[8] = "catt1-1";

char s_snaik4t_act[12] = "snaik4t.act";

char s_snaik4b_act[12] = "snaik4b.act";

char s_snaik3t_act[12] = "snaik3t.act";

char s_snaik3b_act[12] = "snaik3b.act";

char s_snaik2t_act[12] = "snaik2t.act";

char s_snaik2b_act[12] = "snaik2b.act";

char s_snaik1t_act[12] = "snaik1t.act";

char s_snaik1b_act[12] = "snaik1b.act";

char s_varcu3t_act[12] = "varcu3t.act";

char s_varcu3b_act[12] = "varcu3b.act";

char s_varcu2t_act[12] = "varcu2t.act";

char s_varcu2b_act[12] = "varcu2b.act";

char s_varcu1t_act[12] = "varcu1t.act";

char s_varcu1b_act[12] = "varcu1b.act";

char s_dov3t_act[12] = "dov3t.act";

char s_dov3b_act[12] = "dov3b.act";

char s_dov2t_act[12] = "dov2t.act";

char s_dov2b_act[12] = "dov2b.act";

char s_dov1t_act[12] = "dov1t.act";

char s_dov1b_act[12] = "dov1b.act";

char s_sha3t_act[12] = "sha3t.act";

char s_sha3b_act[12] = "sha3b.act";

char s_sha2t_act[12] = "sha2t.act";

char s_sha2b_act[12] = "sha2b.act";

char s_sha1t_act[12] = "sha1t.act";

char s_sha1b_act[12] = "sha1b.act";

char s_aris3t_act[12] = "aris3t.act";

char s_aris3b_act[12] = "aris3b.act";

char s_aris2t_act[12] = "aris2t.act";

char s_aris2b_act[12] = "aris2b.act";

char s_aris1t_act[12] = "aris1t.act";

char s_aris1b_act[12] = "aris1b.act";

char s_enli3t_act[12] = "enli3t.act";

char s_enli3b_act[12] = "enli3b.act";

char s_enli2t_act[12] = "enli2t.act";

char s_enli2b_act[12] = "enli2b.act";

char s_enli1t_act[12] = "enli1t.act";

char s_enli1b_act[12] = "enli1b.act";

char s_meil3t_act[12] = "meil3t.act";

char s_meil3b_act[12] = "meil3b.act";

char s_meil2t_act[12] = "meil2t.act";

char s_meil2b_act[12] = "meil2b.act";

char s_meil1t_act[12] = "meil1t.act";

char s_meil1b_act[12] = "meil1b.act";

char s_bar3t_act[12] = "bar3t.act";

char s_bar3b_act[12] = "bar3b.act";

char s_bar2t_act[12] = "bar2t.act";

char s_bar2b_act[12] = "bar2b.act";

char s_bar1t_act[12] = "bar1t.act";

char s_bar1b_act[12] = "bar1b.act";

char s_armi3t_act[12] = "armi3t.act";

char s_armi3b_act[12] = "armi3b.act";

char s_armi2t_act[12] = "armi2t.act";

char s_armi2b_act[12] = "armi2b.act";

char s_armi1t_act[12] = "armi1t.act";

char s_armi1b_act[12] = "armi1b.act";

char s_rickbt_act[12] = "rickbt.act";

char s_rick4b_act[12] = "rick4b.act";

char s_rick3t_act[12] = "rick3t.act";

char s_rick3b_act[12] = "rick3b.act";

char s_rick2t_act[12] = "rick2t.act";

char s_rick2b_act[12] = "rick2b.act";

char s_rick1t_act[12] = "rick1t.act";

char s_rick1b_act[12] = "rick1b.act";

char s_mark2_bmp[12] = "mark2.bmp";

char s__d__d__d__d__d__d__d__d__d[28] = "%d %d %d %d %d %d %d %d %d";

char s__d__d__d__d__d[16] = "%d %d %d %d %d";

char s__d__d__d__d__d__d__d__d[24] = "%d %d %d %d %d %d %d %d";

char s_default_txt[12] = "default.txt";

char s_Miss_Match[12] = "Miss Match";

char s_AI[4] = "AI";

char s__magic[8] = "@magic";

char s___[4] = "??";

char s_object[8] = "object";

char s_satt[8] = "satt";

char s_dead[8] = "dead";

char s_damage[8] = "damage";

char s_guard2[8] = "guard2";

char s_guard1[8] = "guard1";

char s_natt2[8] = "natt2";

char s_natt1[8] = "natt1";

char s_3natt2[8] = "3natt2";

char s_2natt2[8] = "2natt2";

char s_1natt2[8] = "1natt2";

char s_3natt1[8] = "3natt1";

char s_2natt1[8] = "2natt1";

char s_1natt1[8] = "1natt1";

char s_walk[8] = "walk";

char s__addexp[8] = "@addexp";

char s__eye[8] = "@eye";

char s__guard[8] = "@guard";

char s__tohit[8] = "@tohit";

char s__speed[8] = "@speed";

char s__power[8] = "@power";

char s__mp[4] = "@mp";

char s__hp[4] = "@hp";

char s_wtoby_act[12] = "wtoby.act";

char s_levelup_act[12] = "levelup.act";

char s_item_error[12] = "item error";

char s_Item__d___d[12] = "Item#%d: %d";

char s_re_dark_act[12] = "re-dark.act";

char s_re_mp_act[12] = "re-mp.act";

char s_re_hp_act[12] = "re-hp.act";

signed char DirectionalLookupTable[8] = {0, 0, '\xff', '\xff', 0, '\xff', '\xff', 0};

char s_MAPNAME[8] = "MAPNAME";

int32_t VisualFlag_InitiallyMinusOne = -0x1;

VisualTxtItem VisualTxtItems[6] = {
    {0, {118, 105, 115, 117, 97, 108}, {0}, 0, 0, 0, 0},
    {0, {118, 105, 115, 117, 97, 108}, {0}, 0, 0, 0, 0},
    {0, {118, 105, 115, 117, 97, 108}, {0}, 0, 0, 0, 0},
    {0, {0, 0, 0, 0, 0, 0}, {0}, 0, 0, 0, 0},
    {0, {0, 0, 0, 0, 0, 0}, {0}, 0, 0, 0, 0},
    {0, {0, 0, 0, 0, 0, 0}, {0}, 0, 0, 0, 0}};

ClickableRectangle3 StartMenuClickBoxes[4] = {
    {211, 211, 434, 253, 0, 1},
    {206, 273, 440, 296, 1, 2},
    {185, 310, 469, 333, 2, 4},
    {279, 356, 371, 378, 3, 3}};

char StartEndCharacters___09__AZ__az__[16] = "!/09:@AZ[`az{}";

char s__s__s__d[12] = "%s %s %d";

char s_visual_txt[12] = "visual.txt";

char s_menu_snd[12] = "menu.snd";

char s_mainmenu_act[16] = "mainmenu.act";

char s_winb_act[12] = "winb.act";

char s_rect[8] = "rect";

char s_gate0[8] = "gate0";

char s_macro[8] = "macro";

char s_Wrong_Message[16] = "Wrong Message";

char s__d__d__d__d__d__d[20] = "%d %d %d %d %d %d";

char s_cLOADWLD[12] = "cLOADWLD";

int32_t RngSeed = 0x1;

int32_t WriteErrorLogConfig = 0x2;

ErrorEntry LowerUpperErrorDictionary[45] = {{1, 22}, {2, 2}, {3, 2}, {4, 24}, {5, 13}, {6, 9}, {7, 12}, {8, 12}, {9, 12}, {10, 7}, {11, 8}, {12, 22}, {13, 22}, {15, 2}, {16, 13}, {17, 18}, {18, 2}, {33, 13}, {53, 2}, {65, 13}, {67, 2}, {80, 17}, {82, 13}, {83, 13}, {87, 22}, {89, 11}, {108, 13}, {109, 32}, {112, 28}, {114, 9}, {6, 22}, {128, 10}, {129, 10}, {130, 9}, {131, 22}, {132, 13}, {145, 41}, {158, 13}, {161, 2}, {164, 11}, {167, 13}, {183, 17}, {206, 2}, {215, 11}, {1816, 12}};

int32_t* FontPixelMap = 00000000;

int16_t* TalkboxImageVector = 00000000;

int16_t SingleRowPixels640[640] = {0};

IDirectDrawSurface* DirectDrawSurface = 00000000;

uint32_t MovieCallCounter = 0x0;

int32_t PauseState = 0x0;

IDirectDraw* DirectDrawObject = 00000000;

MusicObject* PtrMusicObject = 00000000;

SfxObject* PtrSfxObject = 00000000;

LPDIRECTSOUND DirectSoundObject = 00000000;

GlobalStruct2048 GlobalStructColors2048 = {0};

int16_t CameraCanvas[20480] = {0};

PathfindingDirection* PathfindingLatestDirection = 00000000;

ActSummary* LatestLoadedAct = 00000000;

byte* NestedLoadActHelperConstant = 00000000;

uint32_t SizeInMemory_ActString = 0x0;

SpriteMapPair* LoadActHelperSpriteMapPair = 0x0;

PathfindingNodesBlock* WrapperRelated = 00000000;

ItemRawCollection* RawItemCollection62k = 0;

char CurrentSceneName[16] = {'\0'};

char ScreenshotFilename[24] = {'\0'};

int32_t ScreenshotCounter = 0x0;

GameState GlobalHazGameState = {};

HWND GameFullscreenWindow = 00000000;

uint32_t FlagRelatedToLoadingSfx = 0x0;

char InputStates128[128] = {'\0'};

int32_t GameStateFlag = 0x0;

RunTickClass* CurrentRunTickClass = 0;

uint32_t MouseInput = 0x0;

float GatedTick = 0;

LPCSTR lpCaption = 00000000;

int32_t MouseButtonClick = 0x0;

int32_t CursorXCoord = 0x0;

int32_t CursorYCoord = 0x0;

ObjectWrapper* ObjectList = 0;

ActiveCharacter* TeamCharacterList[12] = {0};

ActiveCharacter* BenchedCharacterList[12] = {0};

ActiveCharacter* ActiveTeamCharacterSlots[5] = {0};

LPDIRECTSOUNDBUFFER ListOfSfxBuffers[100] = {0};

int32_t* GameFlags = 0;

CoreActClass* Item00Act = 00000000;

ItemReferenceCollection* ItemStruct12k = 0;

GameWindow* GameWindowRightSide = 00000000;

GameWindow* GameWindowLeftSidebar = 00000000;

int32_t IncrementGradually = 0x0;

int32_t BloodActStand = 0x0;

int32_t NestedContentFromAct = 0x0;

CoreActClass* BloodActObject = 00000000;

int32_t HasLoadedDefaultTxt = 0x0;

int32_t OrientationRelated = 0x0;

ImageVectorWithHeader* LoadMark2 = 0x0;

int16_t CursorSpriteRelated[2560] = {0};

int32_t SCCommandRelated = 0x00000000;

byte* BackgroundSpriteImageAddress = 00000000;

LargeTmpObject BackgroundSpriteObject = {0, {0}};

UnpackedFilePakStruct* GlobalUnpackedFilePakStruct = 00000000;

UnpackedFileBase* UnpackedSceneTxtContent = 00000000;

int32_t NewSceneIndex = 0x0;

int32_t GlobalSceneInstanceIndex = 0x0;

int32_t HandlesUpperValue = 0x0;

int32_t HandlesLowerValue = 0x0;

uint32_t ReadFileRelated = 0x0;

int32_t ReadFileFlag = 0x0;

FileHandleComponent* FileHandleComponentAddresses[64] = {0};

UINT uNumber = 0x0;

StringIntegerMap PointerKeyValuePair_ARRAY[30] = {
    {s_if, 1},
    {s_elseif, 2},
    {s_endif, 3},
    {s_command, 4},
    {s_camera, 5},
    {s_talkbox, 6},
    {s_door, 7},
    {s_button, 8},
    {s_movetile, 9},
    {s_check, 10},
    {s_music, 11},
    {s_type, 12},
    {s_viewport, 13},
    {s_magic, 14},
    {s_gate, 15},
    {s_anibg, 16},
    {s_cloud, 17},
    {s_map, 18},
    {s_user, 19},
    {s_talker, 20},
    {s_box0, 21},
    {s_box, 22},
    {s_noise, 23},
    {s_item, 24},
    {s_switch, 25},
    {s_gate0, 30},
    {s_rect, 31},
    {s_user0, 34},
    {s_step, 35},
    {s_boss, 48}};

char* PointersMagicAnimation[10] = {0, s_m_armi_act, 0, 0, 0, s_m_aris_act, s_m_shasha_act, 0, 0, 0};

char* ListOfResistances[6] = {nullptr, s__res_f, s__res_i, s__res_li, s__res_w, s__res_la};

DefaultCharacterStats ListOfDefaultCharacterStats[11] = {
    {s_rick, 0, 58, 58, 54, 54, 4, 6, 5, 5, 0, 0, 30, 0, 0, 30, 2, 30, 25, 25, 20, 0, 1, 0, 0, 0, s_rick1b_act, s_rick1t_act, s_rick2b_act, s_rick2t_act, s_rick3b_act, s_rick3t_act, s_rick4b_act, s_rickbt_act},
    {s_armi, 1, 32, 32, 71, 71, 2, 7, 5, 6, 2, 10, 5, 15, 10, 50, 0, 20, 30, 20, 30, 0, 1, 0, 0, 0, s_armi1b_act, s_armi1t_act, s_armi2b_act, s_armi2t_act, s_armi3b_act, s_armi3t_act, s_armi3b_act, s_armi3t_act},
    {s_bar, 2, 71, 71, 34, 34, 7, 4, 6, 3, 0, 0, 0, 0, 30, 30, 1, 35, 20, 30, 20, 0, 1, 0, 0, 0, s_bar1b_act, s_bar1t_act, s_bar2b_act, s_bar2t_act, s_bar3b_act, s_bar3t_act, s_bar3b_act, s_bar3t_act},
    {s_meil, 3, 62, 62, 44, 44, 5, 6, 4, 5, 0, 30, 0, 0, 0, 30, 3, 25, 30, 20, 25, 0, 1, 0, 0, 0, s_meil1b_act, s_meil1t_act, s_meil2b_act, s_meil2t_act, s_meil3b_act, s_meil3t_act, s_meil3b_act, s_meil3t_act},
    {s_enlike, 4, 38, 38, 66, 66, 5, 6, 4, 7, 5, 4, 2, 7, 1, 50, 1, 15, 30, 20, 35, 0, 1, 0, 0, 0, s_enli1b_act, s_enli1t_act, s_enli2b_act, s_enli2t_act, s_enli3b_act, s_enli3t_act, s_enli3b_act, s_enli3t_act},
    {s_aris, 5, 41, 41, 62, 62, 3, 7, 4, 6, 15, 3, 10, 5, 8, 50, 0, 15, 35, 20, 30, 0, 1, 0, 0, 0, s_aris1b_act, s_aris1t_act, s_aris2b_act, s_aris2t_act, s_aris3b_act, s_aris3t_act, s_aris3b_act, s_aris3t_act},
    {s_sha, 6, 32, 32, 68, 68, 4, 6, 4, 6, 15, 0, 20, 0, 0, 50, 2, 20, 30, 20, 30, 0, 1, 0, 0, 0, s_sha1b_act, s_sha1t_act, s_sha2b_act, s_sha2t_act, s_sha3b_act, s_sha3t_act, s_sha3b_act, s_sha3t_act},
    {s_dov, 7, 72, 72, 28, 28, 8, 3, 7, 2, 0, 30, 0, 0, 0, 30, 0, 40, 15, 35, 10, 0, 1, 0, 0, 0, s_dov1b_act, s_dov1t_act, s_dov2b_act, s_dov2t_act, s_dov3b_act, s_dov3t_act, s_dov3b_act, s_dov3t_act},
    {s_varcu, 8, 70, 70, 30, 30, 5, 5, 3, 7, 0, 0, 0, 30, 0, 30, 4, 25, 15, 35, 10, 0, 1, 0, 0, 0, s_varcu1b_act, s_varcu1t_act, s_varcu2b_act, s_varcu2t_act, s_varcu3b_act, s_varcu3t_act, s_varcu3b_act, s_varcu3t_act},
    {s_snaik, 9, 74, 74, 70, 70, 60, 50, 50, 30, 30, 0, 0, 0, 0, 30, 2, 30, 25, 25, 20, 0, 1, 0, 0, 0, s_snaik1b_act, s_snaik1t_act, s_snaik2b_act, s_snaik2t_act, s_snaik3b_act, s_snaik3t_act, s_snaik4b_act, s_snaik4t_act},
    {0, 0, 0, 0, 0, 0, 60, 50, 50, 30, 30, 0, 0, 0, 0, 30, 2, 30, 25, 25, 20, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

char* Switch_s_fopen[4] = {s_fopen, s_bopen, s_lopen, s_ropen};

char* Switch1_s_fstand[4] = {s_fstand, s_bstand, s_lstand, s_rstand};

char* Switch1_s_fopened[4] = {s_fopened, s_bopened, s_lopened, s_ropened};

char* Switch_s_fopened[4] = {s_fopened, s_bopened, s_lopened, s_ropened};

char* Switch_s_fstand[4] = {s_fstand, s_bstand, s_lstand, s_rstand};

char* Button3_s_fstand[4] = {s_fstand, s_bstand, s_lstand, s_rstand};

char* Button2_s_fopen[4] = {s_fopen, s_bopen, s_lopen, s_ropen};

char* Button1_s_fopened[4] = {s_fopened, s_bopened, s_lopened, s_ropened};

char* Button0_s_fopen[4] = {s_fopen, s_bopen, s_lopen, s_ropen};

char* Button_s_fstand[4] = {s_fstand, s_bstand, s_lstand, s_rstand};

char* Box_s_fopen[4] = {s_fopen, s_bopen, s_lopen, s_ropen};

char* Box_s_fopened[4] = {s_fopened, s_bopened, s_lopened, s_ropened};

char* Box_s_fstand[8] = {s_fstand, s_bstand, s_lstand, s_rstand, s_fopened, s_bopened, s_lopened, s_ropened};

char* CharacterNames[10] = {s_rick, s_armi, s_bar, s_meil, s_enlike, s_aris, s_sha, s_dov, s_varcu, s_snaik};

StringIntegerMap ScriptCommand_ARRAY[47] = {
    {s_if, 1},
    {s_elseif, 2},
    {s_endif, 3},
    {s_command, 4},
    {s_camera, 5},
    {s_talkbox, 6},
    {s_door, 7},
    {s_button, 8},
    {s_movetile, 9},
    {s_check, 10},
    {s_music, 11},
    {s_type, 12},
    {s_viewport, 13},
    {s_magic, 14},
    {s_gate, 15},
    {s_anibg, 16},
    {s_cloud, 17},
    {s_map, 18},
    {s_user, 19},
    {s_talker, 20},
    {s_box0, 21},
    {s_box, 22},
    {s_noise, 23},
    {s_item, 24},
    {s_switch, 25},
    {s_draw, 26},
    {s_give, 27},
    {s_say, 28},
    {s_mart, 29},
    {s_delobj, 32},
    {s_move, 33},
    {s_user0, 34},
    {s_money, 36},
    {s_receive, 37},
    {s_save, 38},
    {s_party, 39},
    {s_group, 40},
    {s_heal, 41},
    {s_gang, 42},
    {s_deluser, 43},
    {s_visual, 44},
    {s_action, 45},
    {s_effect, 46},
    {s_scroll, 47},
    {s_boss, 48},
    {s_sfx, 49},
    {s_say2, 50}};

char* ListOfCharacterWindowActions[9] = {s_frame, s_body, s_exp, s_number1, s_hp1, s_hp2, s_mp1, s_mp2, s_lvnum};

char* ListOfSidebarActions[19] = {s_main, s_number, s_frame, s_name, s_lv, s_lvnum, s_hp, s_mp, s_time, s_face, s_select, s_button, s_str0, s_str1, s_str2, s_str3, s_str4, s_str5, s_str6};

int32_t ExperienceTable_Leveling[72] = {1000, 2200, 3000, 4000, 666};
