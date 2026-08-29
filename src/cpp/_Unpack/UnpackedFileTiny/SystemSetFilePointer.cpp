#include "HazardClasses/UnpackedFileTiny.hpp"
#include "HazardGlobals.hpp"

int32_t UnpackedFileTiny::setFilePointer(int32_t distanceToMove, int32_t moveMethod) {
  int32_t returnValue;
  returnValue = SetFilePointer(this->fileHandleIndex, distanceToMove, moveMethod);
  return returnValue;
}
