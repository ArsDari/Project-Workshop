#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

constexpr unsigned int circleSize = 75;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 500 }), "Rectangles and circle");
    
    window.clear(sf::Color(0x80, 0x80, 0x80));

    sf::RectangleShape letterD_o;
    letterD_o.setSize({25, 300});
    letterD_o.setPosition({25, 25});
    sf::RectangleShape letterD_l;
    letterD_l.setSize({25, 180});
    letterD_l.setPosition({30, 50});
    letterD_l.setRotation(sf::degrees(-30));
    sf::RectangleShape letterD_u;
    letterD_u.setSize({25, 170});
    letterD_u.setPosition({50, 325});
    letterD_u.setRotation(sf::degrees(-150));

    sf::RectangleShape letterA_o;
    letterA_o.setPosition({300, 25});
    letterA_o.setSize({25, 275});
    letterA_o.setRotation(sf::degrees(15));
    sf::RectangleShape letterA_b;
    letterA_b.setPosition({300, 25});
    letterA_b.setSize({25, 275});
    letterA_b.setRotation(sf::degrees(-15));
    sf::RectangleShape letterA_c;
    letterA_c.setPosition({270, 200});
    letterA_c.setSize({100, 25});

    sf::RectangleShape letterD_o_a;
    letterD_o_a.setSize({25, 300});
    letterD_o_a.setPosition({25 + 500, 25});
    sf::RectangleShape letterD_l_a;
    letterD_l_a.setSize({25, 180});
    letterD_l_a.setPosition({30 + 500, 50});
    letterD_l_a.setRotation(sf::degrees(-30));
    sf::RectangleShape letterD_u_a;
    letterD_u_a.setSize({25, 170});
    letterD_u_a.setPosition({50 + 500, 325});
    letterD_u_a.setRotation(sf::degrees(-150));

    window.draw(letterD_o);
    window.draw(letterD_l);
    window.draw(letterD_u);
    window.draw(letterA_o);
    window.draw(letterA_b);
    window.draw(letterA_c);
    window.draw(letterD_o_a);
    window.draw(letterD_l_a);
    window.draw(letterD_u_a);

    window.display();

    sf::sleep(sf::seconds(5));
}