#ifndef HAZARD_UNPACKEDFILEBASE_HPP
#define HAZARD_UNPACKEDFILEBASE_HPP
#include "HazardFunctions.hpp"
#include "HazardTypedef.hpp"

class UnpackedFileBase {

public:
  UnpackedFileBase() {}

  virtual ~UnpackedFileBase() {}

  virtual int32_t readFile(void*, int32_t) {
    ExitGame();
    return -1;
  }

  virtual int32_t readByte() {
    ExitGame();
    return -1;
  }

  virtual int32_t setFilePointer(int32_t, int32_t) {
    ExitGame();
    return -1;
  }

  virtual int32_t getFilePointer() {
    ExitGame();
    return -1;
  }

  static UnpackedFileBase* __cdecl LoadFileFromArchive(char* filename, int32_t chunkSize);
  static void __fastcall LoadAndClosePak(UnpackedFileBase* param_1);
  static void CloseUnpackedFile(UnpackedFileBase*);
};

#endif
