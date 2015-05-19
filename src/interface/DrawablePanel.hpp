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

    virtual void UpdateGraphics() = 0;
    virtual void UpdateDataAsync() = 0;
    virtual void SetDimensions(sf::Vector2f dimensions) = 0;

};

}
#endif
