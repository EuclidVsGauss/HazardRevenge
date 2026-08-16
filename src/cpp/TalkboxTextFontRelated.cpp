#include "HazardPatches.hpp"
#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardGlobals.hpp"

#if PATCH_USE_KOREAN_FONT
static uint32_t glyph_composition_buffer[8] = {0};

/* Initial consonants (Choseong) */
static const uint8_t initial_consonants[32] = {
    0x00, 0x00, 0x01, 0x02,
    0x03, 0x04, 0x05, 0x06,
    0x07, 0x08, 0x09, 0x0a,
    0x0b, 0x0c, 0x0d, 0x0e,
    0x0f, 0x10, 0x00, 0x11,
    0x12, 0x13, 0x14, 0x15,
    0x16, 0x17, 0x18, 0x19,
    0x1a, 0x1b, 0x00, 0x00};

/* Medial vowels (Jungseong) */
static const uint8_t medial_vowels[24] = {
    0x00, 0x00, 0x01, 0x02,
    0x03, 0x04, 0x05, 0x06,
    0x07, 0x08, 0x09, 0x0a,
    0x0b, 0x0c, 0x0d, 0x0e,
    0x0f, 0x10, 0x11, 0x12,
    0x13, 0x00, 0x00, 0x00};

static const uint8_t final_consonants[32] = {
    0x00, 0x00, 0x00, 0x01,
    0x02, 0x03, 0x04, 0x05,
    0x00, 0x00, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x00, 0x00, 0x0c, 0x0d,
    0x0e, 0x0f, 0x10, 0x11,
    0x00, 0x00, 0x12, 0x13,
    0x14, 0x15, 0x00, 0x00};

/* Offset table for vowels (no initial consonant) */
static const uint8_t medial_offsets_no_initial[44] = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00,
    0x03, 0x00, 0x03, 0x00,
    0x03, 0x00, 0x01, 0x00,
    0x02, 0x00, 0x04, 0x00,
    0x04, 0x00, 0x04, 0x00,
    0x02, 0x00, 0x01, 0x00,
    0x03, 0x00, 0x00, 0x00};

/* Offset table for vowels (with initial consonant) */
static const uint8_t medial_offsets_with_initial[44] = {
    0x00, 0x00, 0x05, 0x00,
    0x05, 0x00, 0x05, 0x00,
    0x05, 0x00, 0x05, 0x00,
    0x05, 0x00, 0x05, 0x00,
    0x05, 0x00, 0x06, 0x00,
    0x07, 0x00, 0x07, 0x00,
    0x07, 0x00, 0x06, 0x00,
    0x06, 0x00, 0x07, 0x00,
    0x07, 0x00, 0x07, 0x00,
    0x06, 0x00, 0x06, 0x00,
    0x07, 0x00, 0x05, 0x00};

/*  Offset table for initial consonants */
static const uint8_t initial_offsets[112] = {
    0x00, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x01, 0x00,
    0x02, 0x00, 0x01, 0x00,
    0x02, 0x00, 0x03, 0x00,
    0x00, 0x00, 0x02, 0x00,
    0x01, 0x00, 0x03, 0x00,
    0x03, 0x00, 0x01, 0x00,
    0x02, 0x00, 0x01, 0x00,
    0x03, 0x00, 0x03, 0x00,
    0x01, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x77, 0x01, 0x00, 0x00,
    0xd1, 0x00, 0x00, 0x00,
    0xa0, 0x01, 0x00, 0x00,
    0xe0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x74, 0x01, 0x00, 0x00,
    0xe4, 0x00, 0x00, 0x00,
    0xa3, 0x01, 0x00, 0x00,
    0xf5, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00,
    0x66, 0x01, 0x00, 0x00,
    0xfa, 0x00, 0x00, 0x00,
    0xb2, 0x01, 0x00, 0x00,
    0x0a, 0x01, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00};

static void blend_glyph(uint32_t* dest, const uint32_t* src, int32_t byte_size) {
  int32_t count = (byte_size + 3) >> 2;
  for (int32_t i = 0; i < count; i++) {
    dest[i] |= src[i];
  }
}

uint32_t* compose_hangul_from_euckr(uint16_t char_code) {

  uint8_t initial = initial_consonants[char_code & 0x1f];
  uint8_t medial = medial_vowels[(char_code >> 10) & 0x1f];
  uint8_t final = final_consonants[(char_code >> 5) & 0x1f];

  uint32_t* font_base = (uint32_t*)FontPixelMap;
  uint32_t* composition_ptr;

  if (initial != 0) {

    int32_t final_offset = (int32_t) final;

    uint16_t medial_offset = medial_offsets_with_initial[final_offset * 2];

    uint32_t* base_ptr = (uint32_t*)((uintptr_t)font_base +
                                     ((medial + medial_offset * 0x14) * 0x20));

    composition_ptr = glyph_composition_buffer;
    for (int32_t i = 0; i < 8; i++) {
      *composition_ptr = *base_ptr;
      base_ptr++;
      composition_ptr++;
    }

    int32_t final_glyph_offset;
    if (medial == 1 || medial == 24) {
      final_glyph_offset = final_offset + 0xcc;
    }
    else {
      final_glyph_offset = final_offset + 0xe2;
    }

    uint32_t* final_ptr = (uint32_t*)((uintptr_t)font_base + (final_glyph_offset * 0x20));
    blend_glyph(glyph_composition_buffer, final_ptr, 0x20);

    uint16_t initial_offset = initial_offsets[final_offset * 2];

    uint32_t* initial_ptr = (uint32_t*)((uintptr_t)font_base +
                                        ((initial + 0xf8 + initial_offset * 0x1c) * 0x20));

    blend_glyph(glyph_composition_buffer, initial_ptr, 0x20);

    return glyph_composition_buffer;
  }

  else {

    int32_t final_offset = (int32_t) final;

    uint16_t medial_offset = medial_offsets_no_initial[final_offset * 2];

    uint32_t* base_ptr = (uint32_t*)((uintptr_t)font_base +
                                     ((medial + medial_offset * 0x14) * 0x20));

    composition_ptr = glyph_composition_buffer;
    for (int32_t i = 0; i < 8; i++) {
      *composition_ptr = *base_ptr;
      base_ptr++;
      composition_ptr++;
    }

    int32_t final_glyph_offset;
    if (medial != 1 && medial != 24) {
      final_glyph_offset = final_offset + 0xb6;
    }
    else {
      final_glyph_offset = final_offset + 0xa0;
    }

    uint32_t* final_ptr = (uint32_t*)((uintptr_t)font_base + (final_glyph_offset * 0x20));
    blend_glyph(glyph_composition_buffer, final_ptr, 0x20);

    return glyph_composition_buffer;
  }
}

int32_t TalkboxTextFontRelated(char* screenPixels, int32_t screenStride, char* stringText, int32_t textLength) {
  uint8_t currentChar;
  uint8_t bitMask;
  int32_t bitIndex;
  uint8_t* pixelPtr;
  uint8_t* linePtr;
  uint16_t* fontDataPtr;
  uint16_t glyphRowData;
  int32_t cursorX = 0;
  int32_t stringIndex = 0;
  int32_t totalLines = 1;
  int32_t remainingRows;

  while (stringIndex < textLength) {
    currentChar = stringText[stringIndex];

    if ((currentChar & 0x80) != 0) {

      uint16_t charCode = ((uint16_t)(uint8_t)currentChar << 8) | (uint8_t)stringText[stringIndex + 1];

      fontDataPtr = (uint16_t*)compose_hangul_from_euckr(charCode);

      pixelPtr = (uint8_t*)((intptr_t)screenPixels + cursorX);
      remainingRows = 16;

      do {

        glyphRowData = *fontDataPtr;
        fontDataPtr++;

        bitIndex = 7;
        linePtr = pixelPtr;
        do {
          bitMask = (uint8_t)bitIndex;
          bitIndex--;

          *linePtr = ((1 << (bitMask & 0xf)) & glyphRowData) ? 31 : 0;
          linePtr++;
        } while (bitIndex >= -8);

        pixelPtr += screenStride;
        remainingRows--;
      } while (remainingRows != 0);

      cursorX += 16;
      stringIndex += 2;
    }
    else {

      if (currentChar == '|') {

        screenPixels += (screenStride * 16);
        cursorX = 0;
        stringIndex++;
        totalLines++;
      }
      else {
        fontDataPtr = (uint16_t*)((uintptr_t)FontPixelMap +
                                  (currentChar + 0x168) * 32);

        pixelPtr = (uint8_t*)((intptr_t)screenPixels + cursorX);
        remainingRows = 16;

        do {
          glyphRowData = *fontDataPtr;
          fontDataPtr++;

          bitIndex = 7;
          linePtr = pixelPtr;
          do {
            bitMask = (uint8_t)bitIndex;
            bitIndex--;

            *linePtr = ((1 << (bitMask & 0xf)) & glyphRowData) ? 31 : 0;
            linePtr++;
          } while (bitIndex >= -4);

          pixelPtr += screenStride;
          remainingRows--;
        } while (remainingRows != 0);

        cursorX += 12;
        stringIndex++;
      }
    }
  }

  return totalLines;
}

#else
int32_t TalkboxTextFontRelated(char* screenPixels, int32_t screenStride, char* stringText, int32_t textLength) {
  byte bitMask;
  uint32_t bitIndex;
  byte* pixelPtr;
  byte* linePtr;
  int32_t lineInGlyph;
  int32_t glyphX;
  int32_t stringIndex;
  int32_t totalLines;
  byte currentChar;
  byte glyphRowData;
  int32_t* fontData;

  glyphX = 0;
  stringIndex = 0;
  totalLines = 1;
  lineInGlyph = 1;
  if (0 < textLength) {
    do {
      fontData = FontPixelMap;
      currentChar = stringText[stringIndex];
      if (currentChar == '|') {
        screenPixels = screenPixels + (screenStride * 16);
        totalLines = totalLines + 1;
        glyphX = 0;
      }
      else {
        lineInGlyph = 0;
        linePtr = (byte*)(glyphX + (intptr_t)screenPixels);
        do {
          glyphRowData = *(byte*)((intptr_t)fontData + lineInGlyph + ((uint32_t)currentChar * 16));
          bitIndex = 7;
          pixelPtr = linePtr;
          do {
            bitMask = (byte)bitIndex;
            bitIndex = bitIndex - 1;
            *pixelPtr = -((1 << (bitMask & 31) & (uint32_t)glyphRowData) != 0) & 31;
            pixelPtr = pixelPtr + 1;
          } while (bitIndex < 0x80000000);
          lineInGlyph = lineInGlyph + 1;
          linePtr = linePtr + screenStride;
        } while (lineInGlyph < 16);
        glyphX = glyphX + 8;
      }
      stringIndex = stringIndex + 1;
      lineInGlyph = totalLines;
    } while (stringIndex < textLength);
  }
  return lineInGlyph;
}

#endif
