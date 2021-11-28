#include "Precompiled.h"
#include "Time.h"
#include "AudioManager.h"
#include "RythmnMapManager.h"
#include "NoteManager.h"
#include "GlobalConstants.h"
#include "ScoreManager.h"

void DrawMainMenu(sf::RenderWindow& window);
void UpdateWindow(sf::RenderWindow& window);
void DrawScoreScreen(sf::RenderWindow& window);
void OnStartGame(Difficulty);
void StartGameDelay();
void UpdateGameLogic();
void ResetGameLogic();
bool InMenu = true;
bool OffsetCreated = false;
bool GameStarted = false;
bool MusicStarted = false;
bool MapOver = false;
bool ScoreScreen = false;
bool LastUpdateUpperKeyPressed = false;
bool LastUpdateLowerKeyPressed = false;
sf::Font m_Font;

int main()
{
	sf::RenderWindow window(sf::VideoMode(k_WindowWidth, k_WindowHeight), "IT IS ALIVE!", sf::Style::Titlebar | sf::Style::Close);

	RythmnMapManager manager;
	manager.LoadMap();

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
			{
				// TODO Cleanup memory;
				manager.Delete();
				window.close();
				return 0;
			}
		}

		window.clear();
		UpdateGameLogic();
		UpdateWindow(window);

		window.display();
	}

	manager.Delete();
	return 0;
}

void UpdateWindow(sf::RenderWindow& window)
{
	if (InMenu)
	{
		DrawMainMenu(window);
	}
	else if (GameStarted)
	{
		NoteManager noteManager;
		noteManager.Draw(window);
		ScoreManager score;
		score.DrawScore(window, m_Font);
	}
	else if (ScoreScreen)
	{
		ScoreManager score;
		score.DrawScoreScreen(window, m_Font);
		DrawScoreScreen(window);
	}
}

void UpdateGameLogic()
{
	if (!MusicStarted && GameStarted)
	{
		StartGameDelay();
	}

	if (GameStarted)
	{
		KeyPressOnFrame keyPress;
		keyPress.Update();
		NoteManager noteManager;
		MapOver = noteManager.UpdateNoteTracks();
		if (MapOver)
		{
			AudioManager audio; 
			audio.Instance().StopMusic();
			OffsetCreated = false;
			GameStarted = false;
			MusicStarted = false;
			ScoreScreen = true;
		}
	}
}

void DrawMainMenu(sf::RenderWindow& window)
{
	const float buttonWidth = 360.0f;
	const float buttonHeight = 100.0f;
	const float buttonOffset = 150.0f;
	sf::Vector2f position(k_WindowWidth / 2.0 - buttonWidth / 2.0, k_WindowHeight / 2.0 - buttonHeight / 2.0 + 50.0);

	sf::RectangleShape easyButton(sf::Vector2f(buttonWidth, buttonHeight));
	easyButton.setOutlineColor(sf::Color::White);
	easyButton.setOutlineThickness(1.0f);
	easyButton.setPosition(position);
	easyButton.setFillColor(sf::Color::White);

	sf::Text normalText("Start Normal", m_Font, 50);
	normalText.setFillColor(sf::Color::Black);
	normalText.setPosition(sf::Vector2f(position.x + 41.0, position.y + 18.0));

	window.draw(easyButton);
	window.draw(normalText);

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	if (mousePos.x > position.x && mousePos.x < position.x + buttonWidth &&
		mousePos.y > position.y && mousePos.y < position.y + buttonHeight &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		OnStartGame(Difficulty::Normal);
	}

	position.y += buttonOffset;

	sf::RectangleShape hardButton(sf::Vector2f(buttonWidth, buttonHeight));
	hardButton.setOutlineColor(sf::Color::White);
	hardButton.setOutlineThickness(1.0f);
	hardButton.setPosition(position);
	hardButton.setFillColor(sf::Color::White);

	sf::Text hardText("Start Hard", m_Font, 50);
	hardText.setFillColor(sf::Color::Black);
	hardText.setPosition(sf::Vector2f(position.x + 63.0, position.y + 18.0));

	window.draw(hardButton);
	window.draw(hardText);

	if (mousePos.x > position.x && mousePos.x < position.x + buttonWidth &&
		mousePos.y > position.y && mousePos.y < position.y + buttonHeight &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		OnStartGame(Difficulty::Hard);
	}
}

void DrawScoreScreen(sf::RenderWindow& window)
{
	float buttonWidth = 500.0f;
	float buttonHeight = 100.0f;

	sf::Vector2f position(k_WindowWidth / 2.0 - buttonWidth / 2.0, k_WindowHeight - buttonHeight - 100);

	sf::RectangleShape shape(sf::Vector2f(buttonWidth, buttonHeight));
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1.0f);
	shape.setPosition(position);
	shape.setFillColor(sf::Color::White);

	sf::Text text("Back to Main Menu", m_Font, 50);
	text.setFillColor(sf::Color::Black);
	text.setPosition(sf::Vector2f( position.x + 38.0, position.y + 18.0));

	window.draw(shape);
	window.draw(text);

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	if (mousePos.x > position.x && mousePos.x < position.x + buttonWidth &&
		mousePos.y > position.y && mousePos.y < position.y + buttonHeight &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		ResetGameLogic();
	}
}

void OnStartGame(Difficulty diff)
{
	RythmnMapManager manager;
	manager.SetDifficulty(diff);

	Time time;
	time.SetTimeStart();

	//std::cout << "Game Started \n";
	InMenu = false;
	GameStarted = true;
}

void StartGameDelay()
{
	Time time;
	RythmnMapManager manager;
	if (time.CalculateCurrentBeat() > k_BeatDelay - k_Offset)
	{
		MusicStarted = true;

		AudioManager audio;
		audio.Instance().PlayMusic();
	}
}
void ResetGameLogic()
{
	ScoreManager score;
	score.Reset();

	NoteManager note;
	note.Reset();

	InMenu = true;
	OffsetCreated = false;
	GameStarted = false;
	MusicStarted = false;
	MapOver = false;
	ScoreScreen = false;
}


