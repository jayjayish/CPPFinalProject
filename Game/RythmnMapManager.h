#pragma once
#include "NoteObject.h"
#include "NoteTrackEnum.h"
#include "DifficultyEnum.h"

class RythmnMapManager
{
private:
	static const std::string k_NormalMapFile;
	static const std::string k_HardMapFile;
	static int m_Size[2];
	static NoteObject* m_Notes[2];
	static Difficulty m_Difficulty;
	void LoadMap(std::string, Difficulty diff);
public:
	NoteObject GetNote(int);
	int GetSize();
	void LoadMap();
	void Delete();
	void SetDifficulty(Difficulty diff);
};

