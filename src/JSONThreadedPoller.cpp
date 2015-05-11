/*
 * JSONThreadedPoller.cpp
 *
 *  Created on: 11/05/2015
 *      Author: gandalf
 */

#include "JSONThreadedPoller.h"

namespace jsonevents {

JSONThreadedPoller::JSONThreadedPoller() :
        m_thread(&JSONThreadedPoller::go, this) {
    this->isRunning = false;
    this->lompartTimestamp = 9999999;
}

JSONThreadedPoller::~JSONThreadedPoller() {
    // TODO Auto-generated destructor stub
}

void JSONThreadedPoller::Start() {

    this->isRunning = true;

    std::cout << "STarting json thread" << std::endl;

    this->m_thread.launch();
}

void JSONThreadedPoller::Stop() {

    this->isRunning = false;

    std::cout << "Stopping json thread" << std::endl;

    this->m_thread.wait();

}

void JSONThreadedPoller::AddDelegate(interface::Delegate & delegate) {
    this->delegates.push_back(&delegate);
}

void JSONThreadedPoller::go() {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(3, 7);


    sf::Http http;
    http.setHost("http://force.mjay.me");

    /**
     * Let two threads, share the lompartTimestamp (jikes!)
     * Use a polling-thread, that runs at its own pace, then
     * update the lompart-timestamp. Let the second thread,
     * read the messages.
     * Pass the same http-connection along, as it might be
     * necessary to do a protocol upgrade.
     */
    while (this->isRunning) {

        // Start by sleeping it off.
        sf::sleep(sf::seconds(dist(mt)));

        // Actually do the requests.
        sf::Http::Request request;

        request.setMethod(sf::Http::Request::Method::Get);

        request.setUri("/msg.php");

        request.setHttpVersion(1, 0); // HTTP 1.1

        request.setField("X-lompart-Token", std::to_string(lompartTimestamp));

        sf::Http::Response response = http.sendRequest(request);

#ifdef __DEBUG__
        std::cout << "status: " << response.getStatus() << std::endl;
        std::cout << "HTTP version: " << response.getMajorHttpVersion() << "."
                << response.getMinorHttpVersion() << std::endl;
        std::cout << "Content-Type header:" << response.getField("Content-Type")
                << std::endl;
        std::cout << "body: " << response.getStatus() << std::endl;

        std::cout << "Response: " << response.getBody() << std::endl;
#endif

        /*
         * This block determines if the timestamp has changed, and if its necessary
         * to fetch the messages.
         */
        int value = 0;
        if (response.getBody() != "") {

            const std::string simple_test = response.getBody();
            //R"({"k1":"v1", "k2":42, "k3":["a",123,true,false,null]})";
            std::string err;
            auto json = json11::Json::parse(simple_test, err);
            value = json["lompartToken"].int_value();

        } else {
            value = this->lompartTimestamp;
        }

        // If this increases, then it was updated. Do something.
        if (value > this->lompartTimestamp) {

            // Now. How many messages, do we need to fetch?
            int numMessages = value - lompartTimestamp;

            for (int i = 0; i < numMessages; i++) {

                if (this->isRunning == false)
                    break;

                sf::Http::Request request;

                request.setMethod(sf::Http::Request::Method::Get);

                request.setUri("/getmsg.php");

                request.setHttpVersion(1, 0); // HTTP 1.1

                request.setField("X-lompart-Token",
                        std::to_string(lompartTimestamp + i));

                sf::Http::Response response = http.sendRequest(request);

#ifdef __DEBUG__
                std::cout << "status: " << response.getStatus() << std::endl;
                std::cout << "HTTP version: " << response.getMajorHttpVersion()
                        << "." << response.getMinorHttpVersion() << std::endl;
                std::cout << "Content-Type header:"
                        << response.getField("Content-Type") << std::endl;
                std::cout << "body: " << response.getStatus() << std::endl;

                std::cout << "(fetched data) Response: " << response.getBody()
                        << std::endl;

#endif
                if (response.getStatus() != 404) {

                    const std::string test2 = response.getBody();
                    //R"({"k1":"v1", "k2":42, "k3":["a",123,true,false,null]})";

                    std::string err;
                    auto json = json11::Json::parse(test2, err);

                    //std::cout << "k1: " << json["tekst"].string_value() << "\n";
                    //      std::cout << "k3: " << json["k3"].dump() << "\n";

                    //          for (auto &k : json["k3"].array_items()) {
                    //                  std::cout << "    - " << k.dump() << "\n";
//                  }

                    /*
                     * This section, should probably be replaced, with a json-parser, that
                     * reads and parses the message-structures, and creates the appropriate
                     * objects for delegation. Use virtual, to let the compiler decide, via
                     * its interface.
                     */

                    int value = json["data"].int_value();

                    /* shapes[rotate++ % shapes.size()].setValue(value);

                     // 'Demo-purpose only.
                     messageLoader.setSize(sf::Vector2f(numMessages - i, 10));

                     tekst = std::to_string(numMessages - i);
                     //tekst = std::to_string();*/


                    this->delegates[0]->Ping(value);
                }
            }
        }

        // Allways, end on the lighter side :)
        this->lompartTimestamp = value; // update the value, so we don't fetch it several times.
    }
}

}
/* namespace events */
