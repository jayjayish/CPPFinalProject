#include "Precompiled.h"
#include "Time.h"
#include "AudioManager.h"
#include "RythmnMapManager.h"

constexpr const int k_WindowWidth = 1920;
constexpr const int k_WindowHeight = 1014;

void RenderKeys(sf::RenderWindow& window);
void RenderButton(sf::RenderWindow& window);
void UpdateWindow(sf::RenderWindow& window);
void OnStartGame();
void ModifyOffset();
void UpdateGameLogic();
bool InMenu = true;
bool OffsetCreated = false;
int lastBPM = 4;
sf::Font m_Font;

int main()
{
	sf::RenderWindow window(sf::VideoMode(k_WindowWidth, k_WindowHeight), "IT IS ALIVE!", sf::Style::Titlebar | sf::Style::Close);

	RythmnMapManager manager;
	manager.Instance().LoadMap("Resources/NeeNeeNee.txt");

	AudioManager audioManager;
	audioManager.Instance().Initialize();

	if (!m_Font.loadFromFile("Resources/arial.ttf"))
	{
		throw "Font file not found";
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		UpdateGameLogic();
		UpdateWindow(window);
		window.display();
	}

	return 0;
}

void UpdateWindow(sf::RenderWindow& window)
{
	if (InMenu)
	{
		RenderButton(window);
	}
	else
	{
		RenderKeys(window);
	}
}

void RenderButton(sf::RenderWindow& window)
{
	float buttonWidth = 360.0f;
	float buttonHeight = 100.0f;

	sf::RectangleShape shape(sf::Vector2f(buttonWidth, buttonHeight));
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1.0f);
	shape.setPosition(sf::Vector2f(k_WindowWidth / 2.0 - buttonWidth / 2.0, k_WindowHeight / 2.0 - buttonHeight / 2.0));
	shape.setFillColor(sf::Color::White);
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	sf::Text text("Start Game", m_Font, 50);
	text.setFillColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(k_WindowWidth / 2.0 - buttonWidth / 2.0 + 50.0, k_WindowHeight / 2.0 - buttonHeight / 2.0  + 15.0));


	window.draw(shape);

	window.draw(text);

	if (mousePos.x > k_WindowWidth / 2.0 && mousePos.x < (k_WindowWidth / 2.0 + buttonWidth) && 
		mousePos.y > k_WindowHeight / 2.0 && mousePos.y < (k_WindowHeight / 2.0 + buttonHeight) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		OnStartGame();
	}
}

void RenderKeys(sf::RenderWindow& window)
{
	Time timeClass;
	//if (timeClass.CalculateCurrentBeat() > lastBPM)
	//{
	//	AudioManager audioManager;
	//	audioManager.Instance().PlayHitSound();
	//	lastBPM += 1;
	//}

	float buttonWidth = 100.0f;
	float buttonHeight = 100.0f;
	float buttonHorizontalPosition = 200.0f;
	float buttonVerticalOffset = 200.f;
	sf::Color upperKeyColor = sf::Color::Cyan;
	sf::Color lowerKeyColor = sf::Color::Yellow;

	sf::RectangleShape upperKey(sf::Vector2f(buttonWidth, buttonHeight));
	upperKey.setOutlineColor(upperKeyColor);
	upperKey.setOutlineThickness(1.0f);
	upperKey.setPosition(sf::Vector2f(buttonHorizontalPosition, k_WindowHeight / 2.0 - buttonHeight / 2.0 - buttonVerticalOffset));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		std::cout << timeClass.CalculateCurrentBeat() << "\n";
	}
	else
	{
		upperKey.setFillColor(sf::Color::Black);
	}

	sf::RectangleShape lowerKey(sf::Vector2f(buttonWidth, buttonHeight));
	lowerKey.setOutlineColor(lowerKeyColor);
	lowerKey.setOutlineThickness(1.0f);
	lowerKey.setPosition(sf::Vector2f(buttonHorizontalPosition, k_WindowHeight / 2.0 - buttonHeight / 2.0 + buttonVerticalOffset));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
	{
		lowerKey.setFillColor(lowerKeyColor);
	}
	else
	{
		lowerKey.setFillColor(sf::Color::Black);
	}

	window.draw(upperKey);
	window.draw(lowerKey);


	
}


void OnStartGame()
{
	AudioManager audio;
	audio.Instance().PlayMusic();
	Time time;
	time.SetTimeStart();

	std::cout << "Game Started \n";
	InMenu = false;
}

void UpdateGameLogic()
{
	if (InMenu)
	{

	}
	else
	{
		ModifyOffset();
	}
}

void ModifyOffset()
{
	Time time;
	RythmnMapManager mapManager;
	if (!OffsetCreated && time.CalculateCurrentBeat() > mapManager.Instance().GetStartOffset())
	{
		time.SetTimeStart();
		OffsetCreated = true;
	}
}