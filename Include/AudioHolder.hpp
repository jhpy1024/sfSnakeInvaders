#pragma once

#include <SFML/Audio.hpp>

#include <iostream>
#include <map>
#include <utility>

class AudioHolder
{
public:
	void addSound(const std::string& id, const std::string& fileName);
	void addMusic(const std::string& id, const std::string& fileName);

	void removeSound(const std::string& id);
	void removeMusic(const std::string& id);

	sf::Sound& getSound(const std::string& id);
	sf::Music& getMusic(const std::string& id);

	void playSound(const std::string& id);
	void playMusic(const std::string& id);

private:
	std::map<std::string, std::pair<sf::SoundBuffer, sf::Sound>> sounds_;
	std::map<std::string, sf::Music> music_;
};