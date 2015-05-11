
#ifndef __DELEGATE_H_
#define __DELEGATE_H_

namespace interface {


class Delegate {
public:
    virtual ~Delegate() { }
    virtual void Ping(int value) = 0;

};

}
#endif
