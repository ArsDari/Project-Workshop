#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr float BALL_SIZE = 40;

constexpr float periodY = 2;

int main() {
	sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Wave Moving Ball");
	sf::Clock clock;
	float time = 0.f;

	const sf::Vector2f position = { 10, 350 };
	sf::Vector2f speed = { 100.f, 80.f };

	sf::CircleShape ball(BALL_SIZE);
	ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
	ball.setPosition(position);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		const float deltaTime = clock.restart().asSeconds();
		time += deltaTime;

		const float wavePhase = time * float(2 * M_PI);
		const float y = speed.y * std::sin(wavePhase / periodY);
		
		sf::Vector2f currentPosition = ball.getPosition();
		currentPosition.x += speed.x * deltaTime;
		currentPosition.y = position.y + y;

		if ((currentPosition.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed.x > 0)) {
			speed.x = -speed.x;
		}
		if ((currentPosition.x < 0) && (speed.x < 0)) {
			speed.x = -speed.x;
		}
		ball.setPosition(currentPosition);

		window.clear();
		window.draw(ball);
		window.display();
	}
}