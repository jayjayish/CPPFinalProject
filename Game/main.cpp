#include "Precompiled.h"
#include "Time.h"
#include "AudioManager.h"
#include "RythmnMapManager.h"

constexpr const int k_WindowWidth = 1920;
constexpr const int k_WindowHeight = 1080;

sf::Clock Clock;

void RenderSquare(sf::RenderWindow& window);
void Update(sf::RenderWindow& window);
void BPMTemp();
int lastBPM = 0;

int main()
{
	sf::RenderWindow window(sf::VideoMode(k_WindowWidth, k_WindowHeight), "IT IS ALIVE!", sf::Style::Default);

	Time timeClass;
	RythmnMapManager manager;
	manager.Instance().LoadMap("Resources/NeeNeeNee.txt");
	std::cout << manager.Instance().GetNote(0).GetDuration() << "\n";

	AudioManager audioManager;
	audioManager.Instance().Initialize();
	Clock.restart();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		Update(window);
		window.display();
	}

	return 0;
}

void Update(sf::RenderWindow& window)
{
	RenderSquare(window);
	BPMTemp();
}


void RenderSquare(sf::RenderWindow& window)
{
	Time timeClass;
	double timeDiff = Clock.getElapsedTime().asSeconds();
	double sinVal = sin(timeDiff * 2 * 3.1415);
	sf::RectangleShape shape(sf::Vector2f(100.0f, 100.0f));
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.0f);
	shape.setPosition(sf::Vector2f(sinVal * k_WindowWidth / 2.0 + k_WindowWidth / 2.0, k_WindowHeight / 2.0));
	shape.setFillColor(sf::Color::Black);

	window.draw(shape);
}

void BPMTemp()
{
	Time timeClass;
	RythmnMapManager manager;
	std::cout << manager.Instance().GetBPM();
	if (timeClass.CalculateTimeDifference() > lastBPM)
	{
		AudioManager audioManager;
		audioManager.Instance().PlayHitSound();
		std::cout << "Hitsound\n";
		lastBPM += 1;
	}
}

