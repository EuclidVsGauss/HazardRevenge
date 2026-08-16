#ifndef HAZARD_FUNCTIONS_HPP
#define HAZARD_FUNCTIONS_HPP

#include <windows.h>
#include <dsound.h>
#include "HazardStructs/ImageVectorWithHeader.hpp"
#include "HazardTypedef.hpp"

class UnpackedFileBase;
struct ImageVectorWithHeader;

ImageVectorWithHeader* __fastcall DecodeShadowSprite(byte* imageVector, int32_t width, int32_t height, int32_t null1, int32_t null2, int32_t centerX, int32_t centerY);
ImageVectorWithHeader* __fastcall DecodeSolidSprite(byte* startOfImage, int32_t length1, int32_t length2, int32_t null, int16_t* shortColorMapAddress, int32_t halfLength1, int32_t halfLength2);

__declspec(nothrow) int32_t __cdecl GetCurentFilePointerLocation(uint32_t param_1);
__declspec(nothrow) int32_t __cdecl ReadFileWithTranslation(uint32_t param_1, byte* buffer, int32_t nBytesToRead);
__declspec(nothrow) int32_t __cdecl SetFilePointer(uint32_t fileHandleId, LONG distanceToMove, DWORD moveMethod);
__declspec(nothrow) int32_t PseudoRng();

HANDLE __cdecl GetIndexedFileHandle(uint32_t param_1);
int16_t* __fastcall Create16BitImageFromPalette(byte* startingAddress, int32_t length1, int32_t length2, int16_t* colorMap);
int32_t __cdecl SetFileTextModeFlag(uint32_t param_1, int32_t param_2);
int32_t __cdecl CloseAndResetStdHandle(uint32_t flagStdHandle);
int32_t __cdecl ReadFileFixedSize(char* filename, uint32_t size, uint32_t zero);
int32_t __cdecl OpenFileWithFlags(char* filename, uint32_t largeSize, uint32_t size64, uint32_t zero);
int32_t __cdecl SetFilePointerAndPadZeros(uint32_t param_1, int32_t param_2);
int32_t __cdecl SetStdHandle_(uint32_t param_1, HANDLE param_2);
int32_t __cdecl WrapperCloseFileHandle(uint32_t handleIndex);
int32_t __cdecl WriteFileWithTranslation(DWORD param_1, char* saveBuffer, uint32_t nBytesToWrite);
int32_t __fastcall Maximum(int32_t param_1, int32_t param_2);
int32_t __fastcall Minimum(int32_t param_1, int32_t param_2);
int32_t __fastcall GetTickCountsAndAsyncStates(int32_t* cursorX, int32_t* cursorY, int32_t* mouseInput);
int32_t TalkboxTextFontRelated(char* screenPixels, int32_t referenceHeight, char* stringText, int32_t lengthString);
int32_t AllocateFileHandleSlot();
LPDIRECTSOUNDBUFFER __fastcall RunMenuSound(char* soundName, int32_t samplingRate);
LRESULT CALLBACK GameLoopCallback(HWND param_1, UINT param_2, WPARAM param_3, LPARAM param_4);
UINT MainFunction(HINSTANCE param_1);
int32_t __cdecl IsGreaterThanFloat(double* param_1);
void __cdecl ReadInterpolatableString(UnpackedFileBase* param_1, char* interpolatableString, ...);
void __cdecl MapErrorCode(uint32_t lastError);
void __cdecl SetRngSeed(int32_t param_1);
void __fastcall PixelCalculations_DirectDrawSurface(int32_t largeInteger, int32_t smallInteger);
void __fastcall SaveScreenshot(char* param_1);
void __fastcall WrapperMessageBoxA(LPCSTR text, LPCSTR caption);
void __fastcall ProcessPakFile(char* pakFilename);

void CoreGameLoop();
void ExitGame();
void InitializeMusicObject();
void InitializeSfxObject();
void LoadItemTxtAndAct();
void ReleaseDirectDraw();
void ResetRngAndAsyncKeys();
void SetSaveFileHandleComponent();
void ShutDownMusicObject();
void ShutDownSfxObject();
void ValidateDirectXInstallation();

#endif
