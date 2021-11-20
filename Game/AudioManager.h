#pragma once
class AudioManager
{
private:
	sf::Music m_Music;
	sf::Sound m_HitSound;
	sf::SoundBuffer m_SoundBuffer;
public:
	void Initialize();
	static AudioManager& Instance() { static AudioManager audioManager; return audioManager; }
	void PlayMusic();
	void PlayHitSound();
};

