/*
 * Progressbar.cpp
 *
 *  Created on: 12/05/2015
 *      Author: gandalf
 */

#include <panels/Progressbar.hpp>

namespace objects {

Progressbar::Progressbar() {
    m_font.loadFromFile(
            "/home/gandalf/workspace/flaming-octo-ironman/src/font/Roboto-Light.ttf");

    m_tekst.setFont(m_font);
    m_tekst.setString("0");
    m_tekst.setCharacterSize(20);
    m_tekst.setColor(sf::Color(sf::Color(255, 0, 0, 240)));
    m_messageLoader.setFillColor(sf::Color(255, 0, 0, 240));
}

Progressbar::~Progressbar() {
    // FIXME: Progressbar destructor is empty.
}

void Progressbar::SetDimensions(sf::Vector2f dimensions) {
    this->m_dimensions = dimensions;
}

void Progressbar::UpdateDataAsync() {

}

const sf::Vector2f Progressbar::GetDimensions() {
    return this->m_dimensions;
}

void Progressbar::UpdateGraphics(sf::FloatRect& view) {

    if (this->GetValue() <= 0) {
        m_tekst.setString("");
    }

    m_tekst.setPosition(this->getPosition());
    m_messageLoader.setPosition(this->getPosition() + sf::Vector2f(0, 30));
}



void Progressbar::draw(sf::RenderTarget& target,
        sf::RenderStates states) const {

    target.draw(this->m_tekst, states);
    target.draw(this->m_messageLoader, states);

}

void Progressbar::SetValue(int value) {
    m_messageLoader.setSize(sf::Vector2f(std::min(500, value), 10));
    m_tekst.setString(std::to_string(value));
}

int Progressbar::GetValue() {
    return this->m_messageLoader.getSize().x;
}

} /* namespace objects */
