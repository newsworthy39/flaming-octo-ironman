/*
 * EBdkImage.cpp
 *
 *  Created on: 16/05/2015
 *      Author: gandalf
 */

#include <panels/SmallImagePanel.hpp>

namespace objects {

SmallImagePanel::SmallImagePanel() {

    this->m_mediaPath = "/favicon.ico";

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

    this->m_headline.setColor(sf::Color(0, 255, 255, 240));
    this->m_teaser.setColor(sf::Color(0, 255, 255, 240));
    this->m_byline.setColor(sf::Color(0, 255, 255, 240));

}

const sf::Vector2f SmallImagePanel::GetDimensions() {
    return this->m_dimensions;
}

//// Move constructor.
//SmallImagePanel::SmallImagePanel(SmallImagePanel&& other) {
//    this->m_font_h1 = other.m_font_h1;
//
//    this->m_font_h2 = other.m_font_h2;
//    this->m_font_byline = other.m_font_byline;
//
//    this->m_mediaPath = other.m_mediaPath;
//    this->m_dimensions = other.m_dimensions;
//    this->m_texture = other.m_texture;
//    this->m_sprite = other.m_sprite;
//    this->m_rectangle = other.m_rectangle;
//
//    this->m_headline = other.m_headline;
//    this->m_teaser = other.m_teaser;
//    this->m_byline = other.m_byline;
//
//    this->m_slideX = other.m_slideX;
//    this->m_slideY = other.m_slideY;
//    this->m_slideDelta = other.m_slideDelta;
//}

void SmallImagePanel::SetTeaser(sf::String t) {
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

void SmallImagePanel::SetHeadline(sf::String t) {
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

void SmallImagePanel::SetByline(sf::String t) {
    // FIXME: GODDAMN! Hvad sker der for de tegn, som er enkodet utf8, multi-byte, men ikke kan ses af SFML
    //t.replace("ø", L"ø");
#ifdef __DEBUG__
    std::cout << "Byline " << t.toAnsiString() << std::endl;
#endif

    this->m_byline.setString(t);
}

void SmallImagePanel::SetMediaPath(sf::String imagePath) {
    this->m_mediaPath = imagePath;
}

void SmallImagePanel::SetDimensions(sf::Vector2f dimensions) {

    this->m_dimensions = dimensions;

    this->m_headline.setCharacterSize(this->m_dimensions.y / 25);

    this->m_teaser.setCharacterSize(this->m_dimensions.y / 28);

    this->m_byline.setCharacterSize(this->m_dimensions.y / 40);

}

void SmallImagePanel::UpdateDataAsync() {

    this->downloadImages();

    /**
     * finally, fix the image.
     */
    float sx = this->m_dimensions.x / (float) this->m_texture.getSize().x;
    float sy = this->m_dimensions.y / (float) this->m_texture.getSize().y;

    float scale = std::max(sx, sy);

#ifdef __DEBUG__

    float scaleW = sx * scale;
    float scaleH = sy * scale;

    std::cout << "Display properties: " << this->m_dimensions.x << "x"
            << this->m_dimensions.y << std::endl;
    std::cout << "Image properties: " << this->m_texture.getSize().x << "x"
            << this->m_texture.getSize().y << std::endl;
    std::cout << "SX, SY: " << sx << ", " << sy << std::endl;
    std::cout << "Scale: (minimum of sx, sy ~sx * scale) " << scale
            << std::endl;
    std::cout << "Scale * SX, SY " << scaleW << ", " << scaleH << std::endl;
#endif

    this->m_sprite.setScale(sf::Vector2f(scale, scale));

}

bool SmallImagePanel::downloadImages() {

    if (this->m_mediaPath.isEmpty()) {
#ifdef __DEBUG__
        std::cerr << "The SmallItemLargePanel m_imagePath == 0" << std::endl;
#endif
        return false;
    }

    std::string bckcompatible = this->m_mediaPath;
    ssize_t t1 = bckcompatible.find("http://", 0);
    ssize_t t2 = bckcompatible.find("/", t1 + 7);
    sf::String host = bckcompatible.substr(t1 + 7, t2 - (t1 + 7));
    sf::String path = bckcompatible.substr(t2, bckcompatible.length() - t2);

    sf::Http http(host);

    sf::Http::Request request;

    request.setMethod(sf::Http::Request::Get);

    request.setUri(path);

    request.setHttpVersion(1, 0);

    request.setField("Connection", "Close");
    request.setField("Accept", "image/webp");
    request.setField("Accept-Encoding", "gzip, deflate");
    request.setField("User-Agent", "libSFML2.2");

    sf::Http::Response response = http.sendRequest(request, sf::seconds(7));

#ifdef __DEBUG__
    std::cout << "Image: " << response.getStatus() << ", from "
            << this->m_mediaPath.toAnsiString() << "." << std::endl;
#endif

    if (response.getStatus() == sf::Http::Response::Ok) {

        void * ptrResponse = (void*) response.getBody().c_str();

        std::cout << "Response length: " << response.getField("Content-Length")
                << std::endl;

        ssize_t sSize = std::stoi(response.getField("Content-Length"));

        bool status = this->m_texture.loadFromMemory(ptrResponse, sSize);

        if (!status) {
            std::cerr << "Could not load image "
                    << std::string(this->m_mediaPath) << "." << std::endl;
            return false;
        }

        this->m_texture.setSmooth(true);
        this->m_sprite.setTexture(this->m_texture);

        return true;
    }

    return false;
}

SmallImagePanel::~SmallImagePanel() {
    //
}

void SmallImagePanel::UpdateGraphics(sf::FloatRect& view) {
    float noSlide =
            std::abs(
                    view.height
                            - (this->m_texture.getSize().y
                                    * this->m_sprite.getScale().y));
    if (noSlide > 2.0f) {
        this->m_slideY += this->m_slideDelta;
        if (this->m_slideY
                > std::abs(
                        view.height
                                - (this->m_texture.getSize().y
                                        * this->m_sprite.getScale().y))
                || this->m_slideY < 0.0f) {

            this->m_slideDelta = -this->m_slideDelta;
        }
    }

    this->m_sprite.setPosition(
            this->getPosition() - sf::Vector2f(this->m_slideX, this->m_slideY));

    // Setup gradient box # 1
    this->m_rectangle[0] = sf::Vertex(
            sf::Vector2f(this->getPosition().x,
                    this->getPosition().y + this->m_dimensions.y - 200),
            sf::Color(0, 0, 0, 0));

    this->m_rectangle[1] = sf::Vertex(
            sf::Vector2f(this->getPosition().x, this->m_dimensions.y),
            sf::Color(0, 0, 0, 255));

    this->m_rectangle[2] = sf::Vertex(
            sf::Vector2f(this->getPosition().x + this->m_dimensions.x,
                    this->getPosition().y + this->m_dimensions.y),
            sf::Color(0, 0, 0, 255));

    this->m_rectangle[3] = sf::Vertex(
            sf::Vector2f(this->getPosition().x + this->m_dimensions.x,
                    this->getPosition().y + this->m_dimensions.y - 200),
            sf::Color(0, 0, 0, 0));



    this->m_rectangle[4] = sf::Vertex(sf::Vector2f(this->getPosition().x + this->m_dimensions.x / 2, 0),
            sf::Color(0, 0, 0, 0));

    this->m_rectangle[5] = sf::Vertex(
            sf::Vector2f(this->getPosition().x + this->m_dimensions.x / 2, this->m_dimensions.y),
            sf::Color(0, 0, 0, 0));

    this->m_rectangle[6] = sf::Vertex(
            sf::Vector2f(this->getPosition().x + this->m_dimensions.x, this->m_dimensions.y),
            sf::Color(0, 0, 0, 255));

    this->m_rectangle[7] = sf::Vertex(sf::Vector2f(this->getPosition().x + this->m_dimensions.x, 0),
            sf::Color(0, 0, 0, 255));

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

void SmallImagePanel::draw(sf::RenderTarget& target,
        sf::RenderStates states) const {
    target.draw(this->m_sprite, states);
    target.draw(this->m_rectangle, 8, sf::Quads);
    target.draw(this->m_headline, states);
    target.draw(this->m_teaser, states);
    target.draw(this->m_byline, states);
}

} /* namespace objects */

