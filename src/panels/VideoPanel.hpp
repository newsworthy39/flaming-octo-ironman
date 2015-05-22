/*
 * EBdkImage.h
 *
 *  Created on: 16/05/2015
 *      Author: gandalf
 */

#ifndef OBJECTS_VIDEOPANEL_H_
#define OBJECTS_VIDEOPANEL_H_

#include <iostream>
#include <string>
#include <interface/DrawablePanel.hpp>
#include <sfeMovie/Movie.hpp>

namespace panels {

class VideoPanel: public interface::DrawablePanel {
public:
    VideoPanel();
    virtual ~VideoPanel();

    // From DrawablePanel
    void UpdateGraphics(sf::FloatRect&);
    void UpdateDataAsync();
    const sf::Vector2f GetDimensions();
    void SetDimensions(sf::Vector2f);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void SetMediaPath(sf::String mediaPath);
private:
    sfe::Movie m_movie;
    sf::Vector2f m_dimensions;
    sf::String m_mediaPath;
};

} /* namespace objects */

#endif /* OBJECTS_RSSITEMLARGEPANEL_H_ */
