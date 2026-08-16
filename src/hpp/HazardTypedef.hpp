#ifndef HAZARD_TYPEDEF_HPP
#define HAZARD_TYPEDEF_HPP


#include <windows.h>

#ifdef _MSC_VER
typedef signed __int8 int8_t;
typedef signed __int16 int16_t;
typedef signed __int32 int32_t;
typedef signed __int64 int64_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;

typedef signed __int32 intptr_t;
typedef signed __int32 uintptr_t;
typedef unsigned __int32 uint64_t;
typedef unsigned __int32 ssize_t;
#define nullptr 0
#define override
#else
#define __forceinline inline
#endif

typedef unsigned char byte;
typedef LONGLONG longlong;
typedef ULONGLONG ulonglong;
typedef uint16_t uint16_t;

#endif
