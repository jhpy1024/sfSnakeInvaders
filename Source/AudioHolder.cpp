#include "../Include/AudioHolder.hpp"

void AudioHolder::addSound(const std::string& id, const std::string& fileName)
{
	sf::SoundBuffer buffer;
	buffer.loadFromFile(fileName);

	sounds_[id].first = buffer;

	sf::Sound sound;
	sound.setBuffer(sounds_[id].first);
	sounds_[id].second = sound;
}

void AudioHolder::addMusic(const std::string& id, const std::string& fileName)
{
	sf::Music music;
	music.openFromFile(fileName);

	music_[id] = music;
}

void AudioHolder::removeSound(const std::string& id)
{
	if (sounds_.find(id) != sounds_.end())
		sounds_.erase(id);
}

void AudioHolder::removeMusic(const std::string& id)
{
	if (music_.find(id) != music_.end())
		music_.erase(id);
}

void AudioHolder::playSound(const std::string& id)
{
	if (sounds_.find(id) != sounds_.end())
		sounds_[id].second.play();
}

void AudioHolder::playMusic(const std::string& id)
{
	if (music_.find(id) != music_.end())
		music_[id].play();
}

sf::Sound& AudioHolder::getSound(const std::string& id)
{
	return sounds_[id].second;
}

sf::Music& AudioHolder::getMusic(const std::string& id)
{
	return music_[id];
}