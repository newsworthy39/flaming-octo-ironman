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
Dashboard::Dashboard(const std::string host, int port) {
    this->m_port = port;
    this->m_host = host;
    this->m_paneldisplaycounter = 0;

    // FIXME: Fonts are loaded from an absolute location.
    this->m_font_h1.loadFromFile(
            "/home/gandalf/workspace/flaming-octo-ironman/src/font/Roboto-Regular.ttf");

    this->m_clock.setFont(this->m_font_h1);
    this->m_clock.setColor(sf::Color(255, 0, 0, 240));
    this->m_clock.setCharacterSize(120);

    this->prevValue = 0.f;
    this->newValue = 0.f;

    updateClock();
}

void Dashboard::AddPanel(interface::DrawablePanel * p) {
    unsigned int maxPanels = 10;

    this->m_largepanelimages.insert(this->m_largepanelimages.begin(), p);

    if (this->m_largepanelimages.size() >= maxPanels) {

#ifdef __DEBUG__
        std::cout << "Destroyed first element, size is: "
                << this->m_largepanelimages.size() << std::endl;
#endif
        const interface::DrawablePanel* p1 = this->m_largepanelimages.back();
        this->m_largepanelimages.pop_back();
        delete p1; // LargeImagePanels

        //delete p1;
    }

    // Next, push the rest to the side.
    sf::Vector2f l_position(0.f, 0.f);
    for (std::vector<interface::DrawablePanel*>::iterator p =
            this->m_largepanelimages.begin();
            p != this->m_largepanelimages.end(); ++p) {

        (*p)->setPosition(l_position);

        l_position.x += (*p)->GetDimensions().x;
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

}

Dashboard::~Dashboard() {
    // TODO: Unregister stuff here.
}

void Dashboard::UpdateDataAsync() {


    sf::Http http(this->m_host, this->m_port);

    sf::Http::Request request;

    request.setMethod(sf::Http::Request::Method::Get);

    request.setUri("/view/dashboard-0?type=raw");

    request.setHttpVersion(1, 0); // HTTP 1.0

    request.setField("Connection", "Close");

    sf::Http::Response response = http.sendRequest(request);

    if (response.getStatus() == sf::Http::Response::Ok) {

        // foreach, that shit.
        std::string err;
        auto json = json11::Json::parse(response.getBody(), err);

        // resourcefactory o; (observable and stuff)
        // o.addMediaPath(json["mediapath"]);
        // interface::Drawable * d = new ...
        // d->addResourceFactory(o)
        // d->UpdateDataAsync
        // (inside d) this->m_resourceFactory.Download(this->m_mediapath)

        std::random_device rd;
        //std::mt19937 mt(rd());
        std::default_random_engine mt(rd());
        std::uniform_int_distribution<> dist(0, 1);
        int f = dist(mt);

#ifdef __DEBUG__
        std::cout << err << ", " << json.dump() << std::endl;
        std::cout << "Random: " << f << std::endl;
#endif
        // This is the first part of the decision-making.
        if (0 == std::string().compare(json["mediapath"].string_value())) {
#ifdef __DEBUG__
            std::cout << "No image path" << std::endl;
#endif
            f = 2; // Deliberately, set textpanel if no image.
        }

        switch (f) {
        case 0: {
            objects::LargeImagePanel * p = new objects::LargeImagePanel();
            p->SetMediaPath(json["mediapath"].string_value());
            p->SetHeadline(json["headline"].string_value());
            p->SetTeaser(json["teaser"].string_value());
            p->SetByline(json["byline"].string_value());
            p->SetDimensions(this->m_dimensions);

            p->UpdateDataAsync();

            this->AddPanel(p);

        }
            ;
            break;
        case 1: {
            objects::SmallImagePanel * p = new objects::SmallImagePanel();
            p->SetMediaPath(json["mediapath"].string_value());
            p->SetHeadline(json["headline"].string_value());
            p->SetTeaser(json["teaser"].string_value());
            p->SetByline(json["byline"].string_value());
            p->SetDimensions(this->m_dimensions);

            p->UpdateDataAsync();

            this->AddPanel(p);

        }
            ;
            break;

        case 2: {
            objects::LogPanel * p = new objects::LogPanel();

            p->SetHeadline(json["headline"].string_value());
            p->SetTeaser(json["teaser"].string_value());
            p->SetByline(json["byline"].string_value());
            p->SetDimensions(this->m_dimensions);

            p->UpdateDataAsync();

            this->AddPanel(p);

        }
            ;
            break;

        }
    }
}

/**
 * Dashboard::ReceiveEventDelegateStatus
 * Receives a message, when arrived.
 */
void Dashboard::ReceiveMessage(const event::Event& e, json11::Json & data) {
    switch (e) {
    case event::Event::MESSAGESPENDING: {
        this->m_progressbar.SetValue(data["messagespending"].int_value());

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

void Dashboard::UpdateGraphics(sf::FloatRect& view) {

    this->updateClock();

    /*
     * So we're going to cheet. If the last restart is large than
     * 30 seconds, pick a new panel. (this simulates an animator.)
     */
    if (this->m_wallclock.getElapsedTime() >= sf::seconds(30)) {
        this->m_wallclock.restart();

        this->prevValue = this->newValue;
        this->newValue += view.width;

        if (this->newValue >= (this->m_largepanelimages.size() * view.width)) {
            this->newValue = 0;
        }

    }

    float diffRadius = (this->prevValue - this->newValue) / 8;
    view.left = this->prevValue + diffRadius;
    this->prevValue -= diffRadius;

    /**
     * This is ALLWAYS the same position.
     */
    this->m_clock.setPosition(
            view.left + view.width
                    - ((this->m_clock.getCharacterSize() / 2.0)
                            * this->m_clock.getString().getSize() + 40),
            view.top);

    this->m_progressbar.setPosition(
            sf::Vector2f(view.left + 40, view.height - 60));

    for (interface::DrawablePanel * p : this->m_largepanelimages) {
        p->UpdateGraphics(view);
    }

    this->m_progressbar.UpdateGraphics(view);

}

void Dashboard::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    for (auto *p : this->m_largepanelimages) {
        if (p != NULL)
            target.draw(*p, states);
    }

    target.draw(this->m_progressbar, states);
    target.draw(this->m_clock, states);
}

} /* namespace objects */
