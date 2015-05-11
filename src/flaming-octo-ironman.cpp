/**
 * Author: newsworthy39
 * Documentation: http://www.sfml-dev.org/documentation/2.2/
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <random>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "AnimatedRectangle.h"
#include "json11/json11.hpp"

sf::Http http;
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> dist(3, 7);

int isRunning = 1;

std::vector<objects::AnimatedRectangle> shapes(50);
sf::String tekst;
sf::RectangleShape messageLoader;

void PollRequest(int * isRunning) {

	http.setHost("http://force.mjay.me");

	int rotate = 0;
	int lompartTimestamp = 9999999;

	/**
	 * Let two threads, share the lompartTimestamp (jikes!)
	 * Use a polling-thread, that runs at its own pace, then
	 * update the lompart-timestamp. Let the second thread,
	 * read the messages.
	 * Pass the same http-connection along, as it might be
	 * necessary to do a protocol upgrade.
	 */
	while (*isRunning == 1) {

		// Start by sleeping it off.
		sf::sleep(sf::seconds(dist(mt)));

		// Actually do the requests.
		sf::Http::Request request;

		request.setMethod(sf::Http::Request::Method::Get);

		request.setUri("/msg.php");

		request.setHttpVersion(1, 0); // HTTP 1.1

		request.setField("X-lompart-Token", std::to_string(lompartTimestamp));

		sf::Http::Response response = http.sendRequest(request);

#ifdef __DEBUG__
		std::cout << "status: " << response.getStatus() << std::endl;
		std::cout << "HTTP version: " << response.getMajorHttpVersion() << "."
				<< response.getMinorHttpVersion() << std::endl;
		std::cout << "Content-Type header:" << response.getField("Content-Type")
				<< std::endl;
		std::cout << "body: " << response.getStatus() << std::endl;

		std::cout << "Response: " << response.getBody() << std::endl;
#endif

		/*
		 * This block determines if the timestamp has changed, and if its necessary
		 * to fetch the messages.
		 */
		int value = 0;
		if (response.getBody() != "") {


			const std::string simple_test = response.getBody();
			//R"({"k1":"v1", "k2":42, "k3":["a",123,true,false,null]})";
			std::string err;
			auto json = json11::Json::parse(simple_test, err);
			value = json["lompartToken"].int_value();

		} else {
			value = lompartTimestamp;
		}

		// If this increases, then it was updated. Do something.
		if (value > lompartTimestamp) {

			// Now. How many messages, do we need to fetch?
			int numMessages = value - lompartTimestamp;

			for (int i = 0; i < numMessages; i++) {

				// double check if, we're still running
				if (*isRunning == 0)
					break;

				sf::Http::Request request;

				request.setMethod(sf::Http::Request::Method::Get);

				request.setUri("/getmsg.php");

				request.setHttpVersion(1, 0); // HTTP 1.1

				request.setField("X-lompart-Token",
						std::to_string(lompartTimestamp + i));

				sf::Http::Response response = http.sendRequest(request);

#ifdef __DEBUG__
				std::cout << "status: " << response.getStatus() << std::endl;
				std::cout << "HTTP version: " << response.getMajorHttpVersion()
						<< "." << response.getMinorHttpVersion() << std::endl;
				std::cout << "Content-Type header:"
						<< response.getField("Content-Type") << std::endl;
				std::cout << "body: " << response.getStatus() << std::endl;

				std::cout << "(fetched data) Response: " << response.getBody()
						<< std::endl;

#endif
				if (response.getStatus() != 404) {

					const std::string test2 = response.getBody();
					//R"({"k1":"v1", "k2":42, "k3":["a",123,true,false,null]})";

					std::string err;
					auto json = json11::Json::parse(test2, err);

					//std::cout << "k1: " << json["tekst"].string_value() << "\n";
			//		std::cout << "k3: " << json["k3"].dump() << "\n";

		//			for (auto &k : json["k3"].array_items()) {
	//					std::cout << "    - " << k.dump() << "\n";
//					}

					/*
					 * This section, should probably be replaced, with a json-parser, that
					 * reads and parses the message-structures, and creates the appropriate
					 * objects for delegation. Use virtual, to let the compiler decide, via
					 * its interface.
					 */

					int value = json["lompartToken"].int_value();

					shapes[rotate++ % shapes.size()].setValue(value);

					// 'Demo-purpose only.
					messageLoader.setSize(sf::Vector2f(numMessages - i, 10));

					tekst = std::to_string(numMessages - i);
					//tekst = std::to_string();
				}
			}
		}

		// Allways, end on the lighter side :)
		lompartTimestamp = value; // update the value, so we don't fetch it several times.
	}
}

int main() {

	sf::Thread thread(std::bind(&PollRequest, &isRunning));

	sf::ContextSettings context;

	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(1980, 1024), "SFML works!",
			sf::Style::Fullscreen, context);

	window.setFramerateLimit(60);

	for (std::vector<objects::AnimatedRectangle>::size_type i = 0;
			i != shapes.size(); i++) {
		shapes[i].setHorizontalOffset((1 + i) * 20);
	}

	sf::Text text;
	sf::Font font;
	font.loadFromFile(
			"/home/gandalf/git/flaming-octo-ironman/src/font/Roboto-Light.ttf");

	text.setFont(font);
	text.setCharacterSize(20);
	text.setColor(sf::Color(0, 0, 0));
	text.setPosition(sf::Vector2f(20, 440));

	messageLoader.setPosition(sf::Vector2f(20, 400));
	messageLoader.setFillColor(sf::Color(163, 38, 38));

	// Start it.
	thread.launch();
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
				isRunning = 0;
				thread.wait();
			}
		}

		for (std::vector<objects::AnimatedRectangle>::iterator it =
				shapes.begin(); it != shapes.end(); ++it) {
			(*it).Update();
		}

		text.setString(tekst);

		window.clear(sf::Color(89, 217, 217));
		window.draw(text);
		window.draw(messageLoader);

		for (std::vector<objects::AnimatedRectangle>::iterator it =
				shapes.begin(); it != shapes.end(); ++it) {
			window.draw(*it);
		}

		// Show display.
		window.display();
	}

	thread.wait();

	return 0;
}
