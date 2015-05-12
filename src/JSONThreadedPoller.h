/*
 * JSONThreadedPoller.h
 *
 *  Created on: 11/05/2015
 *      Author: gandalf
 */

#ifndef JSONTHREADEDPOLLER_H_
#define JSONTHREADEDPOLLER_H_

#include <chrono>
#include <thread>
#include <functional>
#include <random>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "json11/json11.hpp"
#include "interface/Delegate.h"

namespace jsonevents {

class JSONThreadedPoller {
public:
    JSONThreadedPoller();
    virtual ~JSONThreadedPoller();
    void Start();
    void Stop();
    void AddDelegate(interface::Delegate &);
    void RemoveDelegate(interface::Delegate &);

    void SetProgressbar(interface::Delegate& pbar) ;
    void RemoveProgressbar();
private:
    void go();
    bool isRunning ;
    sf::Thread m_thread;
    int lompartTimestamp;

    interface::Delegate* messageLoader;
    std::vector<interface::Delegate*> delegates;
};

} /* namespace jsonevents */

#endif /* JSONTHREADEDPOLLER_H_ */
