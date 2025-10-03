#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr int pointCount = 200;
constexpr sf::Vector2f ellipseRadius = { 200.f, 80.f };

int main() {
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	sf::RenderWindow window(
		sf::VideoMode({ 800, 600 }), "Ellipse", sf::Style::Default,
		sf::State::Windowed, settings
	);

	sf::ConvexShape ellipse;
	ellipse.setPosition({ 400, 320 });
	ellipse.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

	ellipse.setPointCount(pointCount);
	for (int pointNo = 0; pointNo < pointCount; ++pointNo) {
		float angle = float(2 * M_PI * pointNo) / float(pointCount);
		sf::Vector2f point = sf::Vector2f{
			ellipseRadius.x * std::sin(angle),
			ellipseRadius.y * std::cos(angle)
		};
		ellipse.setPoint(pointNo, point);
	}

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		window.clear();
		window.draw(ellipse);
		window.display();
	}
}