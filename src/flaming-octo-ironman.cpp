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
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim
 *  that you wrote the original software. If you use this software in a product,
 *  an acknowledgment in the product documentation would be appreciated but is
 *  not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Libraries used in SFML and here-in.
 * freetype is distributed under the FTL license or the GPL license
 * libjpeg is in the public domain
 * stb_image is in the public domain
 * OpenAL Soft is distributed under the LGPL license
 * libogg is distributed under the BSD 3 license
 * libvorbis is distributed under the BSD 3 license
 * libflac is distributed under the BSD 3 license
 *
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <random>
#include <ctime>
#include <event/JSONThreadedPoller.h>
#include <scenes/Dashboard.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <X11/Xlib.h>

// FIXME: Screen width and height, should not de a static compile.
#ifdef __DEBUG__
#define SCREEN_W 1600
#define SCREEN_H 900
#define FULLSCREEN false
#else
#define SCREEN_W 1920
#define SCREEN_H 1080
#define FULLSCREEN true
//#Define SPLITSCREEN
#endif

int main() {

	// initialize X11
	if (0 == XInitThreads()) {
		std::cerr << "Threads are not supported, on this platform, aborting."
				<< std::endl;
		exit(-1);
	}

	sf::ContextSettings context;

	sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H),
			"Flaming-octo-ironman",
			FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Close, context);

	window.setMouseCursorVisible(!FULLSCREEN);
//    window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	// Jsonthreaded poller
	events::JSONThreadedPoller poller("http://mjay.me", 9000);

	// Objects used, here-in.
	scenes::Dashboard dashboard("http://mjay.me", 9001);
	dashboard.setPosition(sf::Vector2f(20, 20));
	dashboard.SetDimensions(sf::Vector2f(SCREEN_W, SCREEN_H));
	dashboard.UpdateDataAsync();

	// Add callback, to objects, to receive events.
	poller.AddObserver(dashboard);

	// Start json-poller.
	poller.Start();

	/* FIXME: When running in FULLSCREEN Twin-monitor-mode (3580x1080)
	 * When viewRect isn't 3840x1080, its 1920x1080! Also, there are some
	 * calculations on locations, when using virtual screens that doesnt'
	 * entirely pan-out.
	 */
	sf::FloatRect viewRect(0, 0, SCREEN_W, SCREEN_H);

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
				dashboard.UpdateDataAsync();
			}

			if (event.type == sf::Event::Resized) {
#ifdef __DEBUG__
				std::cout << "The window was resized" << std::endl;
#endif
				dashboard.SetDimensions((sf::Vector2f) window.getSize());

			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				viewRect.left += 4.f;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				viewRect.left -= 4.f;
			}
		}

		// FIXME: Integrate, this into a state-machine, accepting scene-objects.
		dashboard.UpdateGraphics(viewRect);

		// We like our color-scheme, but black is purrrrty.
		window.clear(sf::Color(89, 217, 217));
		//window.clear(sf::Color(0, 0, 0));

#ifdef __DEBUG__
		sf::View v(viewRect);
		window.setView(v);

		// FIXME: Integrate, this into a state-machine, accepting scene-objects.
		// let's define a view
		// Draw shit in it.
		window.draw(dashboard);
#else
		// Production multi-screen display (twinview primarly nvidia)
		// let's define a view
		sf::View leftmonitor(viewRect);

#ifdef SPLITSCREEN
        leftmonitor.setViewport(sf::FloatRect(0, 0, 0.5, 1));

		// activate it
		window.setView(leftmonitor);

		// Draw shit in it.
		window.draw(dashboard);

		// FIXME: Integrate, this into a state-machine, accepting scene-objects.
		// let's define a view
		sf::View rightmonitor(viewRect);
		rightmonitor.setViewport(sf::FloatRect(0.5, 0, 0.5, 1));

		// activate it
		window.setView(rightmonitor);
#else
		window.setView(leftmonitor);
#endif

		// Draw shit in it.
		window.draw(dashboard);

#endif
		// Show display.
		window.display();
	}

	// make entirely sure.
	poller.Stop();

	return 0;
}
