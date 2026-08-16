#ifndef HAZARD_HANDLEENTRY_HPP
#define HAZARD_HANDLEENTRY_HPP
#include "HazardTypedef.hpp"

typedef struct HandleEntry HandleEntry, *PHandleEntry;

struct HandleEntry {
  HANDLE handle;

  union {
    uint64_t metadata;

    struct {
      uint8_t flags;
      uint8_t stored_char;
      uint8_t padding[6];
    };
  };
};

#endif
