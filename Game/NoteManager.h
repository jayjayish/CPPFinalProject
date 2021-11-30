#pragma once
#include "NoteHolder.h"
#include "KeyPressOnFrame.h"
#include "KeyHighlightStruct.h"
#include "AudioManager.h"

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

	static NoteHolder* GetTrack(NoteTrack);
	static KeyHighlight& GetKeyHighlight(NoteTrack track);
	static void DrawKeys(sf::RenderWindow& window);
	static void DrawNotes(sf::RenderWindow& window);
	static void DrawHighlight(sf::RenderWindow& window);
	static double inline Lerp(double a, double b, double t);
public:
	static AudioManager* m_AudioManager;
	static bool UpdateNoteTracks();
	static void Draw(sf::RenderWindow& window);
	static void Reset();

	NoteManager() = default;
	NoteManager(const NoteManager&) = delete;
	NoteManager& operator=(const NoteManager&) = delete;
};

