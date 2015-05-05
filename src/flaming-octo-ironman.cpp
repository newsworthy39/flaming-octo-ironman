/**
 * Author: newsworthy39
 * Documentation: http://www.sfml-dev.org/documentation/2.2/
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;

int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1980, 1024), "SFML works!",
            sf::Style::Default, settings);

    window.setFramerateLimit(60);

    sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(100,100), sf::Color::White),
            sf::Vertex(sf::Vector2f(100,100), sf::Color::White)
    };

    float degrees = 1.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();
        }

        degrees += 0.1f;

        line[1].position.x = 100 + (std::cos((2 * M_PI / 360 ) * degrees)*100);
        line[1].position.y = 100 + (std::sin((2 * M_PI / 360) * degrees)*100);

        window.clear();
        window.draw(line, 2, sf::Lines);
        window.display();
    }

    return 0;
}
