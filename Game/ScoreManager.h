#pragma once
#include "ScoreEnum.h"
class ScoreManager
{
private:
	static int m_Miss;
	static int m_Good;
	static int m_Perfect;
	static int m_Combo;
	static int m_Score;
	static int m_MaxCombo;
public:
	void Add(ScoreEnum hit);
};

