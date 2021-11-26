#pragma once
#include "NoteHolder.h"
#include "KeyPressOnFrame.h"
#include "KeyHighlightStruct.h"

class NoteManager
{
private:
	static NoteHolder m_UpperTrack;
	static NoteHolder m_LowerTrack;
	static const double k_ScrollDelay;
	static double m_CurrentBPMCursor;
	static int m_NoteCursor;
	static const double k_PerfectThreshold;
	static const double k_GoodThreshold;
	static const double k_MissThreshold;
	static KeyHighlight m_UpperTrackHighlight;
	static KeyHighlight m_LowerTrackHighlight;

	static double inline Lerp(double a, double b, double t);

	NoteHolder* GetTrack(NoteTrack);
	KeyHighlight& GetKeyHighlight(NoteTrack track);
	void DrawKeys(sf::RenderWindow& window);
	void DrawNotes(sf::RenderWindow& window);
	void DrawHighlight(sf::RenderWindow& window);
public:
	void UpdateNoteTracks();
	void Draw(sf::RenderWindow& window);
};

