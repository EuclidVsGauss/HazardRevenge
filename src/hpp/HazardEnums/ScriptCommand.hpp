#ifndef HAZARD_SCRIPTPARSERENUM_HPP
#define HAZARD_SCRIPTPARSERENUM_HPP

#include "HazardTypedef.hpp"

typedef int32_t ScriptCommandEnum;

struct ScriptCommand {
  enum Value {
    script_if = 1,
    script_elseif = 2,
    script_endif = 3,
    script_command = 4,
    script_camera = 5,
    script_talkbox = 6,
    script_door = 7,
    script_button = 8,
    script_movetile = 9,
    script_check = 10,
    script_music = 11,
    script_type = 12,
    script_viewport = 13,
    script_magic = 14,
    script_gate = 15,
    script_anibg = 16,
    script_cloud = 17,
    script_map = 18,
    script_user = 19,
    script_talker = 20,
    script_box0 = 21,
    script_box = 22,
    script_noise = 23,
    script_item = 24,
    script_switch = 25,
    script_draw = 26,
    script_give = 27,
    script_say = 28,
    script_mart = 29,
    script_delobj = 32,
    script_move = 33,
    script_user0 = 34,
    script_money = 36,
    script_receive = 37,
    script_save = 38,
    script_party = 39,
    script_group = 40,
    script_heal = 41,
    script_gang = 42,
    script_deluser = 43,
    script_visual = 44,
    script_action = 45,
    script_effect = 46,
    script_scroll = 47,
    script_boss = 48,
    script_sfx = 49,
    script_say2 = 50
  };
};

#endif
