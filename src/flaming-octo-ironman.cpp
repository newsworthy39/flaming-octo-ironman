/**
 * Author: newsworthy39
 * Documentation: http://www.sfml-dev.org/documentation/2.2/
 */

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!",
            sf::Style::Default, settings);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                // left key is pressed: move our character
                shape.move(1, 0);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                // left key is pressed: move our character
                shape.move(-1, 0);
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
