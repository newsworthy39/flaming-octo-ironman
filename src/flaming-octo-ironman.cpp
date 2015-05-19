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
#define SCREEN_W 3840
#define SCREEN_H 1080
#define FULLSCREEN true
#endif

int main() {

    // initialize X11
    if (0 == XInitThreads()) {
        std::cerr << "Threads are not supported, on this platform, aborting."
                << std::endl;
        exit(-1);
    }

    sf::ContextSettings context;
    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H),
            "Flaming-octo-ironman",
            FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Close, context);

    window.setMouseCursorVisible(!FULLSCREEN);
//    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    // Jsonthreaded poller
    events::JSONThreadedPoller poller("http://localhost", 9000);

    // Objects used, here-in.
    scenes::Dashboard dashboard;
    dashboard.setPosition(sf::Vector2f(20, 20));
    dashboard.SetDimensions(sf::Vector2f(SCREEN_W, SCREEN_H));
    dashboard.UpdateDataAsync();

    // Add callback, to objects, to receive events.
    poller.AddObserver(dashboard);

    // Start json-poller.
    poller.Start();

    // update the view to the new size of the window
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
        //window.clear(sf::Color(89, 217, 217));
        window.clear(sf::Color(0, 0, 0));

        #ifdef __DEBUG__
        // FIXME: Integrate, this into a state-machine, accepting scene-objects.
        // let's define a view
        // Draw shit in it.
        window.draw(dashboard);

        // Show display.
        window.display();
#else

        // Production multi-screen display (twinview primarly nvidia)
        // let's define a view
        sf::View leftmonitor(viewRect);
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

        // Draw shit in it.
        window.draw(dashboard);

        // Show display.
        window.display();
#endif
    }

    // make entirely sure.
    poller.Stop();

    return 0;
}
