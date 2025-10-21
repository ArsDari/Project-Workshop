#define _USE_MATH_DEFINES
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string.h>
#include "constants.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define ONE_VECT sf::Vector2f({1, 0})
constexpr int SPRITE_WIDTH_CAT = 50 * 2;
constexpr int SPRITE_HEIGHT_CAT = 50 * 2;

constexpr int SPRITE_WIDTH_LASER = 38;
constexpr int SPRITE_HEIGHT_LASER = 35;

#define RIGHT 0
#define LEFT 1
#define DOWN 2
#define UP 3

struct Cat
{
	sf::Sprite catSprite;
	sf::Texture catTexture;
	sf::Vector2f position;
	int typeOfMovement;
};

struct Laser
{
	sf::Sprite laserSprite;
	sf::Texture laserTexture;
};

struct Game
{
	Cat cat;
	Laser laser;
	int SPS; //Sprite per second
	float currS;
	std::string state;
};

float toDegrees(float radians)
{
	return float(double(radians) * 180.0 / M_PI);
}

int getTypeOfMovement(sf::Vector2f delta) {
	float angle = toDegrees(atan2(delta.y, delta.x));
	// std::cout << angle << '|' << () <<  '|';
	if (-135 < angle && angle < -45) return UP;
	else if (135 > angle && angle > 45) return DOWN;
	else if ((-90 > angle && angle > -180) || (180 > angle && angle > 90)) return LEFT;
	else return RIGHT;
}

void onMouseClick(const sf::Event::MouseButtonPressed& event, sf::Vector2f& mousePosition, Game& game)
{
	if (event.button == sf::Mouse::Button::Left) {
		mousePosition = { float(event.position.x), float(event.position.y) };
		game.state = "GoToLaser";
		game.laser.laserSprite.setPosition(mousePosition);
		game.currS = 0;
		game.cat.typeOfMovement = getTypeOfMovement(mousePosition - game.cat.position);
	}
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition, Game& game)
{
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		if (const auto* mouseMoved = event->getIf<sf::Event::MouseButtonPressed>()) {
			onMouseClick(*mouseMoved, mousePosition, game);
		}
	}
}

void updatePosition(Cat& cat, float dfTime, sf::Vector2f delta) {
	if ((abs(delta.x) > 1 || abs(delta.y) > 1)) {
		sf::Vector2f directVector = delta.normalized();
		float deltaLen = sqrt(delta.x * delta.x + delta.y * delta.y);
		// std::cout << directVector.x << '|' << directVector.y << std::endl;

		float distance = SPEED_MOVEMENT * dfTime;
		cat.position += directVector * distance;
		cat.catSprite.setPosition(cat.position);
	}
}

void updateCatSprites(Game& game, int row, int column) {
	game.cat.catSprite.setTextureRect(sf::IntRect({ SPRITE_WIDTH_CAT * row, SPRITE_HEIGHT_CAT * column + 1 }, { SPRITE_WIDTH_CAT, SPRITE_HEIGHT_CAT }));
}

void movementCycle(Game& game, float dfTime, sf::Vector2f mousePosition) {
	sf::Vector2f delta = mousePosition - game.cat.position;

	updatePosition(game.cat, dfTime, delta);
	if (abs(delta.x) < 2 || abs(delta.y) < 2) { game.state = "Loyater"; }


	if (game.currS > 3) game.currS = 0;
	switch (game.cat.typeOfMovement)
	{
	case UP:
		std::cout << "UP" << std::endl;
		updateCatSprites(game, game.currS / 1, 1);
		break;
	case DOWN:
		std::cout << "DOWN" << std::endl;
		updateCatSprites(game, game.currS / 1, 0);
		break;
	case LEFT:
		std::cout << "LEFT" << std::endl;
		updateCatSprites(game, game.currS / 1, 2);
		game.cat.catSprite.setScale({ 1, 1 });
		break;
	case RIGHT:
		std::cout << "RIGHT" << std::endl;
		updateCatSprites(game, game.currS / 1, 2);
		game.cat.catSprite.setScale({ -1, 1 });
		break;

	default:
		break;
	}
}

void updateSPSWithState(Game& game) {
	if (game.state == "Loyater") {
		game.SPS = 1;
	}
	else {
		game.SPS = 6;
	}
}

void update(const sf::Vector2f& mousePosition, Game& game, sf::Clock& clock)
{
	const float dfTime = clock.restart().asSeconds();
	updateSPSWithState(game);
	// std::cout << game.SPS << std::endl;
	game.currS += game.SPS * dfTime;

	if (game.state == "GoToLaser") {
		movementCycle(game, dfTime, mousePosition);
	}
	else {
		if (game.currS > 1 && game.currS < 3) game.currS = 3;
		if (game.currS >= 4) game.currS = 0;
		updateCatSprites(game, game.currS / 1, 0);
	}
}

void redrawFrame(sf::RenderWindow& window, Cat& cat, Laser& laser)
{
	window.clear(sf::Color::White);
	window.draw(laser.laserSprite);
	window.draw(cat.catSprite);
	window.display();
}

void redrawFrame(sf::RenderWindow& window, Cat& cat)
{
	window.clear(sf::Color::White);
	window.draw(cat.catSprite);
	window.display();
}

void init(Game& game)
{
	game.cat.position = sf::Vector2f({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
	game.cat.catSprite.setPosition(game.cat.position);

	game.currS = 0;
	game.state = "Loyater";
}

int main() {
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 0;
	sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "prints mouse events to terminal", sf::Style::Default, sf::State::Windowed, settings);

	sf::Vector2f mousePosition;
	sf::Clock clock;

	sf::Texture catTexture;
	if (!catTexture.loadFromFile("./image.png"))
	{
		std::cout << "Невозможно открыть спрайт" << std::endl;
	}
	sf::Sprite catSprite{ catTexture, sf::IntRect(sf::Vector2i(0, 0), {SPRITE_WIDTH_CAT, SPRITE_HEIGHT_CAT}) };
	catTexture.setSmooth(false);
	catTexture.setRepeated(false);
	catSprite.setOrigin({ SPRITE_WIDTH_CAT / 2, SPRITE_HEIGHT_CAT / 2 });

	sf::Texture laserTexture;
	if (!laserTexture.loadFromFile("./image copy 2.png"))
	{
		std::cout << "Невозможно открыть спрайт" << std::endl;
	}
	sf::Sprite laserSprite(laserTexture, sf::IntRect({ 0, 0 }, { SPRITE_WIDTH_LASER, SPRITE_HEIGHT_LASER }));
	laserTexture.setSmooth(false);
	laserTexture.setRepeated(false);
	laserSprite.setOrigin({ SPRITE_WIDTH_LASER / 2, SPRITE_HEIGHT_LASER / 2 });

	Game game{ catSprite, catTexture, {0, 0}, RIGHT, laserSprite, laserTexture };
	init(game);
	while (window.isOpen())
	{
		pollEvents(window, mousePosition, game);
		update(mousePosition, game, clock);
		if (game.state == "GoToLaser") redrawFrame(window, game.cat, game.laser);
		else redrawFrame(window, game.cat);
	}

	return 0;
}