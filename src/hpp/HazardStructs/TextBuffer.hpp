#ifndef HAZARD_TEXTBUFFER_HPP
#define HAZARD_TEXTBUFFER_HPP
#include "HazardTypedef.hpp"

struct TextBuffer {
  int16_t textWideBytes[47025];
};
typedef struct TextBuffer TextBuffer, *PTextBuffer;

#endif
