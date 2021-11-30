#pragma once
#include <vector>

class NoteHolder
{
private:
	const double k_ScrollTime = 2;
	std::vector<double> m_NotesInTrack;
public:
	void AddNote(double);
	double LookAtNextNote();
	void RemoveNextNote();
	size_t GetSize();
	void Clear();
	std::vector<double> GetAllNotes();

	NoteHolder() = default;
	~NoteHolder() = default;
	NoteHolder(const NoteHolder&) = delete;
	NoteHolder(NoteHolder&&) = default;
	NoteHolder& operator=(const NoteHolder&) = delete;
	NoteHolder& operator=(NoteHolder&&) = default;
};

