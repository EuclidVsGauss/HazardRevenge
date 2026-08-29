#include "HazardClasses/UnpackedFile44.hpp"

UnpackedFile44::~UnpackedFile44() throw() {
  delete this->dataBufferMemory;
}
