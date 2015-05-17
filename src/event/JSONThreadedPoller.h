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
#include <event/Event.h>
#include <interface/Observable.h>
#include <json12/json11.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

namespace events {

class JSONThreadedPoller {
public:
    JSONThreadedPoller(const std::string host, int port = 80);
    virtual ~JSONThreadedPoller();
    void Start();
    void Stop();
    void AddObserver(interface::Observable &);
    void RemoveObserver(interface::Observable &);

private:
    void go();
    bool isRunning ;
    sf::Thread sfThread;
    int lompartTimestamp;
    std::vector<interface::Observable*> delegates;
	sf::Http http;

};

} /* namespace jsonevents */

#endif /* JSONTHREADEDPOLLER_H_ */
