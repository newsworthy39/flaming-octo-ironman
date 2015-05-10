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

sf::Http http;
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> dist(1, 7);

std::vector<objects::AnimatedRectangle> shapes(99);

sf::Text text;

int isRunning = 1;

void PollRequest(int * isRunning) {

    http.setHost("http://force.mjay.me");
    int rotate = 0;

    while (*isRunning == 1) {
        sf::Http::Request request;

        request.setMethod(sf::Http::Request::Method::Post);
        request.setUri("/metrics.php");
        request.setHttpVersion(1, 0); // HTTP 1.1
        request.setField("X-HTTP-Token", "Yes");

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
        float value = std::stoi(response.getBody());

        shapes[rotate++ % shapes.size()].setValue(value);

        text.setPosition(sf::Vector2f(rotate * 20 + 20, value));

        text.setString(std::to_string((int)value));

        text.setCharacterSize(std::max(32, std::min(64, (int) value)));

        sf::sleep(sf::seconds(dist(mt)));
    }
}

int main() {

    sf::Thread thread(std::bind(&PollRequest, &isRunning));

    sf::ContextSettings context;

    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(1980, 1024), "SFML works!",
            sf::Style::None, context);

    window.setFramerateLimit(60);

    for (std::vector<objects::AnimatedRectangle>::size_type i = 0;
            i != shapes.size(); i++) {
        shapes[i].setHorizontalOffset((1 + i) * 20);
    }

    sf::Font font;

    font.loadFromFile(
            "/home/gandalf/workspace/flaming-octo-ironman/src/font/Roboto-Light.ttf");

    text.setFont(font);

    text.setCharacterSize(20);

    text.setPosition(sf::Vector2f(0, 0));

    text.setString("1");


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

        window.clear(sf::Color::Black);

        for (std::vector<objects::AnimatedRectangle>::iterator it =
                shapes.begin(); it != shapes.end(); ++it) {
            window.draw(*it);
        }

        window.draw(text);

        //window.draw(text);
        window.display();
    }

    thread.wait();

    return 0;
}
