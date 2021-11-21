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
	NoteObject GetNote(int);
	double GetBPM();
	double GetStartOffset();
	void LoadMap(std::string);
};

