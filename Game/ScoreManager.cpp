#include "Precompiled.h"
#include "ScoreManager.h"

int ScoreManager::m_Miss = 0;
int ScoreManager::m_Good = 0;
int ScoreManager::m_Perfect = 0;
int ScoreManager::m_Combo = 0;
int ScoreManager::m_Score = 0;
int ScoreManager::m_MaxCombo = 0;

void ScoreManager::Add(ScoreEnum hit)
{
	if (hit == ScoreEnum::Miss)
	{
		m_Combo = 0;
		m_Miss += 1;
	}
	else
	{
		if (hit == ScoreEnum::Good)
		{
			m_Good += 1;
		}
		else if (hit == ScoreEnum::Perfect)
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
