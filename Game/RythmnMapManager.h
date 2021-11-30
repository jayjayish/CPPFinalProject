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
	static void LoadMap(std::string, Difficulty diff);
public:
	static NoteObject GetNote(int);
	static int GetSize();
	static void LoadMap();
	static void Delete();
	static void SetDifficulty(Difficulty diff);

	RythmnMapManager() = default;
	RythmnMapManager(const RythmnMapManager&) = delete;
	RythmnMapManager& operator=(const RythmnMapManager&) = delete;
};

