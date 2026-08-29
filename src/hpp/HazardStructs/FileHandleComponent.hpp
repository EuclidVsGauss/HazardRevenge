#ifndef HAZARD_FILEHANDLECOMPONENT_HPP
#define HAZARD_FILEHANDLECOMPONENT_HPP

#include "HazardStructs/HandleEntry.hpp"
#include "HazardTypedef.hpp"

struct FileHandleComponent {
  HandleEntry entries[32];
};
typedef struct FileHandleComponent FileHandleComponent, *PFileHandleComponent;

#endif
