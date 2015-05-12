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

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <interface/Delegate.h>
#include <interface/EventStatusDelegate.h>

#include <iostream>
#include <vector>

namespace scenes {

class Dashboard: public sf::Transformable,
        public sf::Drawable,
        public interface::Delegate,
        public interface::EventDelegateStatus {

public:
    Dashboard( int numCols);
    virtual ~Dashboard();
    void Update();
    void ReceiveMessage(event::Event&);
    void ReceiveEventDelegateStatus(event::Event&);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    std::vector<scenes::AnimatedRectangle> shapes;
    int rotate;
    objects::Progressbar messageBar;

};

} /* namespace objects */

#endif /* BARDIAGRAMS_H_ */
