/*
 * Bardiagrams.cpp
 *
 *  Created on: 11/05/2015
 *      Author: gandalf
 */

#include <scenes/Dashboard.h>

namespace scenes {

Dashboard::Dashboard(sf::Vector2f coords) {
    this->setPosition(coords);
}

void Dashboard::SetDimensions(sf::Vector2f dimensions) {
    this->m_dimensions = dimensions;
    this->m_messageBar.setPosition(sf::Vector2f(this->getPosition().x, this->m_dimensions.y - 60));
    this->m_animatedRectangle.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y));
}

Dashboard::~Dashboard() {
    // TODO: Unregister stuff here.
}

void Dashboard::Refresh() {

    sf::Http http("http://ubuntu64bit-msgstack00.lan", 9000);

    sf::Http::Request request;

    request.setMethod(sf::Http::Request::Method::Get);

    request.setUri("/view/ebrss?type=raw");

    request.setHttpVersion(1, 1); // HTTP 1.0

    request.setField("Connection", "Close");

    sf::Http::Response response = http.sendRequest(request);

    if (response.getStatus() == sf::Http::Response::Ok) {

        std::string err;
        std::string test = response.getBody();
        auto json = json11::Json::parse(test, err);
        this->m_ebdkimage.SetImagePath(json["imagepath"].string_value());
        this->m_ebdkimage.SetHeadline(json["headline"].string_value());
        this->m_ebdkimage.SetTeaser(json["teaser"].string_value());
        this->m_ebdkimage.SetByline(json["byline"].string_value());

    }

    this->m_ebdkimage.resizeObject(this->m_dimensions);
}

/**
 * Dashboard::ReceiveEventDelegateStatus
 * Receives a message, when arrived.
 */
void Dashboard::ReceiveMessage(const event::Event& e, json11::Json & data) {
    switch (e) {
    case event::Event::MESSAGESPENDING: {
        this->m_messageBar.SetValue(data["messagespending"].int_value());

    }
        ;
        break;
    case event::Event::MESSAGE: {
        std::string stringValue = data["message"].string_value();
        if (0 == stringValue.compare("update")) {
#ifdef __DEBUG__
            std::cout << "I was asked to do a full update" << std::endl;
#endif
            this->Refresh();
        }
    }
        ;
        break;
    case event::Event::UPDATE: {
        this->Refresh();
    }
        ;
        break;
    }
}

void Dashboard::Update() {

    this->m_ebdkimage.Update();

    this->m_messageBar.Update();

    this->m_animatedRectangle.Update();
}

void Dashboard::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->m_ebdkimage, states);

    target.draw(this->m_messageBar, states);
    target.draw(this->m_animatedRectangle, states);
}

} /* namespace objects */
