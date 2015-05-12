/*
 * Bardiagrams.cpp
 *
 *  Created on: 11/05/2015
 *      Author: gandalf
 */

#include "Bardiagrams.h"

namespace objects {

Bardiagrams::Bardiagrams(int numCols) :
        shapes(numCols) {

    this->rotate = 0;

    for (std::vector<objects::AnimatedRectangle>::size_type i = 0;
            i != shapes.size(); i++) {
        shapes[i].setHorizontalOffset((1 + i) * 20);
    }
}

Bardiagrams::~Bardiagrams() {

}

void Bardiagrams::ReceiveMessage(event::Event& ev) {
    this->shapes[rotate++ % this->shapes.size()].setValue(ev.GetValue());
}

void Bardiagrams::Update() {
    for (std::vector<objects::AnimatedRectangle>::iterator it = this->shapes.begin();
            it != this->shapes.end(); ++it) {
        (*it).Update();
    }
}

void Bardiagrams::draw(sf::RenderTarget& target,
        sf::RenderStates states) const {
    for (std::vector<objects::AnimatedRectangle>::size_type i = 0;
            i != shapes.size(); i++) {
        target.draw(shapes[i], states);
    }
}

} /* namespace objects */
