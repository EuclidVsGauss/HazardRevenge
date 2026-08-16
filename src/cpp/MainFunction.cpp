#include <HazardPatches.hpp>
#include <windows.h>
#include <stdio.h>
#include "HazardGlobals.hpp"

const byte VirtualKey_C = 0x43;
const byte VirtualKey_F = 0x46;
const byte VirtualKey_K = 0x4B;
const byte VirtualKey_U = 0x55;


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
  int32_t integer;
  int32_t driveAsInteger;
  FILE* cdFile;
  char* localUint;
  char filenameToBeLoaded[256];
  char currentDirectory[256];

  cdFile = nullptr;
  localUint = (char*)s_c__;

  commandLine = GetCommandLineA();
  strcpy(currentDirectory, commandLine);

  driveAsInteger = 1;
  while ((currentDirectory[1] != '\"' && (currentDirectory[1] != '\0'))) {
    integer = driveAsInteger + 1;
    driveAsInteger = driveAsInteger + 1;
    currentDirectory[1] = currentDirectory[integer];
  }
  currentDirectory[driveAsInteger] = '\0';

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
      driveAsInteger = 0x43;
      do {
        if (cdFile != (FILE*)0x0) {
          goto label_close_cd_file;
        }
        filenameToBeLoaded[0] = (CHAR)driveAsInteger;
        localUint[0] = filenameToBeLoaded[0];
        driveTypeAddress = GetDriveTypeA((LPCSTR)&localUint);
        if (driveTypeAddress == 5) {
          cdFile = fopen(&filenameToBeLoaded[0], s_rb);
        }
        driveAsInteger = driveAsInteger + 1;
      } while (driveAsInteger < 0x5b);
      if (cdFile != (FILE*)0x0) {
        break;
      }
      driveAsInteger = MessageBoxA(GameFullscreenWindow, s__Please_Insert_a_Hazard_CD_Disk, (LPCSTR)&lpCaption, 1);
      if (driveAsInteger == 2) {
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
