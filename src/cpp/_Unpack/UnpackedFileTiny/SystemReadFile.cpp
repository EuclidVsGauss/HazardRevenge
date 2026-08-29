#include "HazardClasses/AnimationStatusSpell.hpp"
#include "HazardClasses/UnpackedFileTiny.hpp"
#include "HazardGlobals.hpp"

int32_t UnpackedFileTiny::readFile(void* buffer, int32_t bytesToRead) {
  int32_t bytesRead;
  bytesRead = ReadFileWithTranslation(this->fileHandleIndex, (byte*)buffer, bytesToRead);
  return bytesRead;
}
