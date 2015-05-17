/*
 * Bardiagrams.cpp
 *
 *  Created on: 11/05/2015
 *      Author: gandalf
 */

#include <scenes/Dashboard.h>

namespace scenes {

Dashboard::Dashboard() {

}

void Dashboard::SetDimensions(sf::Vector2f dimensions) {
    this->m_dimensions = dimensions;
    this->m_messageBar.setPosition(
            sf::Vector2f(this->getPosition().x, this->m_dimensions.y - 60));
    this->m_animatedRectangle.setPosition(
            sf::Vector2f(this->getPosition().x, this->getPosition().y));
}

Dashboard::~Dashboard() {
    // TODO: Unregister stuff here.
}

void Dashboard::Refresh() {

    sf::Http http("http://ubuntu64bit-msgstack00.lan", 10000);

    sf::Http::Request request;

    request.setMethod(sf::Http::Request::Method::Get);

    request.setUri("/view/ebrss?type=raw");

    request.setHttpVersion(1, 1); // HTTP 1.0

    request.setField("Connection", "Close");

    sf::Http::Response response = http.sendRequest(request);

    if (response.getStatus() == sf::Http::Response::Ok) {

        // foreach, that shit.
        std::string err;
        auto json = json11::Json::parse(response.getBody(), err);

#ifdef __DEBUG__
        std::cout << err << ", " << json.dump()<< std::endl;
#endif

        objects::RssItemLargePanel * p = new objects::RssItemLargePanel();
        p->SetDimensions(this->m_dimensions);
        p->SetHost(json["host"].string_value());
        p->SetImagePath(json["imagepath"].string_value());
        p->SetHeadline(json["headline"].string_value());
        p->SetTeaser(json["teaser"].string_value());
        p->SetByline(json["byline"].string_value());

        p->Refresh();

        this->m_RssMembers.push_back(p);

    }

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

    // this->m_ebdkimage.Update();
    for (objects::RssItemLargePanel * p : this->m_RssMembers) {
        p->Update();
    }

    this->m_messageBar.Update();

    this->m_animatedRectangle.Update();
}

void Dashboard::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    //target.draw(this->m_ebdkimage, states);

    for (const objects::RssItemLargePanel * p : this->m_RssMembers) {
        target.draw(*p, states);
    }

    target.draw(this->m_messageBar, states);
    target.draw(this->m_animatedRectangle, states);
}

} /* namespace objects */
