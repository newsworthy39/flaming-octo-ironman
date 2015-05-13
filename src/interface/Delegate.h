
#ifndef __DELEGATE_H_
#define __DELEGATE_H_

#include <event/Event.h>
#include <json11/json11.hpp>

namespace interface {

class Delegate {
public:
    virtual ~Delegate() { }

    virtual void ReceiveMessage(const event::Event&, json11::Json & data ) = 0;

};

}
#endif
