#ifndef __DELEGATE_H_
#define __DELEGATE_H_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

namespace interface {

class DrawablePanel: public sf::Drawable, public sf::Transformable {
public:
    virtual ~DrawablePanel() {
    }
    ;
    virtual void UpdateGraphics(sf::FloatRect&) = 0;
    virtual void UpdateDataAsync() = 0;
    const virtual sf::Vector2f GetDimensions() = 0;
    virtual void SetDimensions(sf::Vector2f) = 0;
};

}
#endif
