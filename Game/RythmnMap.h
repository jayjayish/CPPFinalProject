#pragma once
#include "NoteObject.h"
#include "NoteTrackEnum.h"

struct RythmnMap
{
private:
	static const int m_Size = 2;
	static NoteObject m_Notes[m_Size];
public:
	NoteObject GetNote(int);
};

