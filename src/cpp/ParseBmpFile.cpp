#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardClasses/UnpackedFileBitmap.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/ParseBmpHelper.hpp"
#include "HazardStructs/RgbColor.hpp"

UnpackedFileBitmap* __fastcall UnpackedFileBitmap::ParseBmpFile(char* filename) {
  signed char colorValue;
  UnpackedFileBase* fileObject;
  UnpackedFileBitmap* bitmapObject;
  int32_t paletteEntryCount;
  uint32_t lengthMod4;
  int32_t paletteIndex;
  int32_t rowIndex;
  char fileHeaderBuf[14];
  ParseBmpHelper bitmapInfo;

  fileObject = UnpackedFileBase::LoadFileFromArchive(filename, 0x20000);

  fileObject->readFile(fileHeaderBuf, 14);

  DWORD fileHeader = *(WORD*)fileHeaderBuf;
  DWORD expectedHeader = *(WORD*)Flag_ParseBmp_14;
  if (fileHeader != expectedHeader) {
    return nullptr;
  }
  fileObject->readFile(&bitmapInfo, 40);
  bitmapObject = (UnpackedFileBitmap*)new byte[((bitmapInfo.bitmapWidth * bitmapInfo.bitmapHeight) + sizeof(UnpackedFileBitmap) - 4)];
  rowIndex = 0;
  bitmapObject->length1 = bitmapInfo.bitmapWidth;
  bitmapObject->length2 = bitmapInfo.bitmapHeight;
  bitmapObject->rgbColorMapAddress = bitmapObject->rgbColorMap;
  bitmapObject->shortColorMapAddress = bitmapObject->shortColorMap;
  bitmapObject->imageAddress = &bitmapObject->startOfImage;
  paletteIndex = 0;
  while (true) {
    paletteEntryCount = bitmapInfo.bitmapClrUsed;
    if (bitmapInfo.bitmapClrUsed == 0) {
      paletteEntryCount = 1 << ((byte)bitmapInfo.bitmapBitCount);
    }
    if (rowIndex >= paletteEntryCount) {
      break;
    }
    colorValue = fileObject->readByte();
    (&bitmapObject->rgbColorMapAddress->blue)[paletteIndex] = colorValue;

    colorValue = fileObject->readByte();
    (&bitmapObject->rgbColorMapAddress->green)[paletteIndex] = colorValue;

    colorValue = fileObject->readByte();
    (&bitmapObject->rgbColorMapAddress->red)[paletteIndex] = colorValue;

    fileObject->readByte();
    rowIndex = rowIndex + 1;
    paletteIndex = paletteIndex + 3;
  }
  paletteEntryCount = bitmapObject->length2;
  while (paletteEntryCount = paletteEntryCount + -1, 0 <= paletteEntryCount) {
    fileObject->readFile((bitmapObject->imageAddress + (bitmapObject->length1 * paletteEntryCount)), bitmapObject->length1);
    lengthMod4 = bitmapObject->length1 & 3;
    if ((lengthMod4 != 0) && (rowIndex = 4 - lengthMod4, 0 < rowIndex)) {
      do {
        fileObject->readByte();
        rowIndex = rowIndex + -1;
      } while (rowIndex != 0);
    }
  }
  if (fileObject != nullptr) {
    delete fileObject;
  }
  UnpackedFileBitmap::Calculate2ByteColorMap(bitmapObject->rgbColorMapAddress, bitmapObject->shortColorMapAddress, 0x100);
  return bitmapObject;
}
