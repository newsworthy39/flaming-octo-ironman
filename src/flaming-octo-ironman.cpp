/**
 * Author: newsworthy39
 * Documentation: http://www.sfml-dev.org/documentation/2.2/
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

using namespace std;

sf::Http http;

void PollRequest(int * memoryBucket, int * isRunning) {

	http.setHost("http://force.mjay.me");

	while (*isRunning == 1) {
		sf::Http::Request request;

		request.setMethod(sf::Http::Request::Method::Get);
		request.setUri("/metrics.php");
		request.setHttpVersion(1, 0); // HTTP 1.1
		request.setField("From", "me");

		sf::Http::Response response = http.sendRequest(request);
		std::cout << "status: " << response.getStatus() << std::endl;
		std::cout << "HTTP version: " << response.getMajorHttpVersion() << "."
				<< response.getMinorHttpVersion() << std::endl;
		std::cout << "Content-Type header:" << response.getField("Content-Type")
				<< std::endl;
		std::cout << "body: " << response.getStatus() << std::endl;

		std::cout << "Response: " << response.getBody() << std::endl;

		*memoryBucket = std::stoi(response.getBody());

		sf::sleep(sf::seconds(5));
	}
}

int main() {

	int radius = 200; int isRunning = 1;

	sf::Thread thread(std::bind(&PollRequest, &radius, &isRunning));

	thread.launch();

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	sf::CircleShape shape((float) radius);

	shape.setFillColor(sf::Color::Green);



	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				isRunning = 0;
				thread.wait();
			}
		}

		shape.setRadius(radius);

		window.clear();
		window.draw(shape);
		window.display();
	}

	thread.wait();

	return 0;
}
