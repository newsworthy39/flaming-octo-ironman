/*
 * EBdkImage.cpp
 *
 *  Created on: 16/05/2015
 *      Author: gandalf
 */

#include <objects/RssItemLargePanel.h>

namespace objects {

RssItemLargePanel::RssItemLargePanel() {

    this->m_imagePath = "/favicon.ico";

    this->m_dimensions = sf::Vector2f(640, 480);

    this->m_slideX = 0.0f;

    this->m_slideY = 0.0f;

    this->m_slideDelta = 0.1f;

    this->m_font_h1.loadFromFile(
            "/home/gandalf/workspace/flaming-octo-ironman/src/font/Roboto-Regular.ttf");

    this->m_font_h2.loadFromFile(
            "/home/gandalf/workspace/flaming-octo-ironman/src/font/Roboto-LightItalic.ttf");

    this->m_font_byline.loadFromFile(
            "/home/gandalf/workspace/flaming-octo-ironman/src/font/Roboto-Light.ttf");

    this->m_byline.setFont(this->m_font_byline);
    this->m_teaser.setFont(this->m_font_h2);
    this->m_headline.setFont(this->m_font_h1);

    this->m_headline.setColor(sf::Color(255, 255, 255));
    this->m_teaser.setColor(sf::Color(255, 255, 255));
    this->m_byline.setColor(sf::Color(255, 255, 255));

}

void RssItemLargePanel::SetTeaser(sf::String t) {

    // FIXME: GODDAMN! Hvad sker der for de tegn, som er enkodet utf8, multi-byte, men ikke kan ses af SFML
//    t.replace("ø", L"ø");
    t.replace("æ", L"æ");
    t.replace("å", L"å");

    t.replace("Ø", L"Ø");
    t.replace("Æ", L"Æ");
    t.replace("Å", L"Å");

    int numCharsOnALine = 100;
    int numLines = std::ceil(t.getSize() / numCharsOnALine);
#ifdef __DEBUG__
    std::cout << "Teaser " << t.toAnsiString() << "Lines is " << numLines << std::endl;
#endif
    for (int i = 0; i < numLines; i++) {
        int findblank = t.find(' ', numCharsOnALine * (i + 1));
        t[findblank] = '\n';
    }

    this->m_teaser.setString(t);
}

void RssItemLargePanel::SetHeadline(sf::String t) {

    // FIXME: GODDAMN! Hvad sker der for de tegn, som er enkodet utf8, multi-byte, men ikke kan ses af SFML

    int numCharsOnALine = 100;
    int numLines = std::ceil(t.getSize() / numCharsOnALine);
#ifdef __DEBUG__
    std::cout << "Headline " << t.toAnsiString() << "Lines is " << numLines << std::endl;
#endif
    for (int i = 0; i < numLines; i++) {
        int findblank = t.find(' ', numCharsOnALine * (i + 1));
        t[findblank] = '\n';
    }

    this->m_headline.setString(t);
}

void RssItemLargePanel::SetByline(sf::String t) {

    // FIXME: GODDAMN! Hvad sker der for de tegn, som er enkodet utf8, multi-byte, men ikke kan ses af SFML
    t.replace("ø", L"ø");
    t.replace("æ", L"æ");
    t.replace("å", L"å");

    t.replace("Ø", L"Ø");
    t.replace("Æ", L"Æ");
    t.replace("Å", L"Å");

#ifdef __DEBUG__
    std::cout << "Byline " << t.toAnsiString() << std::endl;
#endif

    this->m_byline.setString(t);
}

void RssItemLargePanel::SetHost(sf::String host) {
    this->m_host = host;
}

void RssItemLargePanel::SetImagePath(sf::String imagePath) {
    this->m_imagePath = imagePath;
}

void RssItemLargePanel::SetDimensions(sf::Vector2f dimensions) {
    this->m_dimensions = dimensions;
}

void RssItemLargePanel::Refresh() {

    this->downloadImages();

    this->m_rectangle[0] = sf::Vertex(sf::Vector2f(0, 200),
            sf::Color(0, 0, 0, 0));

    this->m_rectangle[1] = sf::Vertex(sf::Vector2f(0, this->m_dimensions.y),
            sf::Color(0, 0, 0, 240));

    this->m_rectangle[2] = sf::Vertex(
            sf::Vector2f(this->m_dimensions.x, this->m_dimensions.y),
            sf::Color(0, 0, 0, 240));

    this->m_rectangle[3] = sf::Vertex(sf::Vector2f(this->m_dimensions.x, 200),
            sf::Color(0, 0, 0, 0));

    this->m_headline.setCharacterSize(this->m_dimensions.y / 32);

    this->m_teaser.setCharacterSize(this->m_dimensions.y / 34);

    this->m_byline.setCharacterSize(this->m_dimensions.y / 40);

    /**
     * Position the text, accordingly.
     */
    this->m_headline.setPosition(
            sf::Vector2f(40, this->m_dimensions.y / 2 + 40));

    this->m_teaser.setPosition(sf::Vector2f(80, this->m_dimensions.y / 2 + 80));

    this->m_byline.setPosition(
            this->m_dimensions.x
                    - ((this->m_byline.getCharacterSize() / 2)
                            * this->m_byline.getString().getSize()),
            this->m_dimensions.y - 40);

    /**
     * finally, fix the image.
     */
    float sx = this->m_texture.getSize().x / this->m_dimensions.x;
    float sy = this->m_texture.getSize().y / this->m_dimensions.y;

    float scale = std::min(sx, sy);

    float scaleW = sx * scale;
    float scaleH = sy * scale;

#ifdef __DEBUG__
    std::cout << "I have (scale) " << scale << ", sx " << sx << ", sy " << sy
            << "scaleW " << scaleW << ", scaleH " << scaleH << std::endl;
#endif

    this->m_sprite.setScale(sf::Vector2f(1.0f + scaleW, 1.0f + scaleW));

}

bool RssItemLargePanel::downloadImages() {

    if (this->m_imagePath.isEmpty()) {
#ifdef __DEBUG__
        std::cerr << "The RssItemLargePanel m_imagePath == 0" << std::endl;
#endif
        return false;
    }

    sf::Http http(this->m_host);

    sf::Http::Request request;

    request.setMethod(sf::Http::Request::Get);

    request.setUri(this->m_imagePath);

    request.setHttpVersion(1, 1);

    request.setField("Connection", "Close");

    sf::Http::Response response = http.sendRequest(request);

#ifdef __DEBUG__
    std::cout << "Image: " << response.getStatus() << ", from "
            << this->m_host.toAnsiString() << " on "
            << this->m_imagePath.toAnsiString() << "." << std::endl;
#endif

    if (response.getStatus() == sf::Http::Response::Ok) {

        void * ptrResponse = (void*) response.getBody().c_str();

        std::cout << "Response length: " << response.getField("Content-Length")
                << std::endl;

        ssize_t sSize = std::stoi(response.getField("Content-Length"));

        bool status = this->m_texture.loadFromMemory(ptrResponse, sSize);

        if (!status) {
            std::cerr << "Could not load image "
                    << std::string(this->m_imagePath) << "." << std::endl;
            return false;
        }

        this->m_texture.setSmooth(true);
        this->m_sprite.setTexture(this->m_texture);

        return true;
    }

    return false;
}

RssItemLargePanel::~RssItemLargePanel() {
    //
}

void RssItemLargePanel::Update() {
    // this->m_texture.getSize().y * this->m_sprite.getScale().y   = Scaled Image Full Height.
    // this->m_dimensions.y - (this->m_texture.getSize().y * this->m_sprite.getScale().y)
    this->m_slideY += this->m_slideDelta;
    if (this->m_slideY
            > std::abs(
                    this->m_dimensions.y
                            - (this->m_texture.getSize().y
                                    * this->m_sprite.getScale().y))
            || this->m_slideY < 0.0f) {

        this->m_slideDelta = -this->m_slideDelta;
    }

    this->m_sprite.setPosition(
            this->getPosition() - sf::Vector2f(this->m_slideX, this->m_slideY));

}

void RssItemLargePanel::draw(sf::RenderTarget& target,
        sf::RenderStates states) const {
    target.draw(this->m_sprite, states);
    target.draw(this->m_rectangle, 4, sf::Quads);
    target.draw(this->m_headline, states);
    target.draw(this->m_teaser, states);
    target.draw(this->m_byline, states);
}

} /* namespace objects */

