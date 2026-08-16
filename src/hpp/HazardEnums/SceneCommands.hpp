#ifndef HAZARD_SCENEPARSERENUM_HPP
#define HAZARD_SCENEPARSERENUM_HPP

#include "HazardTypedef.hpp"

typedef int32_t SceneCommandsEnum;

struct SceneCommands {
  enum Value {
    scene_if = 1,
    scene_elseif = 2,
    scene_endif = 3,
    scene_command = 4,
    scene_camera = 5,
    scene_talkbox = 6,
    scene_door = 7,
    scene_button = 8,
    scene_movetile = 9,
    scene_check = 10,
    scene_music = 11,
    scene_type = 12,
    scene_viewport = 13,
    scene_magic = 14,
    scene_gate = 15,
    scene_anibg = 16,
    scene_cloud = 17,
    scene_map = 18,
    scene_user = 19,
    scene_talker = 20,
    scene_box0 = 21,
    scene_box = 22,
    scene_noise = 23,
    scene_item = 24,
    scene_switch = 25,
    scene_gate0 = 30,
    scene_rect = 31,
    scene_user0 = 34,
    scene_step = 35,
    scene_boss = 48,
  };
};

#endif
