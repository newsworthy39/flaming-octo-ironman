/*
 * AnimatedRectangle.cpp
 *
 *  Created on: 10/05/2015
 *      Author: gandalf
 */

#include "AnimatedRectangle.h"

namespace objects {

AnimatedRectangle::AnimatedRectangle() {
    this->newValue = 0.0f;
    this->prevValue = 0.0f;
    this->horizontalOffset = 0;
    this->shape.setFillColor(sf::Color(16, 16, 16));

}

void AnimatedRectangle::setHorizontalOffset(float horizontalOffset) {
    this->horizontalOffset = horizontalOffset;
}

AnimatedRectangle::~AnimatedRectangle() {
    // TODO Auto-generated destructor stub
}

void AnimatedRectangle::setValue(float value) {
    this->prevValue = this->newValue;
    this->newValue = value;
}

void AnimatedRectangle::Update() {
    float diffRadius = (this->prevValue - this->newValue) / 16;

    //shape.setRadius(this->prevValue + diffRadius);
    this->shape.setSize(sf::Vector2f(20, this->prevValue + diffRadius));

    this->shape.setFillColor(sf::Color(163, 38, 38));

    this->shape.setPosition(sf::Vector2f(this->horizontalOffset, 20));

    this->prevValue -= diffRadius;
}

void AnimatedRectangle::draw(sf::RenderTarget& target,
        sf::RenderStates states) const {
    target.draw(this->shape, states);
}

} /* namespace objects */
