#pragma once
class AudioManager
{
private:
	sf::Music m_Music;
	sf::Sound m_HitSound;
	sf::SoundBuffer m_SoundBuffer;
public:
	void Initialize();
	void PlayMusic();
	void StopMusic();
	void PlayHitSound();
	AudioManager() = default;
	~AudioManager() = default;
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;
};

