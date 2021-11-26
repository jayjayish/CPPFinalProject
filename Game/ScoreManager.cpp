#include "Precompiled.h"
#include <iomanip>
#include <sstream>
#include "ScoreManager.h"
#include "GlobalConstants.h"

const float ScoreManager::k_ComboLeftOffset = 60;
const float ScoreManager::k_ComboBottomOffset = 100;
const float ScoreManager::k_ScoreScreenLeftOffset = 300;
const float ScoreManager::k_ScoreScreenTopOffset = 300;
const float ScoreManager::k_ScoreScreenLineSpacing = 100;

int ScoreManager::m_Miss = 0;
int ScoreManager::m_Good = 0;
int ScoreManager::m_Perfect = 0;
int ScoreManager::m_Combo = 0;
int ScoreManager::m_Score = 0;
int ScoreManager::m_MaxCombo = 0;
double ScoreManager::m_Accuracy = 1;

void ScoreManager::Add(HitType hit)
{
	if (hit == HitType::Miss)
	{
		m_Combo = 0;
		m_Miss += 1;
	}
	else
	{
		if (hit == HitType::Good)
		{
			m_Good += 1;
		}
		else if (hit == HitType::Perfect)
		{
			m_Perfect += 1;
		}
		m_Combo += 1;

		if (m_Combo > m_MaxCombo)
		{
			m_MaxCombo = m_Combo;
		}
	}
	CalculateAccuracy();
}

void ScoreManager::Reset()
{
	m_Miss = 0;
	m_Good = 0;
	m_Perfect = 0;
	m_Combo = 0;
	m_Score = 0;
	m_MaxCombo = 0;
	m_Accuracy = 1;
}

void ScoreManager::DrawScore(sf::RenderWindow& window, sf::Font font)
{
	sf::Text combo(std::to_string(m_Combo) + "x", font, 42);
	combo.setFillColor(sf::Color::White);
	combo.setPosition(sf::Vector2f(k_ComboLeftOffset, k_WindowHeight - k_ComboBottomOffset));
	window.draw(combo);

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << m_Accuracy * 100.0;
	std::string accStr = stream.str();
	sf::Text acc(accStr + "%", font, 42);
	acc.setFillColor(sf::Color::White);
	acc.setPosition(sf::Vector2f(k_ComboLeftOffset, k_ComboBottomOffset - 55.0));
	window.draw(acc);
}

void ScoreManager::DrawScoreScreen(sf::RenderWindow& window, sf::Font font)
{
	const int i = 12;
	const int j = 16;

	sf::Vector2f position(k_ScoreScreenLeftOffset, k_ScoreScreenTopOffset);
	std::string perfectStr = std::to_string(m_Perfect);
	sf::Text perfect("Perfect" + MakePadding(i - 7 - perfectStr.size()) + perfectStr + "x", font, 42);
	perfect.setFillColor(sf::Color::White);
	perfect.setPosition(position);
	window.draw(perfect);

	position.y += k_ScoreScreenLineSpacing;

	std::string goodStr = std::to_string(m_Good);
	sf::Text good("Good" + MakePadding(i - 4 - goodStr.size()) + goodStr + "x", font, 42);
	good.setFillColor(sf::Color::White);
	good.setPosition(position);
	window.draw(good);

	position.y += k_ScoreScreenLineSpacing;

	std::string missStr = std::to_string(m_Miss);
	sf::Text miss("Miss" + MakePadding(i - 3 - missStr.size()) + std::to_string(m_Miss) + "x", font, 42);
	miss.setFillColor(sf::Color::White);
	miss.setPosition(position);
	window.draw(miss);

	position = sf::Vector2f(k_ScoreScreenLeftOffset + 400, k_ScoreScreenTopOffset);

	CalculateAccuracy();
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << m_Accuracy * 100.0;
	std::string accStr = stream.str();
	sf::Text acc("Accuracy" + MakePadding(j - 8 - accStr.size()) + accStr + "%", font, 42);
	acc.setFillColor(sf::Color::White);
	acc.setPosition(position);
	window.draw(acc);

	position.y += k_ScoreScreenLineSpacing;

	std::string comboStr = std::to_string(m_MaxCombo);
	sf::Text combo("Max Combo" + MakePadding(j - 9 - comboStr.size()) + comboStr + "x", font, 42);
	combo.setFillColor(sf::Color::White);
	combo.setPosition(position);
	window.draw(combo);

}

void ScoreManager::CalculateAccuracy()
{
	int totalNotes = m_Miss + m_Good + m_Perfect;

	if (m_Miss + m_Good + m_Perfect == 0)
	{
		m_Accuracy = 1;
	}
	else
	{
		m_Accuracy = (m_Good / 3.0 + m_Perfect) / static_cast<double>(totalNotes);
	}
}

std::string ScoreManager::MakePadding(int i)
{
	std::string s(i ,' ');
	return s;
}


