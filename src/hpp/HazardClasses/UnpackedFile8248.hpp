#ifndef HAZARD_UNPACKEDFILE8248_HPP
#define HAZARD_UNPACKEDFILE8248_HPP

#include "HazardClasses/UnpackedFile44.hpp"
#include "HazardTypedef.hpp"

struct ArchiveEntry;
struct UnpackedFilePakStruct;

class UnpackedFile8248 : public UnpackedFile44 {

public:
  UnpackedFile8248(UnpackedFilePakStruct*, ArchiveEntry*, int32_t);
  virtual ~UnpackedFile8248();
  virtual int32_t readFile(void*, int32_t) override;
  virtual int32_t readByte() override;
  virtual int32_t setFilePointer(int32_t, int32_t) override;
  virtual int32_t getFilePointer() override;

  void RefillCompressedBuffer();

  int32_t currentFilePointer;
  int32_t decompressedByteCount;
  int32_t lastDecompressionPointer;
  byte decompressedBuffer[8192];
};

#endif
