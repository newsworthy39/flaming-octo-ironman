/*
 * Bardiagrams.h
 *
 *  Created on: 11/05/2015
 *      Author: gandalf
 */

#ifndef BARDIAGRAMS_H_
#define BARDIAGRAMS_H_


#include "AnimatedRectangle.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "interface/Delegate.h"

#include <iostream>
#include <vector>

namespace objects {

class Bardiagrams: public sf::Transformable,
        public sf::Drawable,
        public interface::Delegate {
public:
    Bardiagrams( int numCols);
    virtual ~Bardiagrams();
    void Update();
    void ReceiveMessage(event::Event&);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    std::vector<objects::AnimatedRectangle> shapes;
    int rotate;
};

} /* namespace objects */

#endif /* BARDIAGRAMS_H_ */
