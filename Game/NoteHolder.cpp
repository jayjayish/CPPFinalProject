#include "Precompiled.h"
#include "NoteHolder.h"


void NoteHolder::AddNote(double num)
{
	m_NotesInTrack.push_back(num);
}

double NoteHolder::LookAtNextNote()
{
	if (GetSize() == 0)
	{
		return -1.0;
	}
	
	return m_NotesInTrack.front();
}

void NoteHolder::RemoveNextNote()
{
	if (GetSize() != 0)
	{
		m_NotesInTrack.erase(m_NotesInTrack.begin());
	}
}

int NoteHolder::GetSize()
{
	return m_NotesInTrack.size();
}

void NoteHolder::Clear()
{
	m_NotesInTrack.clear();
}

std::vector<double> NoteHolder::GetAllNotes()
{
	return m_NotesInTrack;
}
