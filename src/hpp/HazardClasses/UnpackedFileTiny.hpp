#ifndef HAZARD_UNPACKEDFILETINY_HPP
#define HAZARD_UNPACKEDFILETINY_HPP

#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardTypedef.hpp"

class UnpackedFileTiny : public UnpackedFileBase {

public:
  virtual ~UnpackedFileTiny();
  virtual int32_t readFile(void*, int32_t) override;
  virtual int32_t readByte() override;
  virtual int32_t setFilePointer(int32_t, int32_t) override;
  virtual int32_t getFilePointer() override;

  int32_t unused;
  int32_t fileHandleIndex;
};

#endif
