
#ifndef _OBSERVABLE_H
#define _OBSERVABLE_H

#include <event/Event.h>
#include <json11/json11.hpp>

namespace interface{

class Observable {
public:
    virtual ~Observable() { }

    virtual void ReceiveMessage(const event::Event&, json11::Json & data ) = 0;

};

}
#endif
