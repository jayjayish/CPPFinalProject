#include "Precompiled.h"
#include <fstream>
#include "RythmnMapManager.h"
#include "Time.h"

int RythmnMapManager::m_Size = 0;
double RythmnMapManager::m_Offset = 0.0;
double RythmnMapManager::m_BPM = 0.0;
NoteObject* RythmnMapManager::m_Notes = nullptr;

NoteObject RythmnMapManager::GetNote(int i)
{
	return m_Notes[i];
}

double RythmnMapManager::GetBPM()
{
	return m_BPM;
}

double RythmnMapManager::GetStartOffset()
{
	return m_Offset;
}

int RythmnMapManager::GetSize()
{
	return m_Size;
}

void RythmnMapManager::LoadMap(std::string fileName)
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
				m_BPM = std::stod(line);
			}
			else if (lineNumber == 1)
			{
				m_Offset = std::stod(line);
			}
			else if (lineNumber == 2)
			{
				m_Size = std::stoi(line);
			}
			else
			{	
				if (lineNumber == 3)
				{
					m_Notes = new NoteObject[m_Size];
				}
				int start = 0;
				int end = line.find(',');
				int track = std::stoi( line.substr(start, end - start));
				start = end + 1;
				double duration = std::stod(line.substr(start, end - start));

				m_Notes[lineNumber - 3] = NoteObject((NoteTrack) track, duration);
			}
			lineNumber += 1;
		}
	}
	file.close();

	Time timeClass;
	timeClass.SetMapData(m_BPM, m_Offset);
}




