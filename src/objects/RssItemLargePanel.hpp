/*
 * EBdkImage.h
 *
 *  Created on: 16/05/2015
 *      Author: gandalf
 */

#ifndef OBJECTS_RSSITEMLARGEPANEL_H_
#define OBJECTS_RSSITEMLARGEPANEL_H_

#include <iostream>
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

namespace objects {

class RssItemLargePanel: public sf::Drawable, public sf::Transformable {
public:
    RssItemLargePanel();
    virtual ~RssItemLargePanel();

    // objects::RssItemLargePanel
    void Update();

    void Refresh();


    void SetTeaser(sf::String teaser);
    void SetHeadline(sf::String headline);
    void SetByline(sf::String byline);
    void SetMediaPath(sf::String mediaPath);
    void SetDimensions(sf::Vector2f dimensions);

    // sf::Drawable
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    bool downloadImages();
    sf::Font            m_font_h1;
    sf::Font            m_font_h2;
    sf::Font            m_font_byline;

    sf::String          m_mediaPath;
    sf::Vector2f        m_dimensions;
    sf::Texture         m_texture;
    sf::Sprite          m_sprite;
    sf::Vertex          m_rectangle[4];

    /**
     * Texts, used to describe the image.
     */

    sf::Text    m_headline;
    sf::Text    m_teaser;
    sf::Text    m_byline;

    float m_slideX, m_slideY, m_slideDelta;
};

} /* namespace objects */

#endif /* OBJECTS_RSSITEMLARGEPANEL_H_ */
