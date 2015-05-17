/**
 * Author: newsworthy39
 *
 * The color-scheme, used here-in is at:
 *   http://paletton.com/#uid=7000u0kwi++bu++hX++++rd++kX
 * The SFML documentation, is located at:
 *   Documentation: http://www.sfml-dev.org/documentation/2.2/
 * The json11 library used here-in is:
 *   https://github.com/dropbox/json11, Copyright (c) 2013 Dropbox, Inc.
 *
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <random>
#include <event/JSONThreadedPoller.h>
#include <scenes/Dashboard.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <X11/Xlib.h>

// FIXME: Screen width and height, should not de a static compile.
#define SCREEN_W 1280
#define SCREEN_H 720

int main() {

	// initialize X11
	if (0 == XInitThreads()) {
		std::cerr << "Threads are not supported, on this platform, aborting."
				<< std::endl;
		exit(-1);
	}

	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "Flaming-octo-ironman",
			sf::Style::Close, context);

	window.setFramerateLimit(60);

	// Jsonthreaded poller
	events::JSONThreadedPoller poller("http://ubuntu64bit-msgstack00.lan", 9999);

	// Objects used, here-in.
	scenes::Dashboard dashboard(sf::Vector2f(20,20));
	dashboard.SetDimensions(sf::Vector2f(SCREEN_W, SCREEN_H));
	dashboard.Refresh();

	// Add callback, to objects, to receive events.
	poller.AddObserver(dashboard);

	// Start json-poller.
	poller.Start();

	// Begin rendering-loop.
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
				poller.Stop();
			}

			// Fake, an overall event. (synchron)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
			    dashboard.Refresh();
			}

			if (event.type == sf::Event::Resized) {
#ifdef __DEBUG__
			    std::cout << "The window was resized" << std::endl;
#endif
			    dashboard.SetDimensions((sf::Vector2f)window.getSize());
			    //dashboard.Refresh();
			}
		}

		// FIXME: Integrate, this into a state-machine, accepting scene-objects.
		dashboard.Update();

		// We like our color-scheme.
		//window.clear(sf::Color(89, 217, 217));
		window.clear(sf::Color(0,0,0));

		// FIXME: Integrate, this into a state-machine, accepting scene-objects.
		window.draw(dashboard);

		// Show display.
		window.display();
	}

	// make entirely sure.
	poller.Stop();

	return 0;
}
