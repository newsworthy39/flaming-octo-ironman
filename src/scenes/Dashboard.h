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
#include <objects/AnimatedRectangle.hpp>
#include <objects/Progressbar.hpp>
#include <objects/LargeImagePanel.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>

namespace scenes {

class Dashboard: public sf::Transformable,
        public sf::Drawable,
        public interface::Observable {

public:

    Dashboard();
    virtual ~Dashboard();
    void Update();
    void AsyncRefresh();
    void SetDimensions(sf::Vector2f dimensions);

    // Passing solution
    void ReceiveMessage(const event::Event&, json11::Json & data);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    unsigned int m_panelDisplayCounter;
    std::vector<objects::LargeImagePanel*> m_LargePanelImages;

    objects::AnimatedRectangle m_animatedRectangle;
    objects::Progressbar m_messageBar;
    sf::Vector2f m_dimensions;
    sf::Clock m_wallclock;
    sf::Font m_font_h1;
    sf::Text m_clock;

};

} /* namespace objects */

#endif /* BARDIAGRAMS_H_ */
