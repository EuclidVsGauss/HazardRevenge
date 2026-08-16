#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"

#pragma optimize("s", on)

void ReadInterpolatableString(UnpackedFileBase* param_1, char* formatString, ...) {

  char currentChar;
  int32_t* outputPtr;
  int32_t formatLen;
  int32_t readToken;
  int32_t parsedValue;
  float fFloatValue;
  int32_t formatIndex;
  char tokenBuffer[16];
  char* formatWalker;
  bool lookedAhead;
  va_list args;
  float* floatPtr;

  va_start(args, formatString);

  formatLen = -1;
  readToken = -1;
  formatWalker = formatString;
  do {
    if (formatLen == 0) {
      break;
    }
    formatLen = formatLen - 1;
    currentChar = *formatWalker;
    formatWalker = formatWalker + 1;
  } while (currentChar != '\0');
  formatIndex = 0;
  if ((int32_t)(~formatLen - 1U) < 1) {
    va_end(args);
    return;
  }

label_process_format_specifier:
  if (formatString[formatIndex] == '%') {
    if (readToken == -1) {
      readToken = param_1->readByte();
    }
    while ((((readToken == L'\n' || (readToken == L'\t')) || (readToken == L'\r')) || (readToken == L' '))) {
      readToken = param_1->readByte();
    }
    switch (formatString[formatIndex + 1]) {
    case 'D':
    case 'U':
    case 'd':
    case 'u':
      parsedValue = 0;
      while (((47 < readToken && (readToken < 58)) || (parsedValue == 0 && (readToken == 45)))) {
        tokenBuffer[parsedValue] = (char)readToken;
        readToken = param_1->readByte();
        parsedValue = parsedValue + 1;
      }

      outputPtr = va_arg(args, int32_t*);
      tokenBuffer[parsedValue] = '\0';
      parsedValue = atoi(tokenBuffer);
      *outputPtr = parsedValue;
      break;
    case 'F':
    case 'G':
    case 'f':
    case 'g':
      parsedValue = 0;
      lookedAhead = false;

      do {
        if (((readToken < 48) || (57 < readToken)) && (parsedValue != 0 || (readToken != '-'))) {
          if (lookedAhead || (readToken != '.')) {
            goto label_store_parsed_float;
          }
        label_found_decimal_point:
          lookedAhead = true;
        }
        else if (readToken == '.') {
          goto label_found_decimal_point;
        }
        tokenBuffer[parsedValue] = (char)readToken;
        readToken = param_1->readByte();
        parsedValue = parsedValue + 1;

      } while (true);
    case 'S':
    case 's':

      outputPtr = (int32_t*)va_arg(args, char*);
      parsedValue = 0;
      while ((((readToken != 10 && (readToken != 9)) && (readToken != 13)) && (readToken != ' ' && (readToken != -1)))) {
        *(char*)((intptr_t)outputPtr + parsedValue) = (char)readToken;
        readToken = param_1->readByte();
        parsedValue = parsedValue + 1;
      }
      *(byte*)((intptr_t)outputPtr + parsedValue) = 0;
      break;
    case 'X':
    case 'x':
      lookedAhead = false;
      parsedValue = 0;
      while (true) {
        while ((((47 < readToken && (readToken < 58)) || (96 < readToken && (readToken < 103))) || (64 < readToken && (readToken < 71)))) {
          if (readToken == '-') {
            lookedAhead = true;
            readToken = param_1->readByte();
          }
          else {
            if (96 < readToken) {
              readToken = readToken - 32;
            }
            if (readToken < 58) {
              parsedValue = (parsedValue * 16) + (readToken - 48U);
              readToken = param_1->readByte();
            }
            else {
              parsedValue = (parsedValue * 16) + (readToken - 55U);
              readToken = param_1->readByte();
            }
          }
        }
        if (lookedAhead) {
          break;
        }
        if (readToken != 45) {
          goto label_store_parsed_hex;
        }
        lookedAhead = true;
        readToken = param_1->readByte();
      }
      parsedValue = -parsedValue;
    label_store_parsed_hex:

      outputPtr = va_arg(args, int32_t*);
      *outputPtr = parsedValue;
    }
  }
  goto label_advance_format_index;
label_store_parsed_float:
  tokenBuffer[parsedValue] = '\0';
  fFloatValue = atof(tokenBuffer);

  floatPtr = va_arg(args, float*);
  *floatPtr = fFloatValue;
label_advance_format_index:
  formatIndex = formatIndex + 1;
  if ((int32_t)(~formatLen - 1U) <= formatIndex) {
    va_end(args);
    if (readToken == -1) {
      return;
    }
    if (readToken == 13) {
      return;
    }
    param_1->setFilePointer(-1, 1);
    return;
  }
  goto label_process_format_specifier;
}

#pragma optimize("s", off)
