/*
 * Dashboard.
 *
 *  Created on: 11/05/2015
 *      Author: newsworthy39 @ github.com
 */

#include <scenes/Dashboard.h>

namespace scenes {

/**
 * Dashboard constructor.
 */
Dashboard::Dashboard() : m_LargePanelImages(0) {
    this->m_panelDisplayCounter = 0;


    // FIXME: Fonts are loaded from an absolute location.
    this->m_font_h1.loadFromFile(
            "/home/gandalf/workspace/flaming-octo-ironman/src/font/Roboto-Regular.ttf");

    this->m_clock.setFont(this->m_font_h1);
    this->m_clock.setColor(sf::Color(0, 255, 255, 240));
    this->m_clock.setCharacterSize(120);

    updateClock();
}

void Dashboard::AddPanel(objects::LargeImagePanel* p) {
    unsigned int maxPanels = 10;

    this->m_LargePanelImages.insert(this->m_LargePanelImages.begin(), p);

    if (this->m_LargePanelImages.size() >= maxPanels) {

#ifdef __DEBUG__
        std::cout << "Destroyed first element, size is: " << this->m_LargePanelImages.size() << std::endl;
#endif
        const objects::LargeImagePanel * p1 = this->m_LargePanelImages.back();
        this->m_LargePanelImages.pop_back();
        delete p1; // LargeImagePanels

        //delete p1;

    }
}

void Dashboard::updateClock() {
    std::locale::global(std::locale("en_US.utf8"));
    std::time_t t = std::time(NULL);
    char mbstr[100];
    std::strftime(mbstr, sizeof(mbstr), "%H:%M", std::localtime(&t));

    this->m_clock.setString(mbstr);
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

void Dashboard::UpdateDataAsync() {

    sf::Http http("http://192.168.1.67", 9001);

    sf::Http::Request request;

    request.setMethod(sf::Http::Request::Method::Get);

    request.setUri("/view/dashboard-0?type=raw");

    request.setHttpVersion(1, 1); // HTTP 1.0

    request.setField("Connection", "Close");

    sf::Http::Response response = http.sendRequest(request);

    if (response.getStatus() == sf::Http::Response::Ok) {

        // foreach, that shit.
        std::string err;
        auto json = json11::Json::parse(response.getBody(), err);

#ifdef __DEBUG__
        std::cout << err << ", " << json.dump() << std::endl;
#endif

        objects::LargeImagePanel * p = new objects::LargeImagePanel();
        p->SetMediaPath(json["mediapath"].string_value());
        p->SetHeadline(json["headline"].string_value());
        p->SetTeaser(json["teaser"].string_value());
        p->SetByline(json["byline"].string_value());
        p->SetDimensions(this->m_dimensions);

        p->UpdateDataAsync();

        this->AddPanel(p);

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
            this->UpdateDataAsync();
        }
    }
        ;
        break;
    case event::Event::UPDATE: {
        this->UpdateDataAsync();
    }

        break;
    }
}

void Dashboard::UpdateGraphics() {

    this->updateClock();

    this->m_clock.setPosition(
            this->m_dimensions.x
                    - ((this->m_clock.getCharacterSize() / 2.0)
                            * this->m_clock.getString().getSize() + 40), 0);

    /*
     * So we're going to cheet. If the last restart is large than
     * 30 seconds, pick a new panel.
     */
    if (this->m_wallclock.getElapsedTime() >= sf::seconds(10)) {
        this->m_wallclock.restart();

        this->m_panelDisplayCounter = ++this->m_panelDisplayCounter
                % this->m_LargePanelImages.size();

        std::cout << "Wall clock change, changing panel [max]"
                << this->m_LargePanelImages.size() << ", current "
                << this->m_panelDisplayCounter << std::endl;
    }

    for (objects::LargeImagePanel * p : this->m_LargePanelImages) {
        p->UpdateGraphics();
    }

    this->m_messageBar.UpdateGraphics();


}

void Dashboard::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    const objects::LargeImagePanel * p =
            this->m_LargePanelImages.at(this->m_panelDisplayCounter);

    if (p != NULL)
        target.draw(*p, states);

    target.draw(this->m_messageBar, states);

    target.draw(this->m_clock, states);
}

} /* namespace objects */
