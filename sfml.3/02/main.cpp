#include <SFML/Graphics.hpp>
#include <iostream>

static void pollEvents(sf::RenderWindow& window) {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			std::cout
				<< "mouse pressed,"
				<< " x=" << mouseButtonPressed->position.x
				<< " y=" << mouseButtonPressed->position.y
				<< std::endl;
		}
		if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
			std::cout
				<< "mouse released,"
				<< " x=" << mouseButtonReleased->position.x
				<< " y=" << mouseButtonReleased->position.y
				<< std::endl;
		}
	}
}

static void redrawFrame(sf::RenderWindow& window) {
	window.clear();
	window.display();
}

int main() {
	constexpr unsigned WINDOW_WIDTH = 800;
	constexpr unsigned WINDOW_HEIGHT = 600;

	sf::RenderWindow window(
		sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
		"Prints mouse events to terminal"
	);

	while (window.isOpen()) {
		pollEvents(window);
		redrawFrame(window);
	}
}