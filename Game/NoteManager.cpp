#include "Precompiled.h"
#include "NoteManager.h"
#include "Time.h"
#include "RythmnMapManager.h"
#include "GlobalConstants.h"
#include "AudioManager.h"

NoteHolder NoteManager::m_UpperTrack = NoteHolder();
NoteHolder NoteManager::m_LowerTrack = NoteHolder();
const double NoteManager::m_ScrollDelay = 2.0;
double NoteManager::m_CurrentBPMCursor = 4 - m_ScrollDelay;
int NoteManager::m_NoteCursor = 0;
const double NoteManager::m_LateThreshold = 0.2;
KeyPressOnFrame NoteManager::m_KeyPressed = KeyPressOnFrame();


void NoteManager::UpdateNoteTracks()
{
	Time timeManager;
	double currentBeat = timeManager.CalculateCurrentBeat();
	RythmnMapManager rythmnMapManager;
	int mapSize = rythmnMapManager.GetSize();
	if (currentBeat >= m_CurrentBPMCursor + 3.0 && m_NoteCursor >= mapSize)
	{
		//std::cout << "Map over\n";
	}
	else if (currentBeat >= m_CurrentBPMCursor && m_NoteCursor < mapSize)
	{
		NoteObject note = rythmnMapManager.GetNote(m_NoteCursor);

		if (note.GetTrack() == NoteTrack::Left)
		{
			m_UpperTrack.AddNote(m_CurrentBPMCursor + m_ScrollDelay);
			std::cout << "Note Added to upper\n";
		}
		else if (note.GetTrack() == NoteTrack::Right)
		{
			m_LowerTrack.AddNote(m_CurrentBPMCursor + m_ScrollDelay);
			std::cout << "Note Added to lower\n";
		}

		m_CurrentBPMCursor += note.GetDuration();
		m_NoteCursor += 1;

		if (note.GetDuration() == 0.0)
		{
			UpdateNoteTracks();
			return;
		}
	}

	if (m_KeyPressed.UpperKeyPressed())
	{
		if (abs(m_UpperTrack.LookAtNextNote() - currentBeat) < m_LateThreshold)
		{
			m_UpperTrack.RemoveNextNote();
			AudioManager audio;
			audio.Instance().PlayHitSound();
		}
	}

	if (m_KeyPressed.LowerKeyPressed())
	{
		if (abs(m_LowerTrack.LookAtNextNote() - currentBeat) < m_LateThreshold)
		{
			m_LowerTrack.RemoveNextNote();
			AudioManager audio;
			audio.Instance().PlayHitSound();
		}
	}

	if (m_UpperTrack.GetSize() != 0 &&
		m_UpperTrack.LookAtNextNote() - currentBeat < -m_LateThreshold)
	{
		m_UpperTrack.RemoveNextNote();
	}

	if (m_LowerTrack.GetSize() != 0 &&
		m_LowerTrack.LookAtNextNote() - currentBeat < -m_LateThreshold)
	{
		m_LowerTrack.RemoveNextNote();
	}
}

void NoteManager::DrawNotes(sf::RenderWindow& window)
{
	sf::Vector2f upperKeyPos(k_KeyHorizontalPosition, k_WindowHeight / 2.0 - k_KeyButtonHeight / 2.0 - k_KeyVerticalOffset);
	sf::Vector2f lowerKeyPos(k_KeyHorizontalPosition, k_WindowHeight / 2.0 - k_KeyButtonHeight / 2.0 + k_KeyVerticalOffset);

	Time timeManager;
	double currentBeat = timeManager.CalculateCurrentBeat();

	if (m_UpperTrack.GetSize() != 0)
	{
		std::vector<double> upperTrackVector = m_UpperTrack.GetAllNotes();

		for (auto pos = upperTrackVector.cbegin(); pos != upperTrackVector.cend(); ++pos)
		{
			double timeUntilHit = *pos - currentBeat;
			double horizontalPosition = Lerp(k_KeyHorizontalPosition, k_WindowWidth, timeUntilHit / m_ScrollDelay);

			sf::RectangleShape rect(sf::Vector2f(k_KeyButtonWidth, k_KeyButtonHeight));
			rect.setOutlineColor(sf::Color::Cyan);
			rect.setOutlineThickness(1.0f);
			rect.setPosition(sf::Vector2f(horizontalPosition, upperKeyPos.y));

			window.draw(rect);
		}
	}

	if (m_LowerTrack.GetSize() != 0)
	{
		std::vector<double> lowerTrackVector = m_LowerTrack.GetAllNotes();

		for (auto pos = lowerTrackVector.cbegin(); pos != lowerTrackVector.cend(); ++pos)
		{
			double timeUntilHit = *pos - currentBeat;
			double horizontalPosition = Lerp(k_KeyHorizontalPosition, k_WindowWidth, timeUntilHit / m_ScrollDelay);

			sf::RectangleShape rect(sf::Vector2f(k_KeyButtonWidth, k_KeyButtonHeight));
			rect.setOutlineColor(sf::Color::Yellow);
			rect.setOutlineThickness(1.0f);
			rect.setPosition(sf::Vector2f(horizontalPosition, lowerKeyPos.y));

			window.draw(rect);
		}
	}
}


double inline NoteManager::Lerp(double a, double b, double t)
{
	return a + (t * (b - a));
}

