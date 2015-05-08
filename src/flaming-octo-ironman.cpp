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

using namespace std;

sf::Mutex mutex;
sf::Http http;
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> dist(1, 6);

float radius = 200, animation = 200;
int isRunning = 1;
float x = 100.0f, y = 100.0f;

void PollRequest(int * isRunning) {

	http.setHost("http://force.mjay.me");

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

		mutex.lock();
		// Store the previous.
		animation = radius;

		// The next.
		radius = std::stoi(response.getBody());

		mutex.unlock();

		sf::sleep(sf::seconds(dist(mt)));
	}
}

int main() {

	sf::Thread thread(std::bind(&PollRequest, &isRunning));
	thread.launch();

	sf::ContextSettings context;
	context.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!",
			sf::Style::Default, context);

	sf::CircleShape shape((float) radius);
	shape.setFillColor(sf::Color(16,16,16));
	shape.setPointCount(64);

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


		mutex.lock();
		animation = std::min(radius, animation) - std::max(radius, animation) ; // => DeltaRadius = max - min, ie. 190 - 103
		shape.setRadius(radius + (animation / 8));
		animation = animation / 8;
		mutex.unlock();

		shape.setFillColor(sf::Color(255,16,16));

		shape.setPosition(sf::Vector2f(std::sqrt(radius), std::sqrt(radius)));

		window.clear(sf::Color::Black);
		window.draw(shape);
		window.display();
	}

	thread.wait();

	return 0;
}
