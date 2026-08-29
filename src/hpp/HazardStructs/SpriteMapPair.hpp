#ifndef HAZARD_ASTRUCT_17_HPP
#define HAZARD_ASTRUCT_17_HPP

#include "HazardTypedef.hpp"

struct ImageVectorWithHeader;

struct SpriteMapPair {
  char sprName[16];
  ImageVectorWithHeader** imageVectors;
  ImageVectorWithHeader** sprImageArray;
  int32_t scalar;
  SpriteMapPair* previous;
};
typedef struct SpriteMapPair SpriteMapPair, *PSpriteMapPair;

#endif
