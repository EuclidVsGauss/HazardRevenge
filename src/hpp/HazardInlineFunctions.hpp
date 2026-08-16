#ifndef HAZARD_COMMONFUNCTIONS_HPP
#define HAZARD_COMMONFUNCTIONS_HPP

#include "HazardClasses/GridHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardTypedef.hpp"

__forceinline int32_t __InlineGetSoundEffectIndex(CoreActClass* actObject, int32_t sfxIndex) {
  int32_t index = actObject->GetActionIndexByName(s__sfx);
  if (index == -1) {
    return 0x0;
  }
  return actObject->txtContent[index].ptrFrameStart[sfxIndex];
}

__forceinline int32_t __InlineGetSoundEffectIndex(CoreActClass* actObject) {
  return __InlineGetSoundEffectIndex(actObject, 0);
}

__forceinline int32_t __InlineHasUnoccupiedTileExcludingTypeInRectangularRegion(GridHandler* gridHandler, int32_t startCol, int32_t startRow, int32_t width, int32_t height, int32_t excludeValue) {
  for (int32_t rowOffset = 0; rowOffset < height; rowOffset++) {
    for (int32_t colOffset = 0; colOffset < width; colOffset++) {
      int32_t tileValue = gridHandler->PaddedGridMap_Collision[startRow + rowOffset][startCol + colOffset];
      if (tileValue >= 0 && tileValue != excludeValue) {
        return tileValue;
      }
    }
  }
  return -1;
}

__forceinline int32_t __InlineGetActiveCharacterIndex(GameWindowBase* sceneClassUser) {
  int32_t index;
  for (index = 0; TeamCharacterList[index] != nullptr; index++) {
    if (TeamCharacterList[index]->shiftedSceneClassUser0x48 == sceneClassUser) {
      break;
    }
  }
  return index;
}

__forceinline int32_t __InlineCursorInsideBox(int32_t lowerX, int32_t lowerY, int32_t upperX, int32_t upperY) {
  return (
             ((lowerX < CursorXCoord) &&
              (CursorXCoord < upperX)) &&
             (lowerY < CursorYCoord)) &&
         (CursorYCoord < upperY);
}

__forceinline void __InlineCopyString(char* dest, const char* src) {
  int32_t len = strlen(src) + 1;
  memcpy(dest, src, len);
}

__forceinline int32_t __InlineMinimum(int32_t a, int32_t b) {
  return (a < b) ? a : b;
}

__forceinline int32_t __InlineMaximum(int32_t a, int32_t b) {
  return (a < b) ? b : a;
}

__forceinline int __InlineStringCompare(const char* str1, const char* str2) {
  const char* s1 = str1;
  const char* s2 = str2;

  while (true) {
    char ch1 = *s1;
    char ch2 = *s2;

    if (ch1 != ch2) {

      return 1;
    }

    if (ch1 == '\0') {

      return 0;
    }

    ch1 = s1[1];
    ch2 = s2[1];

    if (ch1 != ch2) {
      return 1;
    }

    s1 += 2;
    s2 += 2;

    if (ch1 == '\0') {
      return 0;
    }
  }
}

#endif
