#pragma once
#include "NoteTrackEnum.h"

struct NoteObject
{
private:
	NoteTrack m_Track;
	double m_Duration;
public:
	NoteObject(NoteTrack, double);
	NoteTrack GetTrack();
	double GetDuration();
	NoteObject();
	~NoteObject() = default;
};

