
#ifndef __DELEGATE_H_
#define __DELEGATE_H_

#include <event/Event.h>
#include <json12/json11.hpp>

namespace interface{

class Observable {
public:
    virtual ~Observable() { }

    virtual void ReceiveMessage(const event::Event&, json11::Json & data ) = 0;

};

}
#endif
