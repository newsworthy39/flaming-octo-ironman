/*
 * Bardiagrams.cpp
 *
 *  Created on: 11/05/2015
 *      Author: gandalf
 */

#include <scenes/Dashboard.h>

namespace scenes {

Dashboard::Dashboard() {
	this->m_panelDisplayCounter = 0;
	this->m_LargePanelImages.resize(10);
}

void Dashboard::SetDimensions(sf::Vector2f dimensions) {
	this->m_dimensions = dimensions;
	this->m_messageBar.setPosition(
			sf::Vector2f(this->getPosition().x, this->m_dimensions.y - 60));
	this->m_animatedRectangle.setPosition(
			sf::Vector2f(this->getPosition().x, this->getPosition().y));
}

Dashboard::~Dashboard() {
	// TODO: Unregister stuff here.
}

void Dashboard::Refresh() {

	this->m_LargePanelImages.clear();

	sf::Http http("http://localhost", 9001);

	sf::Http::Request request;

	request.setMethod(sf::Http::Request::Method::Get);

	request.setUri("/view/dashboard-0?type=raw");

	request.setHttpVersion(1, 1); // HTTP 1.0

	request.setField("Connection", "Close");

	sf::Http::Response response = http.sendRequest(request);

	if (response.getStatus() == sf::Http::Response::Ok) {

		// foreach, that shit.
		std::string err;
		auto json = json11::Json::parse(response.getBody(), err);

#ifdef __DEBUG__
		std::cout << err << ", " << json.dump() << std::endl;
#endif

		objects::LargeImagePanel * p = new objects::LargeImagePanel();
		p->SetDimensions(this->m_dimensions);
		p->SetMediaPath(json["mediapath"].string_value());
		p->SetHeadline(json["headline"].string_value());
		p->SetTeaser(json["teaser"].string_value());
		p->SetByline(json["byline"].string_value());

		p->Refresh();

		this->m_LargePanelImages.push_back(p);

	}

	request.setMethod(sf::Http::Request::Method::Get);

	request.setUri("/view/dashboard-1?type=raw");

	request.setHttpVersion(1, 1); // HTTP 1.0

	request.setField("Connection", "Close");

	sf::Http::Response response1 = http.sendRequest(request);

	if (response1.getStatus() == sf::Http::Response::Ok) {

		// foreach, that shit.
		std::string err;
		auto json = json11::Json::parse(response1.getBody(), err);

#ifdef __DEBUG__
		std::cout << err << ", " << json.dump() << std::endl;
#endif

		objects::LargeImagePanel * p = new objects::LargeImagePanel();
		p->SetDimensions(this->m_dimensions);
		p->SetMediaPath(json["mediapath"].string_value());
		p->SetHeadline(json["headline"].string_value());
		p->SetTeaser(json["teaser"].string_value());
		p->SetByline(json["byline"].string_value());

		p->Refresh();


		this->m_LargePanelImages.push_back(p);

	}

}

/**
 * Dashboard::ReceiveEventDelegateStatus
 * Receives a message, when arrived.
 */
void Dashboard::ReceiveMessage(const event::Event& e, json11::Json & data) {
	switch (e) {
	case event::Event::MESSAGESPENDING: {
		this->m_messageBar.SetValue(data["messagespending"].int_value());

	}
		;
		break;

	case event::Event::MESSAGE: {
		std::string stringValue = data["message"].string_value();
		if (0 == stringValue.compare("update")) {
#ifdef __DEBUG__
			std::cout << "I was asked to do a full update" << std::endl;
#endif
			this->Refresh();
		}
	}
		;
		break;
	case event::Event::UPDATE: {
		this->Refresh();
	}

		break;
	}
}

void Dashboard::Update() {

	// this->m_ebdkimage.Update();

	/*
	 * So we're going to cheet. If the last restart is large than
	 * 30 seconds, pick a new panel.
	 */
	if (this->m_wallclock.getElapsedTime() >= sf::seconds(10)) {
		this->m_wallclock.restart();

		this->m_panelDisplayCounter = ++this->m_panelDisplayCounter
				% this->m_LargePanelImages.size();

		std::cout << "Wall clock change, changing panel [max]"
				<< this->m_LargePanelImages.size() << ", current " << this->m_panelDisplayCounter << std::endl;
	}

	for (objects::LargeImagePanel * p : this->m_LargePanelImages) {
		p->Update();
	}

	this->m_messageBar.Update();

	this->m_animatedRectangle.Update();
}

void Dashboard::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	//for (const objects::LargeImagePanel * p : this->m_LargePanelImages) {
	const objects::LargeImagePanel * p =
			this->m_LargePanelImages[this->m_panelDisplayCounter];
	target.draw(*p, states);
	//}

	target.draw(this->m_messageBar, states);
	target.draw(this->m_animatedRectangle, states);
}

} /* namespace objects */
