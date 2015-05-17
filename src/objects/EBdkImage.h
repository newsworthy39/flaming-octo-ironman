/*
 * EBdkImage.h
 *
 *  Created on: 16/05/2015
 *      Author: gandalf
 */

#ifndef OBJECTS_EBDKIMAGE_H_
#define OBJECTS_EBDKIMAGE_H_

#include <iostream>
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

namespace objects {

class EBdkImage: public sf::Drawable, public sf::Transformable {
public:
    EBdkImage();
    virtual ~EBdkImage();

    // objects::EBdkImage
    void Update();

    void resizeObject(sf::Vector2f resizeTo);
    void SetTeaser(sf::String teaser);
    void SetHeadline(sf::String headline);
    void SetByline(sf::String byline);
    void SetImagePath(sf::String imagePath);


    // sf::Drawable
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

    bool PrepareImage();

    sf::Font            m_font_h1;
    sf::Font            m_font_h2;
    sf::Font            m_font_byline;

    sf::String          m_imagePath;
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

#endif /* OBJECTS_EBDKIMAGE_H_ */
