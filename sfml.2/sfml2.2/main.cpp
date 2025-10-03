#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr int pointCount = 200;
constexpr sf::Vector2u windowSize{ 800, 600 };

int main() {
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	sf::RenderWindow window(
		sf::VideoMode(windowSize), "Polar Rose", sf::Style::Default,
		sf::State::Windowed, settings
	);

	sf::ConvexShape rose;
	sf::Color crimson{ 0xE3, 0x26, 0x36 };
	rose.setFillColor(crimson);

	rose.setPointCount(pointCount);
	for (int pointNo = 0; pointNo < pointCount; ++pointNo) {
		float angle = float(2 * M_PI * pointNo) / float(pointCount);
		const float radius = 200 * sin(6 * angle);
		sf::Vector2f point = sf::Vector2f{
			radius * std::sin(angle),
			radius * std::cos(angle)
		};
		rose.setPoint(pointNo, point);
	}

	const float orbitRadius = 100.f;
	const float orbitSpeed = 1.f;
	float orbitAngle = 0.f;
	sf::Clock clock;

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		float deltaTime = clock.restart().asSeconds();
		orbitAngle += orbitSpeed * deltaTime;

		sf::Vector2f offset{
			orbitRadius * std::cos(orbitAngle),
			orbitRadius * std::sin(orbitAngle)
		};
		sf::Vector2f windowCenter{ windowSize.x / 2, windowSize.y / 2 };
		rose.setPosition(windowCenter + offset);
		rose.rotate(sf::radians(deltaTime * M_PI_2));

		window.clear();
		window.draw(rose);
		window.display();
	}
}