#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardGlobals.hpp"

int32_t UnpackedFile44::getFilePointer() {
  return ((this->sourceFileReadPosition - this->bufferAllocationSize) - this->archiveSegmentStartOffset) + this->bufferReadOffset;
}
