#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardGlobals.hpp"

void ValidateDirectXInstallation(void) {
  int32_t directDrawResult;
  HRESULT hr;
  byte redStart;
  byte greenStart;
  byte blueStart;
  byte tempByte;

  DDSURFACEDESC surfaceDescriptor;
  uint32_t bitTest;

  directDrawResult = DirectDrawCreate(nullptr, &DirectDrawObject, nullptr);
  if (directDrawResult != 0) {
    WrapperMessageBoxA(s_Direct_X_isn_t_installed, s_Time_to_Stop);
    PostQuitMessage(1);
    return;
  }
  DirectDrawObject->SetCooperativeLevel(GameFullscreenWindow, 0x13);
  hr = DirectDrawObject->SetDisplayMode(640, 480, 16);
  if (hr != 0) {
    WrapperMessageBoxA(s_Your_direct_draw_device_doesn_t_i, s_Time_to_Stop);
    PostQuitMessage(1);
    return;
  }

  memset(&surfaceDescriptor, 0, sizeof(DDSURFACEDESC));

  surfaceDescriptor.dwSize = 108;
  surfaceDescriptor.dwFlags = 33;
  surfaceDescriptor.ddsCaps.dwCaps = 536;
  surfaceDescriptor.dwBackBufferCount = 1;
  hr = DirectDrawObject->CreateSurface(&surfaceDescriptor, &DirectDrawSurface, nullptr);
  if (hr != 0) {
    MessageBoxA(GameFullscreenWindow, s_Your_DirectDraw_Device_doesn_t_c, s_Time_to_error, 0);
    PostQuitMessage(1);
    return;
  }
  surfaceDescriptor.dwSize = 108;
  surfaceDescriptor.dwFlags = 0x1000;
  hr = DirectDrawSurface->GetSurfaceDesc(&surfaceDescriptor);
  if (hr != 0) {
    MessageBoxA(GameFullscreenWindow, s_Fail_to_get_pixel_format, s_Time_to_error, 0);
    PostQuitMessage(0);
    return;
  }
  RedOffset1 = 0;
  bitTest = surfaceDescriptor.ddpfPixelFormat.dwRBitMask & 1;
  while (bitTest == 0) {
    RedOffset1 = RedOffset1 + 1;
    bitTest = surfaceDescriptor.ddpfPixelFormat.dwRBitMask & 1 << ((byte)RedOffset1 & 0x1f);
  }
  RedOffset2 = 0;
  redStart = (byte)RedOffset1;
  tempByte = redStart;
  while ((surfaceDescriptor.ddpfPixelFormat.dwRBitMask & 1 << (tempByte & 0x1f)) != 0) {
    RedOffset2 = RedOffset2 + 1;
    tempByte = (char)RedOffset2 + redStart;
  }
  GreenOffset1 = 0;
  bitTest = surfaceDescriptor.ddpfPixelFormat.dwGBitMask & 1;
  while (bitTest == 0) {
    GreenOffset1 = GreenOffset1 + 1;
    bitTest = surfaceDescriptor.ddpfPixelFormat.dwGBitMask & 1 << ((byte)GreenOffset1 & 0x1f);
  }
  GreenOffset2 = 0;
  greenStart = (byte)GreenOffset1;
  tempByte = greenStart;
  while ((surfaceDescriptor.ddpfPixelFormat.dwGBitMask & 1 << (tempByte & 0x1f)) != 0) {
    GreenOffset2 = GreenOffset2 + 1;
    tempByte = greenStart + (char)GreenOffset2;
  }
  BlueOffset1 = 0;
  bitTest = surfaceDescriptor.ddpfPixelFormat.dwBBitMask & 1;
  while (bitTest == 0) {
    BlueOffset1 = BlueOffset1 + 1;
    bitTest = surfaceDescriptor.ddpfPixelFormat.dwBBitMask & 1 << ((byte)BlueOffset1 & 0x1f);
  }
  BlueOffset2 = 0;
  blueStart = (byte)BlueOffset1;
  tempByte = blueStart;
  while ((surfaceDescriptor.ddpfPixelFormat.dwBBitMask & 1 << (tempByte & 0x1f)) != 0) {
    BlueOffset2 = BlueOffset2 + 1;
    tempByte = (char)BlueOffset2 + blueStart;
  }
  InvBlueOffset = 8 - BlueOffset2;
  InvRedOffset = 8 - RedOffset2;
  InvGreenOffset = 8 - GreenOffset2;
  RgbMask = (uint16_t)(((0xff >> ((byte)InvBlueOffset & 0x1f)) + -1) << (blueStart & 0x1f)) |
                     (uint16_t)(((0xff >> ((byte)InvGreenOffset & 0x1f)) + -1) << (greenStart & 0x1f)) |
                     (uint16_t)(((0xff >> ((byte)InvRedOffset & 0x1f)) + -1) << (redStart & 0x1f));
  SetCursor((HCURSOR) nullptr);
}
