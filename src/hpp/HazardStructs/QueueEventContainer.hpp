#ifndef HAZARD_ARRAY256SWITCHIDS_HPP
#define HAZARD_ARRAY256SWITCHIDS_HPP
#include "HazardTypedef.hpp"

struct QueueEventContainer {
  intptr_t queueEvents[256];
};
typedef struct QueueEventContainer QueueEventContainer, *PQueueEventContainer;

#endif
