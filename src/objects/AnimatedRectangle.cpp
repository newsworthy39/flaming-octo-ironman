/*
 * AnimatedRectangle.cpp
 *
 *  Created on: 10/05/2015
 *      Author: gandalf
 */

#include "AnimatedRectangle.h"

namespace objects {

AnimatedRectangle::AnimatedRectangle() {
    this->shape.setFillColor(sf::Color(16, 16, 16));
	this->newValue = 0.0f;
    this->prevValue = 0.0f;

}

AnimatedRectangle::~AnimatedRectangle() {

}

void AnimatedRectangle::setValue(float value) {
    this->prevValue = this->newValue;
    this->newValue = value;
}

void AnimatedRectangle::Update() {

    float diffRadius = (this->prevValue - this->newValue) / 16;

    //shape.setRadius(this->prevValue + diffRadius);

    this->shape.setPosition(this->getPosition());

    this->shape.setSize(sf::Vector2f(20, this->prevValue + diffRadius));

    this->shape.setFillColor(sf::Color(163, 38, 38));

    this->prevValue -= diffRadius;
}

void AnimatedRectangle::draw(sf::RenderTarget& target,
        sf::RenderStates states) const {
    target.draw(this->shape, states);
}

} /* namespace objects */
