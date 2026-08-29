#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardGlobals.hpp"

#pragma optimize("s", on)

void ReadInterpolatableString(UnpackedFileBase* param_1, char* formatString, ...) {
  int32_t* outputPtr;
  int32_t formatLen;
  int32_t readToken;
  int32_t counter;
  float fFloatValue;
  int32_t formatIndex;
  char tokenBuffer[16];
  bool lookedAhead;
  va_list args;
  float* floatPtr;

  va_start(args, formatString);

  formatLen = (int32_t)strlen(formatString);
  if (formatLen <= 0) {
    va_end(args);
    return;
  }

  readToken = -1;
  formatIndex = 0;

  while (formatIndex < formatLen) {
    if (formatString[formatIndex] == '%') {
      if (readToken == -1) {
        readToken = param_1->readByte();
      }
      while (readToken == '\n' || readToken == '\t' ||
             readToken == '\r' || readToken == ' ') {
        readToken = param_1->readByte();
      }

      switch (formatString[formatIndex + 1]) {
      case 'D':
      case 'U':
      case 'd':
      case 'u': {
        counter = 0;
        while ((readToken > '0' - 1 && readToken < '9' + 1) ||
               (counter == 0 && readToken == '-')) {
          tokenBuffer[counter] = (char)readToken;
          readToken = param_1->readByte();
          counter++;
        }
        outputPtr = va_arg(args, int32_t*);
        tokenBuffer[counter] = '\0';
        *outputPtr = atoi(tokenBuffer);
        formatIndex++;
        break;
      }

      case 'F':
      case 'G':
      case 'f':
      case 'g': {
        counter = 0;
        lookedAhead = false;
        for (;;) {
          if ((readToken >= '0' && readToken <= '9') ||
              (counter == 0 && readToken == '-')) {
          }
          else if (!lookedAhead && readToken == '.') {
            lookedAhead = true;
          }
          else {
            break;
          }
          tokenBuffer[counter] = (char)readToken;
          readToken = param_1->readByte();
          counter++;
        }
        tokenBuffer[counter] = '\0';
        fFloatValue = (float)atof(tokenBuffer);
        floatPtr = va_arg(args, float*);
        *floatPtr = fFloatValue;
        formatIndex++;
        break;
      }

      case 'S':
      case 's': {
        char* dst = va_arg(args, char*);
        counter = 0;
        while (readToken != '\n') {
          if (readToken == '\t' || readToken == '\r' ||
              readToken == ' ' || readToken == -1) {
            break;
          }
          dst[counter++] = (char)readToken;
          readToken = param_1->readByte();
        }
        dst[counter] = 0;
        formatIndex++;
        break;
      }

      case 'X':
      case 'x': {
        lookedAhead = false;
        counter = 0;
        for (;;) {
          if (readToken >= '0' && readToken <= '9') {
            counter = (counter * 16) + (readToken - '0');
            readToken = param_1->readByte();
          }
          else if (readToken >= 'a' && readToken <= 'f') {
            counter = (counter * 16) + (readToken - 'a' + 10);
            readToken = param_1->readByte();
          }
          else if (readToken >= 'A' && readToken <= 'F') {
            counter = (counter * 16) + (readToken - 'A' + 10);
            readToken = param_1->readByte();
          }
          else if (!lookedAhead && readToken == '-') {
            lookedAhead = true;
            readToken = param_1->readByte();
          }
          else {
            break;
          }
        }
        if (lookedAhead) {
          counter = -counter;
        }
        outputPtr = va_arg(args, int32_t*);
        *outputPtr = counter;
        formatIndex++;
        break;
      }

      default:
        break;
      }
    }

    formatIndex++;
  }

  va_end(args);

  if (readToken != -1 && readToken != 13) {
    param_1->setFilePointer(-1, 1);
  }
}

#pragma optimize("s", off)
