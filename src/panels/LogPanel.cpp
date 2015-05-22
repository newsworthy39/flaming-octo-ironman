/*
 * EBdkImage.cpp
 *
 *  Created on: 16/05/2015
 *      Author: gandalf
 */

#include <panels/LogPanel.hpp>

namespace panels {

LogPanel::LogPanel() {

    this->m_dimensions = sf::Vector2f(640, 480);

    this->m_slideX = 0.0f;

    this->m_slideY = 0.0f;

    this->m_slideDelta = 0.1f;

    // FIXME: Fonts are loaded from an absolute location.
    this->m_font_h1.loadFromFile(
            "/home/gandalf/workspace/flaming-octo-ironman/src/font/Roboto-Regular.ttf");

    // FIXME: Fonts are loaded from an absolute location.
    this->m_font_h2.loadFromFile(
            "/home/gandalf/workspace/flaming-octo-ironman/src/font/Roboto-Regular.ttf");

    // FIXME: Fonts are loaded from an absolute location.
    this->m_font_byline.loadFromFile(
            "/home/gandalf/workspace/flaming-octo-ironman/src/font/Roboto-Light.ttf");

    this->m_byline.setFont(this->m_font_byline);
    this->m_teaser.setFont(this->m_font_h2);
    this->m_headline.setFont(this->m_font_h1);

    this->m_headline.setColor(sf::Color(250, 0, 0, 255));
    this->m_teaser.setColor(sf::Color(0, 100, 100, 255));
    this->m_byline.setColor(sf::Color(0, 130, 130, 255));

}

const sf::Vector2f LogPanel::GetDimensions() {
    return this->m_dimensions;
}

void LogPanel::SetTeaser(sf::String t) {
    // FIXME: GODDAMN! Hvad sker der for de tegn, som er enkodet utf8, multi-byte, men ikke kan ses af SFML
    //t.replace("ø", L"ø");

    int numCharsOnALine = 50;
    int numLines = std::ceil(t.getSize() / numCharsOnALine);
#ifdef __DEBUG__
    std::cout << "Teaser " << t.toAnsiString() << "Lines is " << numLines
            << std::endl;
#endif
    for (int i = 0; i < numLines; i++) {
        int findblank = t.find(' ', numCharsOnALine * (i + 1));
        t[findblank] = '\n';
    }

    this->m_teaser.setString(t);
}

void LogPanel::SetHeadline(sf::String t) {
    // FIXME: GODDAMN! Hvad sker der for de tegn, som er enkodet utf8, multi-byte, men ikke kan ses af SFML
    //t.replace("ø", L"ø");
    int numCharsOnALine = 100;
    int numLines = std::ceil(t.getSize() / numCharsOnALine);
#ifdef __DEBUG__
    std::cout << "Headline " << t.toAnsiString() << "Lines is " << numLines
            << std::endl;
#endif
    for (int i = 0; i < numLines; i++) {
        int findblank = t.find(' ', numCharsOnALine * (i + 1));
        t[findblank] = '\n';
    }

    this->m_headline.setString(t);
}

void LogPanel::SetByline(sf::String t) {
    // FIXME: GODDAMN! Hvad sker der for de tegn, som er enkodet utf8, multi-byte, men ikke kan ses af SFML
    //t.replace("ø", L"ø");
#ifdef __DEBUG__
    std::cout << "Byline " << t.toAnsiString() << std::endl;
#endif

    this->m_byline.setString(t);
}

void LogPanel::SetDimensions(sf::Vector2f dimensions) {

    this->m_dimensions = dimensions;

    this->m_headline.setCharacterSize(this->m_dimensions.y / 25);

    this->m_teaser.setCharacterSize(this->m_dimensions.y / 28);

    this->m_byline.setCharacterSize(this->m_dimensions.y / 40);

}

void LogPanel::UpdateDataAsync() {

}

LogPanel::~LogPanel() {
    //
}

void LogPanel::UpdateGraphics(sf::FloatRect& view) {

    // Setup gradient box # 1
    this->m_rectangle[0] = sf::Vertex(
            sf::Vector2f(this->getPosition().x,
                    this->getPosition().y + this->m_dimensions.y - 200),
            sf::Color(0,255,255, 0));

    this->m_rectangle[1] = sf::Vertex(
            sf::Vector2f(this->getPosition().x, this->m_dimensions.y),
            sf::Color(0,255,255, 255));

    this->m_rectangle[2] = sf::Vertex(
            sf::Vector2f(this->getPosition().x + this->m_dimensions.x,
                    this->getPosition().y + this->m_dimensions.y),
            sf::Color(0,255,255, 255));

    this->m_rectangle[3] = sf::Vertex(
            sf::Vector2f(this->getPosition().x + this->m_dimensions.x,
                    this->getPosition().y + this->m_dimensions.y - 200),
            sf::Color(0,255,255, 0));

    this->m_rectangle[4] = sf::Vertex(
            sf::Vector2f(this->getPosition().x + this->m_dimensions.x / 2, 0),
            sf::Color(0,255,255, 0));

    this->m_rectangle[5] = sf::Vertex(
            sf::Vector2f(this->getPosition().x + this->m_dimensions.x / 2,
                    this->m_dimensions.y), sf::Color(0,255,255, 0));

    this->m_rectangle[6] = sf::Vertex(
            sf::Vector2f(this->getPosition().x + this->m_dimensions.x,
                    this->m_dimensions.y), sf::Color(0,255,255, 255));

    this->m_rectangle[7] = sf::Vertex(
            sf::Vector2f(this->getPosition().x + this->m_dimensions.x, 0),
            sf::Color(0,255,255, 255));

    /**
     * Position the text, accordingly.
     */
    this->m_headline.setPosition(
            sf::Vector2f(this->getPosition().x + 40,
                    this->getPosition().y + this->m_dimensions.y / 2 + 40));

    this->m_teaser.setPosition(
            sf::Vector2f(this->getPosition().x + 80,
                    this->getPosition().y + this->m_dimensions.y / 2 + 80));

    this->m_byline.setPosition(
            this->getPosition().x + this->m_dimensions.x
                    - ((this->m_byline.getCharacterSize() / 2.0f)
                            * this->m_byline.getString().getSize() + 20),
            this->getPosition().y + this->m_dimensions.y - 60);

}

void LogPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->m_rectangle, 8, sf::Quads);
    target.draw(this->m_headline, states);
    target.draw(this->m_teaser, states);
    target.draw(this->m_byline, states);
}

} /* namespace objects */

