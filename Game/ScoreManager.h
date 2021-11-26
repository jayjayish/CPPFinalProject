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
	static double m_Accuracy;
	static const float k_ComboLeftOffset;
	static const float k_ComboBottomOffset;
	static const float k_ScoreScreenLeftOffset;
	static const float k_ScoreScreenTopOffset;
	static const float k_ScoreScreenLineSpacing;

	void CalculateAccuracy();
	std::string MakePadding(int i);
public:
	void Add(HitType hit);
	void DrawScore(sf::RenderWindow& window, sf::Font font);
	void DrawScoreScreen(sf::RenderWindow& window, sf::Font font);
	void Reset();
};

