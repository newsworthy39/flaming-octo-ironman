/*
 * EBdkImage.h
 *
 *  Created on: 16/05/2015
 *      Author: gandalf
 */

#ifndef OBJECTS_LOGPANEL_H_
#define OBJECTS_LOGPANEL_H_

#include <iostream>
#include <string>
#include <interface/DrawablePanel.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

namespace objects {

class LogPanel: public interface::DrawablePanel {

public:
    LogPanel();
    virtual ~LogPanel();

    // From DrawablePanel
     void UpdateGraphics(sf::FloatRect&);
     void UpdateDataAsync();
     const sf::Vector2f GetDimensions();
     void SetDimensions(sf::Vector2f);
     void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void SetTeaser(sf::String teaser);
    void SetHeadline(sf::String headline);
    void SetByline(sf::String byline);

private:
    sf::Font m_font_h1;
    sf::Font m_font_h2;
    sf::Font m_font_byline;
    sf::Vector2f m_dimensions;

    /**
     * Texts, used to describe the image.
     */
    sf::Text m_headline;
    sf::Text m_teaser;
    sf::Text m_byline;

    float m_slideX, m_slideY, m_slideDelta;

    sf::Vertex m_rectangle[8];
};

} /* namespace objects */

#endif /* OBJECTS_LOGPANEL_H_ */
