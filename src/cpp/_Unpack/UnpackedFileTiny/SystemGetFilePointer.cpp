#include "HazardClasses/UnpackedFileTiny.hpp"
#include "HazardGlobals.hpp"

int32_t UnpackedFileTiny::getFilePointer() {
  int32_t currentFilePointer;
  currentFilePointer = GetCurentFilePointerLocation(this->fileHandleIndex);
  return currentFilePointer;
}
