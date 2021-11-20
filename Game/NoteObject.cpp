#include "Precompiled.h"
#include "NoteObject.h"

NoteObject::NoteObject(NoteTrack track, double time)
	:m_Track(track),
	m_Duration(time)
{}
