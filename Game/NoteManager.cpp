#include "Precompiled.h"
#include "NoteManager.h"
#include "Time.h"
#include "RythmnMapManager.h"
#include "GlobalConstants.h"
#include "AudioManager.h"

NoteHolder NoteManager::m_UpperTrack = NoteHolder();
NoteHolder NoteManager::m_LowerTrack = NoteHolder();
const double NoteManager::m_ScrollDelay = 2.0;
double NoteManager::m_CurrentBPMCursor = k_BeatDelay - m_ScrollDelay;
int NoteManager::m_NoteCursor = 0;
const double NoteManager::m_LateThreshold = 0.2;

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
		GetTrack(note.GetTrack())->AddNote(m_CurrentBPMCursor + m_ScrollDelay);

		m_CurrentBPMCursor += note.GetDuration();
		m_NoteCursor += 1;

		if (note.GetDuration() == 0.0)
		{
			UpdateNoteTracks();
			return;
		}
	}

	KeyPressOnFrame keyInput;

	for (int i = 0; i < 2; i++)
	{

		if (keyInput.KeyPressed((NoteTrack) i))
		{

			NoteHolder* holder = GetTrack((NoteTrack)i);

			std::cout << holder->LookAtNextNote() << "\n";

			if (abs(holder->LookAtNextNote() - currentBeat) < m_LateThreshold)
			{
				holder->RemoveNextNote();
				AudioManager audio;
				audio.Instance().PlayHitSound();
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		NoteHolder* holder = GetTrack((NoteTrack)i);
		if (holder->GetSize() != 0 &&
			holder->LookAtNextNote() - currentBeat < -m_LateThreshold)
		{
			holder->RemoveNextNote();
		}
	}
}

void NoteManager::DrawNotes(sf::RenderWindow& window)
{
	Time timeManager;
	double currentBeat = timeManager.CalculateCurrentBeat();

	for (int i = 0; i < 2; i++)
	{
		NoteHolder* holder = GetTrack((NoteTrack) i);
		if (holder->GetSize() != 0)
		{
			std::vector<double> trackVector = holder->GetAllNotes();

			for (auto pos = trackVector.cbegin(); pos != trackVector.cend(); ++pos)
			{
				double timeUntilHit = *pos - currentBeat;
				double horizontalPosition = Lerp(k_KeyHorizontalPosition, k_WindowWidth, timeUntilHit / m_ScrollDelay);

				sf::RectangleShape rect(sf::Vector2f(k_KeyButtonWidth, k_KeyButtonHeight));
				rect.setOutlineColor(sf::Color::Cyan);
				rect.setOutlineThickness(1.0f);
				rect.setPosition(sf::Vector2f(
					horizontalPosition,
					k_WindowHeight / 2.0 - k_KeyButtonHeight / 2.0 + (-k_KeyVerticalOffset + i * 2 * k_KeyVerticalOffset)
				));

				window.draw(rect);
			}
		}
	}
}

NoteHolder* NoteManager::GetTrack(NoteTrack track)
{
	if (track == NoteTrack::Upper)
	{
		return &m_UpperTrack;
	}
	else if (track == NoteTrack::Lower)
	{
		return &m_LowerTrack;
	}

	throw "This shouldn't happen";
}


double inline NoteManager::Lerp(double a, double b, double t)
{
	return a + (t * (b - a));
}

