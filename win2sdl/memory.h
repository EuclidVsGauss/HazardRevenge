#ifndef REVENGE_MEMORY_H
#define REVENGE_MEMORY_H

#include "win2sdl.h"

static void FillMemory(void* Destination, DWORD Length, BYTE Fill){
    memset((Destination), (Fill), (Length));
}

#endif //REVENGE_MEMORY_H