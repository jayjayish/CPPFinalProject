#pragma once
#include "NoteObject.h"
#include "NoteTrackEnum.h"

class RythmnMapManager
{
private:
	static int m_Size;
	static double m_Offset;
	static double m_BPM;
	static NoteObject* m_Notes;
public:
	NoteObject GetNote(int);
	double GetBPM();
	double GetStartOffset();
	int GetSize();
	void LoadMap(std::string);
};

