/*
 * Bardiagrams.h
 *
 *  Created on: 11/05/2015
 *      Author: gandalf
 */

#ifndef DASHBOARD_H_
#define DASHBOARD_H_

#include <objects/AnimatedRectangle.h>
#include <objects/Progressbar.h>
#include <interface/Delegate.h>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <json11/json11.hpp>

#include <iostream>
#include <vector>

namespace scenes {

class Dashboard: public sf::Transformable,
        public sf::Drawable,
        public interface::Delegate {

public:
    Dashboard(sf::Vector2f coords, sf::Vector2f dimensions);
    virtual ~Dashboard();
    void Update();
    void UpdateEverything();

    // Passing solution
    void ReceiveMessage(const event::Event&, json11::Json & data );

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    objects::AnimatedRectangle animatedRectangle;
    objects::Progressbar messageBar;
    sf::Vector2f dimensions;

};

} /* namespace objects */

#endif /* BARDIAGRAMS_H_ */
