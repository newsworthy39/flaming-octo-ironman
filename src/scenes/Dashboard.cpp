/*
 * Bardiagrams.cpp
 *
 *  Created on: 11/05/2015
 *      Author: gandalf
 */

#include <scenes/Dashboard.h>

namespace scenes {

Dashboard::Dashboard(int screen_width) :
        shapes(screen_width / 20 - 1), rotate(0), messageBar(screen_width) {

    for (std::vector<scenes::AnimatedRectangle>::size_type i = 0;
            i != shapes.size(); i++) {
        shapes[i].setHorizontalOffset((1 + i) * 20);
    }
}

Dashboard::~Dashboard() {

}

void Dashboard::ReceiveMessage(event::Event& ev) {
    this->shapes[rotate++ % this->shapes.size()].setValue(ev.GetValue());

}

void Dashboard::ReceiveEventDelegateStatus(event::Event& ev) {
    this->messageBar.ReceiveMessage(ev);
}

void Dashboard::Update() {
    for (std::vector<scenes::AnimatedRectangle>::iterator it = this->shapes.begin();
            it != this->shapes.end(); ++it) {
        (*it).Update();
    }

    this->messageBar.Update();
}

void Dashboard::draw(sf::RenderTarget& target,
        sf::RenderStates states) const {
    for (std::vector<scenes::AnimatedRectangle>::size_type i = 0;
            i != shapes.size(); i++) {
        target.draw(shapes[i], states);
    }

    target.draw(messageBar, states);
}

} /* namespace objects */
