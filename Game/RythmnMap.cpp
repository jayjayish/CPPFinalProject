#include "Precompiled.h"
#include "RythmnMap.h"

NoteObject RythmnMap::m_Notes[] =
{
	NoteObject(NoteTrack::Left, 1),
	NoteObject(NoteTrack::Right, 1),
};

NoteObject RythmnMap::GetNote(int i)
{
	if (i >= m_Size)
	{
		throw "Out of bounds of rythmn map array";
	}
	
	return m_Notes[i];
}
