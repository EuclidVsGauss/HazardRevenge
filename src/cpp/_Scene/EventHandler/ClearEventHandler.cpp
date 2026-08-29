#include "HazardClasses/EventHandler.hpp"
#include "HazardStructs/QueueEventContainer.hpp"

EventHandler::~EventHandler() {
  QueueEventContainer** currentEventPtr = this->queuedEventsArray;

  while (*currentEventPtr != nullptr) {
    delete *currentEventPtr;
    currentEventPtr++;
  }
}
