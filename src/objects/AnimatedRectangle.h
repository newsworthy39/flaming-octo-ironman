/*
 * AnimatedRectangle.h
 *
 *  Created on: 10/05/2015
 *      Author: gandalf
 */

#ifndef ANIMATEDRECTANGLE_H_
#define ANIMATEDRECTANGLE_H_

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

namespace scenes {

class AnimatedRectangle : public sf::Drawable, public sf::Transformable {
public:
    AnimatedRectangle();
    virtual ~AnimatedRectangle();

    void setValue(float value);
    void setHorizontalOffset(float horizontalOffset);
    void setRotate(float degrees);
    void Update();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::RectangleShape shape;
    float newValue;
    float prevValue;
    float horizontalOffset;
    float rotate;
};

} /* namespace objects */

#endif /* ANIMATEDRECTANGLE_H_ */
