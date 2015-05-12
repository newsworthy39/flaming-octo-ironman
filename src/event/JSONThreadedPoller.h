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

#include <json11/json11.hpp>
#include <event/Event.h>
#include <interface/Delegate.h>
#include <interface/EventStatusDelegate.h>

namespace events {

class JSONThreadedPoller {
public:
    JSONThreadedPoller(const std::string host, int port = 80);
    virtual ~JSONThreadedPoller();
    void Start();
    void Stop();
    void AddDelegate(interface::Delegate &);
    void RemoveDelegate(interface::Delegate &);

    void AddEventStatusDelegate(interface::EventDelegateStatus& pbar) ;
    void RemoveEventStatusDelegate();
private:
    void go();
    bool isRunning ;
    sf::Thread sfThread;
    int lompartTimestamp;

    interface::EventDelegateStatus* messageLoader;
    std::vector<interface::Delegate*> delegates;

	sf::Http http;

};

} /* namespace jsonevents */

#endif /* JSONTHREADEDPOLLER_H_ */
