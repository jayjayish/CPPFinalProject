#pragma once
#include <vector>

class NoteHolder
{
private:
	const double k_ScrollTime = 2;
	std::vector<double> m_NotesInTrack;
public:
	NoteHolder() = default;
	void AddNote(double);
	double LookAtNextNote();
	void RemoveNextNote();
	int GetSize();
	std::vector<double> GetAllNotes();
};

