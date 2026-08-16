#ifndef HAZARD_UNPACKEDFILE32_HPP
#define HAZARD_UNPACKEDFILE32_HPP

#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardTypedef.hpp"

class UnpackedFile32 : public UnpackedFileBase {

public:
  UnpackedFile32(uint32_t, int32_t);
  virtual ~UnpackedFile32();
  virtual int32_t readFile(void*, int32_t) override;
  virtual int32_t readByte() override;
  virtual int32_t setFilePointer(int32_t, int32_t) override;
  virtual int32_t getFilePointer() override;

  int32_t fileStartOffset;
  int32_t chunkOffset;
  int32_t bytesReadCumulative;
  int32_t lastReadOffset;
  int32_t chunkBufferSize;
  byte* cachedFileDataBuffer;
  uint32_t fileHandleId;
};

#endif
