#pragma once
#include "HitType.h"
class ScoreManager
{
private:
	static int m_Miss;
	static int m_Good;
	static int m_Perfect;
	static int m_Combo;
	static int m_Score;
	static int m_MaxCombo;
	static const float k_ComboLeftOffset;
	static const float k_ComboBottomOffset;
public:
	void Add(HitType hit);
	void DrawScore(sf::RenderWindow& window, sf::Font font);
};

