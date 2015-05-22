/*
 * Progressbar.h
 *
 *  Created on: 12/05/2015
 *      Author: gandalf
 */

#ifndef OBJECTS_PROGRESSBAR_H_
#define OBJECTS_PROGRESSBAR_H_

#include <iostream>
#include <interface/DrawablePanel.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>



namespace panels {

class Progressbar: public interface::DrawablePanel {
public:
    Progressbar();
    virtual ~Progressbar();

    // From DrawablePanel
    void UpdateGraphics(sf::FloatRect&);
    void UpdateDataAsync();
    const sf::Vector2f GetDimensions();
    void SetDimensions(sf::Vector2f);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void SetValue(int value);
    int GetValue();
private:
    sf::RectangleShape m_messageLoader;
    sf::Text m_tekst;
    sf::Font m_font;
    sf::Vector2f m_dimensions;
};

} /* namespace objects */

#endif /* OBJECTS_PROGRESSBAR_H_ */
