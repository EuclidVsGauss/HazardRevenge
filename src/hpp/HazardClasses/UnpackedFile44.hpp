#ifndef HAZARD_UNPACKEDFILE44_HPP
#define HAZARD_UNPACKEDFILE44_HPP

#include "HazardClasses/UnpackedFileBase.hpp"
#include "HazardTypedef.hpp"

struct ArchiveEntry;
struct UnpackedFilePakStruct;

class UnpackedFile44 : public UnpackedFileBase {

public:
  UnpackedFile44(UnpackedFilePakStruct*, ArchiveEntry*, int32_t);
  virtual ~UnpackedFile44();
  virtual int32_t readFile(void*, int32_t) override;
  virtual int32_t readByte() override;
  virtual int32_t setFilePointer(int32_t, int32_t) override;
  virtual int32_t getFilePointer() override;

  int32_t uncompressedDataLength;
  byte* dataBufferMemory;
  int32_t bufferReadOffset;
  int32_t archiveSegmentStartOffset;
  int32_t currentSegmentStartPointer;
  int32_t compressedDataSize;
  int32_t sourceFileReadPosition;
  int32_t bufferAllocationSize;
  UnpackedFilePakStruct* sourceFileObject;
  ArchiveEntry* archiveEntryMetadata;
};

#endif
