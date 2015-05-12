/*
 * Progressbar.h
 *
 *  Created on: 12/05/2015
 *      Author: gandalf
 */

#ifndef OBJECTS_PROGRESSBAR_H_
#define OBJECTS_PROGRESSBAR_H_

#include <interface/Delegate.h>
#include <event/Event.h>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <SFML/Graphics.hpp>


#include <iostream>

namespace objects {

class Progressbar: public sf::Drawable,
        public interface::Delegate,
        public sf::Transformable {
public:
    Progressbar(int);
    virtual ~Progressbar();
    void Update();
    void draw(sf::RenderTarget& target,
            sf::RenderStates states) const ;
    void SetValue(int value);
    void ReceiveMessage(event::Event&);

private:
    sf::RectangleShape messageLoader;
    sf::Text tekst;
    sf::Font font;
    int screen_w;
};

} /* namespace objects */

#endif /* OBJECTS_PROGRESSBAR_H_ */
