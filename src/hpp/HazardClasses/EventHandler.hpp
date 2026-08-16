#ifndef HAZARD_EVENTHANDLER_HPP
#define HAZARD_EVENTHANDLER_HPP

#include "HazardStructs/QueueEventContainer.hpp"
#include "HazardTypedef.hpp"

class EventHandler {

public:
  EventHandler();
  virtual ~EventHandler();
  int32_t PopQueuedElement();

  void QueueEvent(intptr_t param_2);
  void QueueTwoEvents(int32_t param_1, int32_t param_2);
  void QueueThreeEvents(int32_t param_1, int32_t param_2, int32_t param_3);

  QueueEventContainer* queuedEventsArray[5];
  int32_t unusedQueueEventContainer[11];
  int32_t eventCounter;

  inline void __InlineableQueueEvent(intptr_t value) {
    int32_t uVar1;
    if (this->queuedEventsArray[this->eventCounter >> 8] == nullptr) {
      this->queuedEventsArray[this->eventCounter >> 8] = new QueueEventContainer;
    }
    uVar1 = this->eventCounter;
    this->queuedEventsArray[uVar1 >> 8]->queueEvents[uVar1 & 0xff] = value;
    this->eventCounter = this->eventCounter + 1;
  }

  __forceinline void __InlineQueueEvent(intptr_t value) {
    int32_t uVar1;
    if (this->queuedEventsArray[this->eventCounter >> 8] == nullptr) {
      this->queuedEventsArray[this->eventCounter >> 8] = new QueueEventContainer;
    }
    uVar1 = this->eventCounter;
    this->queuedEventsArray[uVar1 >> 8]->queueEvents[uVar1 & 0xff] = value;
    this->eventCounter = this->eventCounter + 1;
  }
};

#endif
