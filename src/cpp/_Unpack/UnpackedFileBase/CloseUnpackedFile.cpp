#include "HazardClasses/UnpackedFileBase.hpp"

void UnpackedFileBase::CloseUnpackedFile(UnpackedFileBase* unpackedObject) {
  delete unpackedObject;
}
