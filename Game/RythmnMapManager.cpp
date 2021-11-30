#include "Precompiled.h"
#include <fstream>
#include "RythmnMapManager.h"
#include "Time.h"

const std::string RythmnMapManager::k_NormalMapFile = "Resources/NeeNeeNeeNormal.txt";
const std::string RythmnMapManager::k_HardMapFile = "Resources/NeeNeeNeeHard.txt";
int RythmnMapManager::m_Size[] = { 0 , 0 };
NoteObject* RythmnMapManager::m_Notes[] = { nullptr, nullptr };
Difficulty RythmnMapManager::m_Difficulty = Difficulty::Hard;

NoteObject RythmnMapManager::GetNote(int i)
{
	return m_Notes[(int) m_Difficulty][i];
}

int RythmnMapManager::GetSize()
{
	return m_Size[(int) m_Difficulty];
}

void RythmnMapManager::LoadMap()
{
	LoadMap(k_NormalMapFile, Difficulty::Normal);
	LoadMap(k_HardMapFile, Difficulty::Hard);
}

void RythmnMapManager::LoadMap(std::string fileName, Difficulty diff)
{
	std::fstream file;
	file.open(fileName, std::ios::in);
	if (!file)
	{
		throw "Map manager didn't find the txt file";
	}
	else
	{
		std::string line;
		int lineNumber = 0;
		while (getline(file, line))
		{
			if (lineNumber == 0)
			{
				m_Size[(int) diff] = std::stoi(line);
			}
			else
			{
				if (lineNumber == 1)
				{
					m_Notes[(int)diff] = new NoteObject[m_Size[(int)diff]];
				}
				int start = 0;
				int end = static_cast<int>(line.find(','));
				int track = std::stoi(line.substr(start, end - start));
				start = end + 1;
				double duration = std::stod(line.substr(start, end - start));

				m_Notes[(int)diff][lineNumber - 1] = NoteObject((NoteTrack)track, duration);
			}
			lineNumber += 1;
		}
	}
	file.close();
}

void RythmnMapManager::Delete()
{
	for (int i = 0; i < 2; i++)
	{
		delete m_Notes[i];
		m_Notes[i] = nullptr;
	}
}

void RythmnMapManager::SetDifficulty(Difficulty diff)
{
	m_Difficulty = diff;
}




