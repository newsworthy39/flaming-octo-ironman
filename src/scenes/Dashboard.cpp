/*
 * Bardiagrams.cpp
 *
 *  Created on: 11/05/2015
 *      Author: gandalf
 */

#include <scenes/Dashboard.h>

namespace scenes {

Dashboard::Dashboard(sf::Vector2f coords, sf::Vector2f dimensions) {
	this->setPosition(coords);
	this->dimensions = dimensions;
	this->messageBar.setPosition(sf::Vector2f(coords.x, dimensions.y - 50));
	this->animatedRectangle.setPosition(sf::Vector2f(coords.x, coords.y));
}

Dashboard::~Dashboard() {
	 // TODO: Unregister stuff here.
}

/**
 * Dashboard::ReceiveEventDelegateStatus
 * Receives a message, when arrived.
 */
void Dashboard::ReceiveMessage(const event::Event& e, json11::Json & data) {
	switch(e) {
		case event::Event::MESSAGESPENDING : {
			this->messageBar.SetValue(data["messagepending"].int_value());
		}; break;
		case event::Event::MESSAGE: {
			std::string stringValue = data["message"].string_value();
			std::cout << "Got " << stringValue << std::endl;
			//int intValue = data["message"].int_value();

			if (0 == stringValue.compare("websiteaccess")) {
				this->animatedRectangle.setValue(10);
			}
			//this->animatedRectangle.setValue(data["message"].int_value());
		}; break;
		case event::Event::UPDATE: {
			this->UpdateEverything();
		}; break;
	}
}

void Dashboard::Update() {
    this->messageBar.Update();
    this->animatedRectangle.Update();
}

void Dashboard::UpdateEverything() {
	std::cout << "Somebody, wanted to do a complete refresh" << std::endl;
}

void Dashboard::draw(sf::RenderTarget& target,
        sf::RenderStates states) const {
	target.draw(this->messageBar, states);
    target.draw(this->animatedRectangle, states);
}

} /* namespace objects */
