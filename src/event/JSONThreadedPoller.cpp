/*
 * JSONThreadedPoller.cpp
 *
 *  Created on: 11/05/2015
 *      Author: gandalf
 */

#include "JSONThreadedPoller.h"

namespace events {

JSONThreadedPoller::JSONThreadedPoller(const std::string host, int port) :
        sfThread(&JSONThreadedPoller::go, this) {
    this->isRunning = false;
    this->lompartTimestamp = 9999999;
    this->messageLoader = NULL;
    this->http.setHost(host, port);
}

JSONThreadedPoller::~JSONThreadedPoller() {
    // TODO Auto-generated destructor stub
}

void JSONThreadedPoller::Start() {

    this->isRunning = true;

    this->sfThread.launch();
}

void JSONThreadedPoller::Stop() {

    this->isRunning = false;

    this->sfThread.wait();

}

void JSONThreadedPoller::AddDelegate(interface::Delegate & delegate) {
    this->delegates.push_back(&delegate);
}

void JSONThreadedPoller::RemoveDelegate(interface::Delegate & delegate) {
    for (std::vector<interface::Delegate*>::iterator it =
            this->delegates.begin(); it != this->delegates.end(); it++) {
        auto & mVecdelegate = *it;

        // Address cmp, ? (can i haz that)
        if (mVecdelegate == &delegate) {
            this->delegates.erase(it);
        }
    }
}

void JSONThreadedPoller::AddEventStatusDelegate(interface::EventDelegateStatus& pbar) {
    this->messageLoader = &pbar;
}

void JSONThreadedPoller::RemoveEventStatusDelegate() {
    this->messageLoader = NULL;
}

void JSONThreadedPoller::go() {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(3, 7);

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

        request.setHttpVersion(1, 0); // HTTP 1.0

        // We provide the header, for event-polling, to allow header-inspection
        // in loadbalancing equipment, also to allow for cache-equipment, to
        // use as like a vary-by-header.
        request.setField("x-lompart-token", std::to_string(lompartTimestamp));

        json11::Json my_json = json11::Json::object { { "x-lompart-token",
                lompartTimestamp }, };

        request.setBody(my_json.dump());

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
            value = json["x-lompart-token"].int_value();

        } else {
            value = this->lompartTimestamp;
        }

        // If this increases, then it was updated. Do something.
        if (value > this->lompartTimestamp) {

            // Now. How many messages, do we need to fetch?
            int numMessages = value - lompartTimestamp;

            sf::Http::Request request;

            for (int i = 0; i < numMessages; i++) {

                if (this->isRunning == false)
                    break;

                request.setMethod(sf::Http::Request::Method::Get);

                request.setUri("/getmsg.php");

                /*
                 * TODO: Change, the sfml-dev http library, as
                 * it does not support http-chunked-encoding.
                 * Only http/1.0 is supported.
                 */
                request.setHttpVersion(1, 0); // HTTP 1.1

                // We provide the header, for event-polling, to allow header-inspection
                // in loadbalancing equipment, also to allow for cache-equipment, to
                // use as like a vary-by-header.
                request.setField("x-lompart-token",
                        std::to_string(lompartTimestamp));

                json11::Json my_json = json11::Json::object { {
                        "x-lompart-token", lompartTimestamp + i }, };

                request.setBody(my_json.dump());

                sf::Http::Response response = http.sendRequest(request);

                sf::Http::Response::Status status = response.getStatus();

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
                if (status == sf::Http::Response::Ok) {

                    std::string err;

                    auto json = json11::Json::parse(response.getBody(), err);

                    /*
                     * This section, should probably be replaced, with a json-parser, that
                     * reads and parses the message-structures, and creates the appropriate
                     * objects for delegation. Use virtual, to let the compiler decide, via
                     * its interface.
                     */
                    int value = json["data"].int_value();

                    event::Event numMsg(numMessages - i);
                    this->messageLoader->ReceiveEventDelegateStatus(numMsg);

                    event::Event ev(value);
                    for (std::vector<interface::Delegate*>::iterator it =
                            this->delegates.begin();
                            it != this->delegates.end(); it++) {

                        interface::Delegate*& delegate = *it;

                        delegate->ReceiveMessage(ev);

                    } // End ping delegates
                } // end if not 404
            } // end message-loop
        } // end outer while loop

        // Allways, end on the lighter side :)
        this->lompartTimestamp = value; // update the value, so we don't fetch it several times.
    }
}
}
/* namespace events */
