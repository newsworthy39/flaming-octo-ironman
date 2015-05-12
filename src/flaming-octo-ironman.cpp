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

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <X11/Xlib.h>
#include <event/JSONThreadedPoller.h>
#include <scenes/Dashboard.h>

#define SCREEN_W 640
#define SCREEN_H 480

int main() {

	// initialize X11
	if (0 == XInitThreads()) {
		std::cerr << "Threads are not supported, on this platform, abortin."
				<< std::endl;
		exit(-1);
	}

	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "SFML works!",
			sf::Style::Close, context);

	window.setFramerateLimit(60);

	// Jsonthreaded poller
	events::JSONThreadedPoller poller("http://force.mjay.me", 80);

	// Objects used, here-in.
	scenes::Dashboard dashboard(SCREEN_W);

	// Add callback, to objects, to receive events.
	poller.AddDelegate(dashboard);
	poller.AddEventStatusDelegate(dashboard);

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
		}

		// FIXME: Integrate, this into a state-machine, accepting scene-objects.
		dashboard.Update();


		// We like our color-scheme.
		window.clear(sf::Color(89, 217, 217));

		// FIXME: Integrate, this into a state-machine, accepting scene-objects.
		window.draw(dashboard);

		// Show display.
		window.display();
	}

	// make entirely sure.
	poller.Stop();

	return 0;
}
