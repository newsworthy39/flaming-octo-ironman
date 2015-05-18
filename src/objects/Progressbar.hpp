/*
 * Progressbar.h
 *
 *  Created on: 12/05/2015
 *      Author: gandalf
 */

#ifndef OBJECTS_PROGRESSBAR_H_
#define OBJECTS_PROGRESSBAR_H_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

namespace objects {

class Progressbar: public sf::Drawable,
        public sf::Transformable {
public:
    Progressbar();
    virtual ~Progressbar();
    void UpdateGraphics();
    void draw(sf::RenderTarget& target,
            sf::RenderStates states) const ;
    void SetValue(int value);
    int GetValue();
private:
    sf::RectangleShape messageLoader;
    sf::Text tekst;
    sf::Font font;
};

} /* namespace objects */

#endif /* OBJECTS_PROGRESSBAR_H_ */
