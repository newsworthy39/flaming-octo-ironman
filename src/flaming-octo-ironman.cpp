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
std::uniform_real_distribution<double> dist(1, 9);

std::vector<objects::AnimatedRectangle> shapes(56);

sf::Text text;

int isRunning = 1;

void PollRequest(int * isRunning) {

    http.setHost("http://force.mjay.me");

    int rotate = 0;
    int lompartTimestamp = 9999999;

    while (*isRunning == 1) {

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
        int value = 0;

        if (response.getBody() != "") {
            value = std::stoi(response.getBody());
        } else {
            value = lompartTimestamp;
        }

        // If this increases, then it was updated. Do something.
        if (value > lompartTimestamp) {

            // Now. How many messages, do we need to fetch?
            int numMessages = value - lompartTimestamp;

            std::cout << "Will fetch " << numMessages << " messages." << std::endl;

            for (int i = 0; i < numMessages; i++) {

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
                    int value = std::stoi(response.getBody());
                    shapes[rotate++ % shapes.size()].setValue(value);
                }
            }

        }

        // Allways, end on the lighter side :)
        lompartTimestamp = value; // update the value, so we don't fetch it several times.

        /*text.setPosition(sf::Vector2f( ( rotate % shapes.size()) * 20 + 20, value));

         text.setString(std::to_string((int)value));

         text.setCharacterSize(std::max(32, std::min(64, (int) value)));
         */

        sf::sleep(sf::seconds(dist(mt)));
    }
}

int main() {

    sf::Thread thread(std::bind(&PollRequest, &isRunning));

    sf::ContextSettings context;

    context.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!",
            sf::Style::Close, context);

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

    text.setColor(sf::Color(35, 85, 85));

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

        window.clear(sf::Color(89, 217, 217));

        for (std::vector<objects::AnimatedRectangle>::iterator it =
                shapes.begin(); it != shapes.end(); ++it) {
            window.draw(*it);
        }

        // window.draw(text);

        //window.draw(text);
        window.display();
    }

    thread.wait();

    return 0;
}
