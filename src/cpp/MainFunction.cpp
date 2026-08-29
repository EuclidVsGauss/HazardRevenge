#include <stdio.h>
#include <windows.h>
#include "HazardGlobals.hpp"
#include "HazardPatches.hpp"
#ifndef _MSC_VER
#include <SDL3/SDL_filesystem.h>
#include <string>
#include <SDL3/SDL_platform.h>
#endif

const byte VirtualKey_C = 0x43;
const byte VirtualKey_F = 0x46;
const byte VirtualKey_K = 0x4b;
const byte VirtualKey_U = 0x55;

#if defined(SDL_PLATFORM_IOS) || defined(__IPHONEOS__)
static void CopyFileIfMissing(const char* source, const char* destination) {
  FILE* existing = fopen(destination, "rb");
  if (existing != nullptr) {
    fclose(existing);
    return;
  }
  FILE* in = fopen(source, "rb");
  if (in == nullptr) {
    return;
  }
  FILE* out = fopen(destination, "wb");
  if (out == nullptr) {
    fclose(in);
    return;
  }
  char buffer[8192];
  size_t bytesRead;
  while ((bytesRead = fread(buffer, 1, sizeof(buffer), in)) > 0) {
    fwrite(buffer, 1, bytesRead, out);
  }
  fclose(in);
  fclose(out);
}

void InitPakPaths() {
  const char* base = SDL_GetBasePath();
  if (!base) {
    fprintf(stderr, "SDL_GetBasePath failed: %s\n", SDL_GetError());
    return;
  }
  std::snprintf(s_music_pak,  sizeof(s_music_pak),  "%smusic.pak",  base);
  std::snprintf(s_hazard_pak, sizeof(s_hazard_pak), "%shazard.pak", base);
  std::snprintf(s_visual_pak, sizeof(s_visual_pak), "%svisual.pak", base);

  std::snprintf(s_hpatch_001, sizeof(s_hpatch_001), "%shpatch.001", base);
  std::snprintf(s_hpatch_002, sizeof(s_hpatch_002), "%shpatch.002", base);

  char* pref = SDL_GetPrefPath("yourorg", "hazardrevenge");
  if (pref != nullptr) {
    std::snprintf(s_hazard_sav, sizeof(s_hazard_sav),
                  "%shazard.sav", pref);
    std::string bundledSave = std::string(base) + "hazard.sav";
    CopyFileIfMissing(bundledSave.c_str(), s_hazard_sav);
    SDL_free(pref);
  }
  else {
    std::snprintf(s_hazard_sav, sizeof(s_hazard_sav),
                  "%shazard.sav", base);
  }
}
#endif

UINT MainFunction(HINSTANCE param_1) {

  ATOM registerClassResult;
  HWND hWndParent;
  HMENU hMenu;
  LPVOID lpParam;
  WNDCLASSA windowClass;
  tagMSG tagMsg;
  int32_t nWidth;
  int32_t nHeight;

  GameFullscreenWindow = FindWindowA(s_PumpkinSoft, nullptr);
  if (GameFullscreenWindow != (HWND) nullptr) {
    SetForegroundWindow(GameFullscreenWindow);
    return 0;
  }
  windowClass.style = 0;
  windowClass.lpfnWndProc = GameLoopCallback;
  windowClass.cbClsExtra = 0;
  windowClass.cbWndExtra = 0;
  windowClass.hInstance = param_1;
  windowClass.hIcon = LoadIconA(param_1, (LPCSTR)0x29a);
  windowClass.hCursor = (HCURSOR) nullptr;
  windowClass.hbrBackground = (HBRUSH)GetStockObject(4);
  windowClass.lpszMenuName = (LPCSTR) nullptr;
  windowClass.lpszClassName = s_PumpkinSoft;
  registerClassResult = RegisterClassA(&windowClass);
  if (registerClassResult == 0) {
    PostQuitMessage(0);
  }
#if PATCH_SKIP_CD_CHECK == 0
  SHORT asyncKeyState;
  LPSTR commandLine;
  char* filenameCopyFrom;
  UINT driveTypeAddress;
  int32_t driveAsInteger;
  FILE* cdFile;
  char* localUint;
  char filenameToBeLoaded[256];
  char currentDirectory[256];

  cdFile = nullptr;
  localUint = (char*)s_c__;

  commandLine = GetCommandLineA();
  strcpy(currentDirectory, commandLine);

  int i = 0;
  while (currentDirectory[i+1] != '"' && currentDirectory[i+1] != '\0')
    i++;
  currentDirectory[i+1] = '\0';

  filenameCopyFrom = strrchr(currentDirectory, '\\');
  strcpy(filenameCopyFrom, (char*)&lpCaption);

  SetCurrentDirectoryA(currentDirectory + 1);
  strcpy(filenameToBeLoaded, s_c___hazard_pa_);

  do {
    while (true) {
      asyncKeyState = GetAsyncKeyState(VirtualKey_F);
      if ((((asyncKeyState != 0) && (asyncKeyState = GetAsyncKeyState(VirtualKey_U), asyncKeyState != 0)) && (asyncKeyState = GetAsyncKeyState(VirtualKey_C), asyncKeyState != 0)) && (asyncKeyState = GetAsyncKeyState(VirtualKey_K), asyncKeyState != 0)) {
        goto label_process_pak_files;
      }
      for (driveAsInteger = 'C'; driveAsInteger <= 'Z'; driveAsInteger = driveAsInteger + 1) {
        if (cdFile != (FILE*)0x0) {
          goto label_close_cd_file;
        }
        filenameToBeLoaded[0] = (CHAR)driveAsInteger;
        localUint[0] = filenameToBeLoaded[0];
        driveTypeAddress = GetDriveTypeA((LPCSTR)&localUint);
        if (driveTypeAddress == 5) {
          cdFile = fopen(&filenameToBeLoaded[0], s_rb);
        }
      }
      if (cdFile != (FILE*)0x0) {
        break;
      }
      int32_t messageBoxValue = MessageBoxA(GameFullscreenWindow, s__Please_Insert_a_Hazard_CD_Disk, (LPCSTR)&lpCaption, 1);
      if (messageBoxValue == 2) {
        return 0;
      }
    }
  label_close_cd_file:
    fclose(cdFile);
  } while (cdFile == (FILE*)0x0);

label_process_pak_files:
  ProcessPakFile(filenameToBeLoaded + 3);
  strcpy(filenameToBeLoaded + 3, s__visual_pa_);
  ProcessPakFile(filenameToBeLoaded);
#endif


#if defined(SDL_PLATFORM_IOS) || defined(__IPHONEOS__)
  lpParam = (LPVOID) nullptr;
  hMenu = (HMENU) nullptr;
  hWndParent = (HWND) nullptr;

  nHeight = GetSystemMetrics(1);
  nWidth = GetSystemMetrics(0);
  GameFullscreenWindow = CreateWindowExA(0, s_PumpkinSoft, s__HAZARD__Pumpkin_Soft, 0x80880000, 0, 0, nWidth, nHeight, hWndParent, hMenu, param_1, lpParam);

  InitPakPaths();

  char* pref = SDL_GetPrefPath("yourorg", "hazardrevenge");
  if (pref) {
    std::string logPath = std::string(pref) + "debug.log";
    freopen(logPath.c_str(), "w", stderr);
    freopen(logPath.c_str(), "w", stdout);
    SDL_free(pref);
  }
  ProcessPakFile(s_visual_pak);
  ProcessPakFile(s_hazard_pak);
  ProcessPakFile(s_music_pak);
  ProcessPakFile(s_hpatch_001);
  ProcessPakFile(s_hpatch_002);
#else
  ProcessPakFile(s_visual_pak);
  ProcessPakFile(s_hazard_pak);
  ProcessPakFile(s_music_pak);
  ProcessPakFile(s_hpatch_001);
  ProcessPakFile(s_hpatch_002);
  lpParam = (LPVOID) nullptr;
  hMenu = (HMENU) nullptr;
  hWndParent = (HWND) nullptr;

  nHeight = GetSystemMetrics(1);
  nWidth = GetSystemMetrics(0);
  GameFullscreenWindow = CreateWindowExA(0, s_PumpkinSoft, s__HAZARD__Pumpkin_Soft, 0x80880000, 0, 0, nWidth, nHeight, hWndParent, hMenu, param_1, lpParam);
#endif
  ValidateDirectXInstallation();
  InitializeSfxObject();
  InitializeMusicObject();
  FlagRelatedToLoadingSfx = 1;
  GameStateFlag = 0;

  while (FlagGameIsRunning != 0) {
    if (PeekMessageA(&tagMsg, (HWND) nullptr, 0, 0, 1)) {
      if (tagMsg.message == WM_QUIT) {
        FlagGameIsRunning = 0;
      }
      else {
        TranslateMessage(&tagMsg);
        DispatchMessageA(&tagMsg);
      }
    }
    else {
      if (FlagRelatedToLoadingSfx != 0) {
        CoreGameLoop();
      }
    }
  }
  ShutDownMusicObject();
  ShutDownSfxObject();
  ReleaseDirectDraw();
  CloseWindow(GameFullscreenWindow);
  return tagMsg.wParam;
}
