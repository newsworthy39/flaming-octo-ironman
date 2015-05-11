/**
 * Author: newsworthy39
 * Documentation: http://www.sfml-dev.org/documentation/2.2/
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <random>


#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "AnimatedRectangle.h"
#include "JSONThreadedPoller.h"
#include "Bardiagrams.h"

#define SCREEN_W 1024
#define SCREEN_H 768
//
//sf::String tekst;
//
sf::RectangleShape messageLoader;

int main() {

    jsonevents::JSONThreadedPoller poller;

    sf::ContextSettings context;

    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), "SFML works!",
            sf::Style::Close, context);

    window.setFramerateLimit(60);

    objects::Bardiagrams diagrams ( ( SCREEN_W / 20 ) - 1 ) ;
    objects::Progressbar messageBar ();

    poller.AddDelegate(diagrams);
    poller.AddDelegate(messageBar);

//    sf::Text text;
//    sf::Font font;
//    font.loadFromFile(
//            "/home/gandalf/workspace/flaming-octo-ironman/src/font/Roboto-Light.ttf");
//
//    text.setFont(font);
//    text.setCharacterSize(20);
//    text.setColor(sf::Color(0, 0, 0));
//    text.setPosition(sf::Vector2f(20, 440));
//

    // Start it.
    poller.Start();

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
                poller.Stop();
            }
        }

        diagrams.Update();
        messageBar.Update();

       // text.setString(tekst);

        window.clear(sf::Color(89, 217, 217));

		window.draw(messageBar);
        window.draw(diagrams);

        // Show display.
        window.display();
    }

    // make entirely sure.
    poller.Stop();

    return 0;
}
