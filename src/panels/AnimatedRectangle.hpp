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

#include <iostream>

namespace objects {

class AnimatedRectangle : public sf::Drawable, public sf::Transformable {
public:
    AnimatedRectangle();
    virtual ~AnimatedRectangle();
    void setValue(float value);
    const float GetValue();
    void setHorizontalOffset(float horizontalOffset);
    void Update();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::RectangleShape shape;
    float newValue;
    float prevValue;

};

} /* namespace objects */

#endif /* ANIMATEDRECTANGLE_H_ */
