#include <SDL3/SDL_main.h>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#ifndef _MSC_VER
#include <SDL3/SDL_platform.h>
#endif

bool ARGV_PLAY_IN_FULLSCREEN = true;
const char* requiredFiles[] = {"hazard.pak", "visual.pak", "music.pak"};

HMODULE handle;
UINT tagMsgWParam;

UINT MainFunction(HINSTANCE);
void InitPakPaths();
bool CheckRequiredFileMissing();
void ParseCommandLine(int argc, char* argv[]);

int main(int argc, char* argv[]) {
#if (defined(SDL_PLATFORM_IOS) || defined(__IPHONEOS__)) == 0
  if (CheckRequiredFileMissing()) {
    return 1;
  }
#endif
  ParseCommandLine(argc, argv);
  handle = GetModuleHandleA(nullptr);
  tagMsgWParam = MainFunction(handle);
  return 0;
}


bool CheckRequiredFileMissing() {
  for (const char* file : requiredFiles) {
    if (!std::ifstream(file).is_open()) {
      std::cerr << "File is missing: " << file << std::endl;
      return true;
    }
  }
  return false;
}

void ParseCommandLine(int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--fullscreen") == 0 ||
        strcmp(argv[i], "--full-screen") == 0) {
      ARGV_PLAY_IN_FULLSCREEN = true;
    }
    else if (strcmp(argv[i], "--window") == 0 ||
             strcmp(argv[i], "--windowed") == 0) {
      ARGV_PLAY_IN_FULLSCREEN = false;
    }
  }
}
