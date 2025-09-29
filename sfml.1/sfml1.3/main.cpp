#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Convex Shapes");
    window.clear(sf::Color::White);

    sf::RectangleShape chimneyLower;
    chimneyLower.setFillColor(sf::Color(59, 56, 56));
    chimneyLower.setPosition({ 450, 240 });
    chimneyLower.setSize({ 40, 75 });
    window.draw(chimneyLower);

    sf::RectangleShape chimneyUpper;
    chimneyUpper.setFillColor(sf::Color(59, 56, 56));
    chimneyUpper.setPosition({ 437, 200 });
    chimneyUpper.setSize({ 65, 40 });
    window.draw(chimneyUpper);

    sf::CircleShape smoke1(18);
    smoke1.setFillColor(sf::Color(191, 191, 191));
    smoke1.setPosition({ 465, 166 });
    window.draw(smoke1);

    sf::CircleShape smoke2(20);
    smoke2.setFillColor(sf::Color(191, 191, 191));
    smoke2.setPosition({ 473, 140 });
    window.draw(smoke2);

    sf::CircleShape smoke3(25);
    smoke3.setFillColor(sf::Color(191, 191, 191));
    smoke3.setPosition({ 485, 110 });
    window.draw(smoke3);

    sf::CircleShape smoke4(30);
    smoke4.setFillColor(sf::Color(191, 191, 191));
    smoke4.setPosition({ 495, 78 });
    window.draw(smoke4);

    sf::RectangleShape house;
    house.setFillColor(sf::Color(77, 46, 11));
    house.setPosition({ 200, 350 });
    house.setSize({ 400, 200 });
    window.draw(house);

    sf::RectangleShape door;
    door.setFillColor(sf::Color(0, 0, 0));
    door.setPosition({ 250, 410 });
    door.setSize({ 50, 140 });
    window.draw(door);

    sf::ConvexShape roof;
    roof.setFillColor(sf::Color(93, 30, 23));
    roof.setPosition({ 200, 250 });
    roof.setPointCount(4);
    roof.setPoint(0, { 90, 0 });
    roof.setPoint(1, { 400 - 90, 0 });
    roof.setPoint(2, { 400 + 30, 100 });
    roof.setPoint(3, { -30, 100 });
    window.draw(roof);

    window.display();

    sf::sleep(sf::seconds(5));
}