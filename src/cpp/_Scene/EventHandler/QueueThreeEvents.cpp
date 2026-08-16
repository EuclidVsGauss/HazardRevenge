#include "HazardClasses/EventHandler.hpp"
#include "HazardGlobals.hpp"

void EventHandler::QueueThreeEvents(int32_t firstEvent, int32_t secondEvent, int32_t thirdEvent) {
  this->__InlineableQueueEvent(thirdEvent);
  this->__InlineableQueueEvent(secondEvent);
  this->__InlineableQueueEvent(firstEvent);
}
