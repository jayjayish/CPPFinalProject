#pragma once
#include "NoteHolder.h"
#include "KeyPressOnFrame.h"

class NoteManager
{
private:
	static NoteHolder m_UpperTrack;
	static NoteHolder m_LowerTrack;
	static const double m_ScrollDelay;
	static double m_CurrentBPMCursor;
	static int m_NoteCursor;
	static const double m_LateThreshold;
	static double inline Lerp(double a, double b, double t);
	NoteHolder* GetTrack(NoteTrack);
public:
	void UpdateNoteTracks();
	void DrawNotes(sf::RenderWindow& window);
};

