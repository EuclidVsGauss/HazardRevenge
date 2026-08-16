#include <win2sdl.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

bool ARGV_PLAY_IN_FULLSCREEN = true;
const char* requiredFiles[] = {"hazard.pak", "visual.pak", "music.pak"};

HMODULE handle;
UINT tagMsgWParam;

UINT MainFunction(HINSTANCE);
bool CheckRequiredFileMissing();
void ParseCommandLine(int argc, char* argv[]);

int32_t main(int32_t argc, char* argv[]) {
  if(CheckRequiredFileMissing()) {
    return 1;
  }
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
