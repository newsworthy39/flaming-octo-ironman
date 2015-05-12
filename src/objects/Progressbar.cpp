/*
 * Progressbar.cpp
 *
 *  Created on: 12/05/2015
 *      Author: gandalf
 */

#include <objects/Progressbar.h>

namespace objects {

Progressbar::Progressbar() {

    font.loadFromFile(
            "/home/gandalf/workspace/flaming-octo-ironman/src/font/Roboto-Light.ttf");

    tekst.setFont(font);
    tekst.setString("0");
    tekst.setCharacterSize(20);
    tekst.setColor(sf::Color(0, 0, 0));
    tekst.setPosition(sf::Vector2f(20, 440));

    messageLoader.setPosition(sf::Vector2f(20, 400));
    messageLoader.setFillColor(sf::Color(163, 38, 38));

}

Progressbar::~Progressbar() {
    // TODO Auto-generated destructor stub
}

void Progressbar::Update() {
    // TODO Nothing to do.
}

void Progressbar::Ping(int value) {
    this->SetValue(value);
}

void Progressbar::draw(sf::RenderTarget& target,
        sf::RenderStates states) const {
    target.draw(this->tekst, states);
    target.draw(this->messageLoader, states);
}

void Progressbar::SetValue(int value) {
    messageLoader.setSize(sf::Vector2f(value, 10));
    tekst.setCharacterSize(20);
    tekst.setColor(sf::Color(0, 0, 0));
    tekst.setPosition(sf::Vector2f(20, 440));
    tekst.setString(std::to_string(value));
}

} /* namespace objects */
