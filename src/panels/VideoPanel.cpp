/*
 * EBdkImage.cpp
 *
 *  Created on: 16/05/2015
 *      Author: gandalf
 */

#include <panels/VideoPanel.hpp>

namespace panels {

VideoPanel::VideoPanel() {

}

void VideoPanel::SetMediaPath(sf::String imagePath) {
    this->m_mediaPath = imagePath;
    this->m_movie.openFromFile(this->m_mediaPath);

}

void VideoPanel::SetDimensions(sf::Vector2f dimensions) {
    this->m_dimensions = dimensions;

    this->m_movie.fit(0, 0,
            dimensions.x, dimensions.y);
    this->m_movie.play();

}

const sf::Vector2f VideoPanel::GetDimensions() {
    return this->m_dimensions;
}

void VideoPanel::UpdateDataAsync() {

}

VideoPanel::~VideoPanel() {
    //
}

void VideoPanel::UpdateGraphics(sf::FloatRect& view) {
    this->m_movie.setPosition(this->getPosition().x, this->getPosition().y);
    this->m_movie.update();
}

void VideoPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->m_movie, states);
}

} /* namespace objects */

