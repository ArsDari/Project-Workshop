#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

constexpr unsigned int circleSize = 75;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 190, 530 }), "Rectangles and circle");
    
    window.clear(sf::Color(0x80, 0x80, 0x80));

    sf::CircleShape greenLight(circleSize);
    greenLight.setFillColor(sf::Color::Green);
    greenLight.setPosition({ 20, 20 });

    sf::CircleShape yellowLight(circleSize);
    yellowLight.setFillColor(sf::Color::Yellow);
    yellowLight.setPosition({ 20, 190 });

    sf::CircleShape redLight(circleSize);
    redLight.setFillColor(sf::Color::Red);
    redLight.setPosition({ 20, 360 });

    window.draw(greenLight);
    window.draw(yellowLight);
    window.draw(redLight);

    window.display();

    sf::sleep(sf::seconds(5));
}