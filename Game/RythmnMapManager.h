#pragma once
#include "NoteObject.h"
#include "NoteTrackEnum.h"

class RythmnMapManager
{
private:
	int m_Size;
	double m_Offset;
	double m_BPM;
	NoteObject* m_Notes;
public:
	static RythmnMapManager& Instance() { static RythmnMapManager manager; return manager; }
	NoteObject GetNote(int);
	double GetBPM();
	double GetStartOffset();
	void LoadMap(std::string);
};

