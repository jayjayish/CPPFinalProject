#include "Precompiled.h"
#include "SFML/Graphics.hpp"

void RenderSquare(sf::RenderWindow& window);

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 768), "IT IS ALIVE!", sf::Style::Default);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		RenderSquare(window);
		window.display();
	}

	return 0;
}

void RenderSquare(sf::RenderWindow& window)
{
	sf::RectangleShape shape(sf::Vector2f(100.0f, 100.0f));
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.0f);
	shape.setPosition(sf::Vector2f(10.0f, 10.0f));
	shape.setFillColor(sf::Color::Black);

	window.draw(shape);
}