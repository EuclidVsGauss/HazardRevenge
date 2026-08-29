#include "HazardClasses/EventHandler.hpp"
#include "HazardGlobals.hpp"

void EventHandler::QueueTwoEvents(int32_t param_1, int32_t param_2) {
  this->__InlineableQueueEvent(param_2);
  this->__InlineableQueueEvent(param_1);
}
