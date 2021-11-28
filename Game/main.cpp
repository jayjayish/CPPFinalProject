#include "Precompiled.h"
#include "Time.h"
#include "AudioManager.h"
#include "RythmnMapManager.h"
#include "NoteManager.h"
#include "GlobalConstants.h"
#include "ScoreManager.h"

void DrawMainMenu(sf::RenderWindow& window, sf::Font& font);
void UpdateWindow(sf::RenderWindow& window , sf::Sprite&, sf::Font& font);
void DrawScoreScreen(sf::RenderWindow& window, sf::Font& font);
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

int main()
{
	sf::RenderWindow window(sf::VideoMode(k_WindowWidth, k_WindowHeight), "IT IS ALIVE!", sf::Style::Titlebar | sf::Style::Close);

	RythmnMapManager manager;
	manager.LoadMap();

	sf::Texture m_Image;
	if (!m_Image.loadFromFile("Resources/menuImage1.png"))
	{
		throw "Image file not found";
	}
	sf::Sprite m_SpriteImage(m_Image);
	m_SpriteImage.setPosition(k_WindowWidth / 2.0 - m_Image.getSize().x / 2.0, 100.0f);

	AudioManager audioManager;
	audioManager.Instance().Initialize();

	sf::Font m_Font;
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
		UpdateWindow(window, m_SpriteImage, m_Font);

		window.display();
	}

	manager.Delete();
	return 0;
}

void UpdateWindow(sf::RenderWindow& window, sf::Sprite& sprite, sf::Font& font)
{
	if (InMenu)
	{
		DrawMainMenu(window, font);
		window.draw(sprite);
	}
	else if (GameStarted)
	{
		NoteManager noteManager;
		noteManager.Draw(window);
		ScoreManager score;
		score.DrawScore(window, font);
	}
	else if (ScoreScreen)
	{
		ScoreManager score;
		score.DrawScoreScreen(window, font);
		DrawScoreScreen(window, font);
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

void DrawMainMenu(sf::RenderWindow& window, sf::Font& font)
{
	const float buttonWidth = 360.0f;
	const float buttonHeight = 100.0f;
	const float buttonOffset = 150.0f;
	sf::Vector2f position(k_WindowWidth / 2.0 - buttonWidth / 2.0, k_WindowHeight / 2.0 - buttonHeight / 2.0 + 150.0);

	sf::RectangleShape easyButton(sf::Vector2f(buttonWidth, buttonHeight));
	easyButton.setOutlineColor(sf::Color::White);
	easyButton.setOutlineThickness(1.0f);
	easyButton.setPosition(position);
	easyButton.setFillColor(sf::Color::White);

	sf::Text normalText("Start Normal", font, 50);
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

	sf::Text hardText("Start Hard", font, 50);
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

void DrawScoreScreen(sf::RenderWindow& window, sf::Font& font)
{
	float buttonWidth = 500.0f;
	float buttonHeight = 100.0f;

	sf::Vector2f position(k_WindowWidth / 2.0 - buttonWidth / 2.0, k_WindowHeight - buttonHeight - 100);

	sf::RectangleShape shape(sf::Vector2f(buttonWidth, buttonHeight));
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1.0f);
	shape.setPosition(position);
	shape.setFillColor(sf::Color::White);

	sf::Text text("Back to Main Menu", font, 50);
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

