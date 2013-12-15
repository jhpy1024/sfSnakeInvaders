#include "../Include/AudioHolder.hpp"

#include <iostream>

sf::Sound& AudioHolder::getSound(const std::string& id)
{
	if (sounds_.find(id) == sounds_.end())
		throw std::logic_error("Trying to get sound " + id + " but it doesn't exist");

	return sounds_[id].first;
}

sf::Music& AudioHolder::getMusic(const std::string& id)
{
	if (music_.find(id) == music_.end())
		throw std::logic_error("Trying to get music " + id + " but it doesn't exist.");

	return *music_[id];
}

void AudioHolder::loadSound(const std::string& id, const std::string& fileName)
{
	sounds_[id] = std::make_pair(sf::Sound(), std::make_unique<sf::SoundBuffer>());
	sounds_[id].second->loadFromFile(fileName);
	sounds_[id].first.setBuffer(*sounds_[id].second);
}

void AudioHolder::loadMusic(const std::string& id, const std::string& fileName)
{
	music_[id] = std::unique_ptr<sf::Music>(new sf::Music());
	music_[id]->openFromFile(fileName);
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
	{
		std::cout << "Playing sound " << id << std::endl;
		sounds_[id].first.play();
	}
}

void AudioHolder::playMusic(const std::string& id)
{
	if (music_.find(id) != music_.end())
		music_[id]->play();
}