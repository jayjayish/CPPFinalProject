#include "Precompiled.h"
#include "ScoreManager.h"
#include "GlobalConstants.h"

const float ScoreManager::k_ComboLeftOffset = 60;
const float ScoreManager::k_ComboBottomOffset = 100;

int ScoreManager::m_Miss = 0;
int ScoreManager::m_Good = 0;
int ScoreManager::m_Perfect = 0;
int ScoreManager::m_Combo = 0;
int ScoreManager::m_Score = 0;
int ScoreManager::m_MaxCombo = 0;

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
}

void ScoreManager::DrawScore(sf::RenderWindow& window, sf::Font font)
{
	sf::Text text(std::to_string(m_Combo) + "x", font, 42);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(k_ComboLeftOffset, k_WindowHeight - k_ComboBottomOffset));
	window.draw(text);
}
