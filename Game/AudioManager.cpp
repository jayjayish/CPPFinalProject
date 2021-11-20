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
}

void AudioManager::PlayMusic()
{
	m_Music.play();
}

void AudioManager::PlayHitSound()
{
	m_HitSound.play();
}


