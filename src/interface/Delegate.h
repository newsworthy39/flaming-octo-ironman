
#ifndef __DELEGATE_H_
#define __DELEGATE_H_

#include "event/Event.h"

namespace interface {

class Delegate {
public:
    virtual ~Delegate() { }
    virtual void ReceiveMessage(event::Event&) = 0;
};

}
#endif
