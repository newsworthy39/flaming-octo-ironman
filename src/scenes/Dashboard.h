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
#include <random>
#include <chrono>

#include <json11/json11.hpp>
#include <interface/DrawablePanel.hpp>
#include <interface/Observable.hpp>
#include <panels/Progressbar.hpp>
#include <panels/LargeImagePanel.hpp>
#include <panels/SmallImagePanel.hpp>
#include <panels/LogPanel.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>

namespace scenes {

class Dashboard: public interface::Observable, public sf::Transformable, public sf::Drawable{

public:
    Dashboard(const std::string host, int port);
    virtual ~Dashboard();

    // Necessary, components.
    void UpdateGraphics(sf::FloatRect&);
    void UpdateDataAsync();
    void SetDimensions(sf::Vector2f dimensions);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void AddPanelToFront(interface::DrawablePanel* p);
    void AddPanelToBack(interface::DrawablePanel* p);

    // Passing solution, from interface::Observable
    void ReceiveMessage(const event::Event&, json11::Json & data);

protected:
    void SetBasepath(std::string basepath);
    virtual void onDataUpdate(const json11::Json & data);

private:
    std::string GetBasepath();
    void updateClock();
    void _updateDataAsync(std::string & str);
    float prevValue, m_viewportPositionX;
    unsigned int m_paneldisplaycounter;
    std::vector<interface::DrawablePanel*> m_largepanelimages;
    //objects::AnimatedRectangle m_animatedRectangle;
    panels::Progressbar m_progressbar;
    sf::Vector2f m_dimensions;
     sf::Font m_font_h1;
    sf::Text m_clock;
    std::string m_host;
    int m_port;
    sf::Clock m_wallclock;
    std::string m_basepath;
};
} /* namespace objects */

#endif /* BARDIAGRAMS_H_ */
