
#ifndef __EVENTDELEGATESTATUS_H_
#define __EVENTDELEGATESTATUS_H_

#include "event/Event.h"

namespace interface {

class EventDelegateStatus {
public:
    virtual ~EventDelegateStatus() { }
    virtual void ReceiveEventDelegateStatus(event::Event&) = 0;
};

}
#endif
