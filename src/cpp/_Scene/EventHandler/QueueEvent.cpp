#include "HazardClasses/EventHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/QueueEventContainer.hpp"

void EventHandler::QueueEvent(intptr_t value) {
  int32_t maskedCounter;

  if (this->queuedEventsArray[this->eventCounter >> 8] == nullptr) {
    this->queuedEventsArray[this->eventCounter >> 8] = new QueueEventContainer;
  }
  maskedCounter = this->eventCounter;
  this->queuedEventsArray[maskedCounter >> 8]->queueEvents[maskedCounter & 0xff] = value;
  this->eventCounter = this->eventCounter + 1;
}
