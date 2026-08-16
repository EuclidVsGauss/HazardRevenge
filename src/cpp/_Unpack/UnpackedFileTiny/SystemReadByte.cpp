#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFileTiny.hpp"
#include "HazardGlobals.hpp"

int32_t UnpackedFileTiny::readByte() {
  byte byteRead;
  int32_t resultCode;

  resultCode = this->readFile(&byteRead, 1);
  if (resultCode != 0) {
    return byteRead;
  }
  return -1;
}
