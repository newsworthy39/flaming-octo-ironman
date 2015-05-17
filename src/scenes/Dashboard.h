/*
 * Bardiagrams.h
 *
 *  Created on: 11/05/2015
 *      Author: gandalf
 */

#ifndef DASHBOARD_H_
#define DASHBOARD_H_

#include <iostream>
#include <vector>
#include <json11/json11.hpp>
#include <interface/Observable.h>
#include <objects/AnimatedRectangle.h>
#include <objects/Progressbar.h>
#include <objects/RssItemLargePanel.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Network.hpp>

namespace scenes {

class Dashboard: public sf::Transformable,
        public sf::Drawable,
        public interface::Observable {

public:

    Dashboard();
    virtual ~Dashboard();
    void Update();
    void Refresh();
    void SetDimensions(sf::Vector2f dimensions);

    // Passing solution
    void ReceiveMessage(const event::Event&, json11::Json & data);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:

    objects::AnimatedRectangle m_animatedRectangle;
    objects::Progressbar m_messageBar;
    std::vector<objects::RssItemLargePanel*> m_RssMembers;
    sf::Vector2f m_dimensions;

};

} /* namespace objects */

#endif /* BARDIAGRAMS_H_ */
