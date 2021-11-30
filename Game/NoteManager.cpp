#include "Precompiled.h"
#include "NoteManager.h"
#include "Time.h"
#include "RythmnMapManager.h"
#include "GlobalConstants.h"
#include "AudioManager.h"
#include "ScoreManager.h"

NoteHolder NoteManager::m_UpperTrack = std::move(NoteHolder());
NoteHolder NoteManager::m_LowerTrack = std::move(NoteHolder());
const double NoteManager::k_ScrollDelay = 3.0;
double NoteManager::m_CurrentBPMCursor = k_BeatDelay - k_ScrollDelay;
int NoteManager::m_NoteCursor = 0;
const double NoteManager::k_PerfectThreshold = 0.1;
const double NoteManager::k_GoodThreshold = 0.25;
const double NoteManager::k_MissThreshold = 0.5;
AudioManager* NoteManager::m_AudioManager = nullptr;

KeyHighlight NoteManager::m_UpperTrackHighlight = KeyHighlight();
KeyHighlight NoteManager::m_LowerTrackHighlight = KeyHighlight();

bool NoteManager::UpdateNoteTracks()
{
	Time timeManager;
	double currentBeat = timeManager.CalculateCurrentBeat();
	RythmnMapManager rythmnMapManager;
	int mapSize = rythmnMapManager.GetSize();

	if (currentBeat >= m_CurrentBPMCursor + k_DelayBeforeScore && m_NoteCursor >= mapSize)
	{
		return true;
	}
	else if (currentBeat >= m_CurrentBPMCursor && m_NoteCursor < mapSize)
	{
		NoteObject note = rythmnMapManager.GetNote(m_NoteCursor);
		GetTrack(note.GetTrack())->AddNote(m_CurrentBPMCursor + k_ScrollDelay);

		m_CurrentBPMCursor += note.GetDuration();
		m_NoteCursor += 1;

		if (note.GetDuration() == 0.0)
		{
			UpdateNoteTracks();
			return false;
		}
	}

	KeyPressOnFrame keyInput;

	for (int i = 0; i < 2; i++)
	{

		if (keyInput.KeyPressed((NoteTrack) i))
		{
			NoteHolder* holder = GetTrack((NoteTrack)i);
			double nextNoteTime = abs(holder->LookAtNextNote() - currentBeat);

			if (nextNoteTime < k_MissThreshold)
			{
				holder->RemoveNextNote();
				ScoreManager score;

				if (nextNoteTime < k_PerfectThreshold)
				{
					m_AudioManager->PlayHitSound();
					score.Add(HitType::Perfect);
					GetKeyHighlight((NoteTrack)i) = KeyHighlight(currentBeat, HitType::Perfect);
				}
				else if (nextNoteTime < k_GoodThreshold)
				{
					m_AudioManager->PlayHitSound();
					score.Add(HitType::Good);
					GetKeyHighlight((NoteTrack)i) = KeyHighlight(currentBeat, HitType::Good);
				}
				else
				{
					score.Add(HitType::Miss);
					GetKeyHighlight((NoteTrack)i) = KeyHighlight(currentBeat, HitType::Miss);
				}
			}

		}
	}

	for (int i = 0; i < 2; i++)
	{
		NoteHolder* holder = GetTrack((NoteTrack)i);
		if (holder->GetSize() != 0 &&
			holder->LookAtNextNote() - currentBeat < -k_GoodThreshold)
		{
			holder->RemoveNextNote();
			ScoreManager score;
			score.Add(HitType::Miss);
			GetKeyHighlight((NoteTrack)i) = KeyHighlight(currentBeat, HitType::Miss);
		}
	}

	return false;
}

void NoteManager::Reset()
{
	m_UpperTrack.Clear();
	m_LowerTrack.Clear();
	m_CurrentBPMCursor = k_BeatDelay - k_ScrollDelay;
	m_NoteCursor = 0;

	m_UpperTrackHighlight = KeyHighlight();
	m_LowerTrackHighlight = KeyHighlight();
}

void NoteManager::Draw(sf::RenderWindow& window)
{
	DrawHighlight(window);
	DrawKeys(window);

	DrawNotes(window);
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
				double horizontalPosition = Lerp(k_KeyHorizontalPosition, k_WindowWidth, timeUntilHit / k_ScrollDelay);

				sf::RectangleShape rect(sf::Vector2f(k_KeyButtonWidth, k_KeyButtonHeight));
				rect.setOutlineColor(sf::Color::Cyan);
				rect.setOutlineThickness(1.0f);
				rect.setPosition(sf::Vector2f(
					static_cast<float>(horizontalPosition),
					k_WindowHeight / 2.0f - k_KeyButtonHeight / 2.0f + (-k_KeyVerticalOffset + static_cast<float>(i) * 2.0f * k_KeyVerticalOffset)
				));

				window.draw(rect);
			}
		}
	}
}

void NoteManager::DrawKeys(sf::RenderWindow& window)
{
	for (int i = 0; i < 2; i++)
	{
		sf::RectangleShape key(sf::Vector2f(k_KeyButtonWidth, k_KeyButtonHeight));
		key.setOutlineColor(i ? sf::Color::Cyan : sf::Color::Yellow);
		key.setOutlineThickness(k_ButtonThickness);
		key.setPosition(sf::Vector2f(k_KeyHorizontalPosition, k_WindowHeight / 2.0f - k_KeyButtonHeight / 2.0f + (-k_KeyVerticalOffset + 2.0f * static_cast<float>(i) * k_KeyVerticalOffset)));
		if (sf::Keyboard::isKeyPressed(i ? sf::Keyboard::Key::J : sf::Keyboard::Key::F) || sf::Keyboard::isKeyPressed(i ? sf::Keyboard::Key::K : sf::Keyboard::Key::D))
		{
			key.setFillColor(i ? sf::Color::Cyan : sf::Color::Yellow);
		}
		else
		{
			key.setFillColor(sf::Color::Black);
		}
		window.draw(key);
	}
}

void NoteManager::DrawHighlight(sf::RenderWindow& window)
{
	Time time;
	double currentBeat = time.CalculateCurrentBeat();

	for (int i = 0; i < 2; i++)
	{
		KeyHighlight highlight = GetKeyHighlight((NoteTrack)i);
		if (currentBeat - highlight.m_Beat < k_HighlightDuration && highlight.m_HitType != HitType::Perfect)
		{
			sf::RectangleShape key(sf::Vector2f(k_KeyButtonWidth + k_HighlightThickness * 2.0f, k_KeyButtonHeight + k_HighlightThickness * 2.0f));
			key.setOutlineThickness(k_HighlightThickness);
			key.setPosition(sf::Vector2f(
				k_KeyHorizontalPosition - k_HighlightThickness,
				k_WindowHeight / 2.0f - k_KeyButtonHeight / 2.0f + (-k_KeyVerticalOffset + 2.0f * static_cast<float>(i) * k_KeyVerticalOffset) - k_HighlightThickness
			));
			key.setFillColor(sf::Color::Black);
			if (highlight.m_HitType == HitType::Good)
			{
				key.setOutlineColor(sf::Color::Green);
			}
			else if (highlight.m_HitType == HitType::Miss)
			{
				key.setOutlineColor(sf::Color::Red);
			}
			window.draw(key);
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

KeyHighlight& NoteManager::GetKeyHighlight(NoteTrack track)
{
	if (track == NoteTrack::Upper)
	{
		return m_UpperTrackHighlight;
	}
	else if (track == NoteTrack::Lower)
	{
		return m_LowerTrackHighlight;
	}
	
	throw "This shouldn't happen";
}

double inline NoteManager::Lerp(double a, double b, double t)
{
	return a + (t * (b - a));
}

