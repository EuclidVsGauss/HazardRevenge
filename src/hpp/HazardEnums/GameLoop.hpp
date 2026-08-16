#ifndef HAZARD_GAMELOOPENUM_HPP
#define HAZARD_GAMELOOPENUM_HPP

#include "HazardTypedef.hpp"

typedef int32_t GameLoopEnum;

struct GameLoop {
  enum Value {
    LoadSoundsPlayLogo = 0,
    None0x01 = 1,
    PlayIntro = 2,
    InitGame1 = 3,
    LoadMenuB = 4,
    LoadSaveEtc = 5,
    PlayEndingMovie = 6,
    ShutDown = 7,
    PlaySkc = 8
  };
};

#endif
