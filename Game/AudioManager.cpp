#include "Precompiled.h"
#include "AudioManager.h"

void AudioManager::Initialize()
{
	if (!m_Music.openFromFile("Resources/NeeNeeNee.wav"))
	{
		throw "Rythmn map music file doesn't exist!";
	}

	if (!m_SoundBuffer.loadFromFile("Resources/hitsound.wav"))
	{
		throw "Hitsound file doesn't exist!";
	}

	m_HitSound.setBuffer(m_SoundBuffer);
	m_HitSound.setVolume(30.f);
	m_Music.setVolume(30.0f);
}

void AudioManager::PlayMusic()
{
	m_Music.play();
}

void AudioManager::StopMusic()
{
	m_Music.stop();
}

void AudioManager::PlayHitSound()
{
	m_HitSound.play();
}


