#include "Precompiled.h"
#include "NoteObject.h"

NoteObject::NoteObject(NoteTrack track, double time)
	:m_Track(track),
	m_Duration(time)
{}

NoteTrack NoteObject::GetTrack()
{
	return m_Track;
}

double NoteObject::GetDuration()
{
	return m_Duration;
}

NoteObject::NoteObject()
	:m_Track(NoteTrack::Upper),
	m_Duration(0)
{}

//Add Move and copy
