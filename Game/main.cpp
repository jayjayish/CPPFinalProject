#include "Precompiled.h"
#include "Time.h"
#include "AudioManager.h"
#include "RythmnMapManager.h"
#include "NoteManager.h"
#include "GlobalConstants.h"


void RenderKeys(sf::RenderWindow& window);
void RenderMainMenu(sf::RenderWindow& window);
void UpdateWindow(sf::RenderWindow& window);
void OnStartGame();
void StartGameDelay();
void UpdateGameLogic();
bool InMenu = true;
bool OffsetCreated = false;
bool GameStarted = false;
bool MusicStarted = false;
bool LastUpdateUpperKeyPressed = false;
bool LastUpdateLowerKeyPressed = false;
sf::Font m_Font;

int main()
{
	sf::RenderWindow window(sf::VideoMode(k_WindowWidth, k_WindowHeight), "IT IS ALIVE!", sf::Style::Titlebar | sf::Style::Close);

	RythmnMapManager manager;
	manager.LoadMap("Resources/NeeNeeNee.txt");

	AudioManager audioManager;
	audioManager.Instance().Initialize();

	if (!m_Font.loadFromFile("Resources/arial.ttf"))
	{
		throw "Font file not found";
	}

	std::cout << "Resources Loaded\n";
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
		RenderMainMenu(window);
	}
	else
	{
		RenderKeys(window);
		NoteManager noteManager;
		noteManager.DrawNotes(window);
	}
}

void UpdateGameLogic()
{
	if (InMenu)
	{

	}
	else if (!MusicStarted && GameStarted)
	{
		StartGameDelay();
	}

	if (GameStarted)
	{
		KeyPressOnFrame keyPress;
		keyPress.Update();
		NoteManager noteManager;
		noteManager.UpdateNoteTracks();
	}
}


void RenderMainMenu(sf::RenderWindow& window)
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

	if (mousePos.x > k_WindowWidth / 2.0 - buttonWidth / 2.0 && mousePos.x < (k_WindowWidth / 2.0 + buttonWidth / 2.0) &&
		mousePos.y > k_WindowHeight / 2.0 - buttonHeight / 2.0 && mousePos.y < (k_WindowHeight / 2.0 + buttonHeight / 2.0) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		OnStartGame();
	}
}

void RenderKeys(sf::RenderWindow& window)
{
	sf::RectangleShape upperKey(sf::Vector2f(k_KeyButtonWidth, k_KeyButtonHeight));
	upperKey.setOutlineColor(sf::Color::Cyan);
	upperKey.setOutlineThickness(1.0f);
	upperKey.setPosition(sf::Vector2f(k_KeyHorizontalPosition, k_WindowHeight / 2.0 - k_KeyButtonHeight / 2.0 - k_KeyVerticalOffset));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		upperKey.setFillColor(sf::Color::Cyan);
	}
	else
	{
		upperKey.setFillColor(sf::Color::Black);
	}

	sf::RectangleShape lowerKey(sf::Vector2f(k_KeyButtonWidth, k_KeyButtonHeight));
	lowerKey.setOutlineColor(sf::Color::Yellow);
	lowerKey.setOutlineThickness(1.0f);
	lowerKey.setPosition(sf::Vector2f(k_KeyHorizontalPosition, k_WindowHeight / 2.0 - k_KeyButtonHeight / 2.0 + k_KeyVerticalOffset));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
	{
		lowerKey.setFillColor(sf::Color::Yellow);
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
	Time time;
	time.SetTimeStart();

	std::cout << "Game Started \n";
	InMenu = false;
	GameStarted = true;
}

void StartGameDelay()
{
	Time time;
	RythmnMapManager manager;
	if (time.CalculateCurrentBeat() > k_BeatDelay - manager.GetStartOffset())
	{
		MusicStarted = true;

		AudioManager audio;
		audio.Instance().PlayMusic();
	}
}


