/*
 * Progressbar.cpp
 *
 *  Created on: 12/05/2015
 *      Author: gandalf
 */

#include <objects/Progressbar.h>

namespace objects {

Progressbar::Progressbar() {
	font.loadFromFile(
			"/home/gandalf/git/flaming-octo-ironman/src/font/Roboto-Light.ttf");

	tekst.setFont(font);
	tekst.setString("0");
	tekst.setCharacterSize(20);
	tekst.setColor(sf::Color(0, 0, 0));
	messageLoader.setFillColor(sf::Color(163, 38, 38));
}

Progressbar::~Progressbar() {
	// TODO Auto-generated destructor stub
}

void Progressbar::Update() {

	tekst.setPosition(this->getPosition());
	messageLoader.setPosition(this->getPosition() + sf::Vector2f(0, 40));
}

void Progressbar::draw(sf::RenderTarget& target,
		sf::RenderStates states) const {

	target.draw(this->tekst, states);
	target.draw(this->messageLoader, states);
}

void Progressbar::SetValue(int value) {
	messageLoader.setSize(sf::Vector2f(std::min(500, value), 10));
	tekst.setString(std::to_string(value));
}

int Progressbar::GetValue() {
	return this->messageLoader.getSize().x;
}

} /* namespace objects */
