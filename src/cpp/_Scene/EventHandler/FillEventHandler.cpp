#include "HazardClasses/EventHandler.hpp"
#include "HazardGlobals.hpp"
#include "HazardStructs/QueueEventContainer.hpp"

EventHandler::EventHandler() {

  memset(&this->queuedEventsArray, 0x0, (sizeof(int32_t) * 11) + (sizeof(QueueEventContainer*) * 5));
  this->eventCounter = 0;
}
