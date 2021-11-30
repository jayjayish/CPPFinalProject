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

	static void CalculateAccuracy();
	static std::string MakePadding(int i);
public:
	static void Add(HitType hit);
	static void DrawScore(sf::RenderWindow& window, sf::Font font);
	static void DrawScoreScreen(sf::RenderWindow& window, sf::Font font);
	static void Reset();

	ScoreManager() = default;
	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;
};

