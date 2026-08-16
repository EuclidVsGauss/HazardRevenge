#include "HazardClasses/EventHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/QueueEventContainer.hpp"

int32_t EventHandler::PopQueuedElement() {
  int32_t currentCounter;
  int32_t newCounter;

  currentCounter = this->eventCounter;
  if (0 < currentCounter) {
    newCounter = currentCounter - 1;
    this->eventCounter = newCounter;
    return this->queuedEventsArray[newCounter >> 8]->queueEvents[newCounter & 0xff];
  }
  return 0;
}
