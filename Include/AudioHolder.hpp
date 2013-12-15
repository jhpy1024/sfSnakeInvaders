#pragma once

#include <SFML/Audio.hpp>

#include <map>
#include <string>
#include <memory>
#include <utility>

class AudioHolder
{
public:
	void loadSound(const std::string& id, const std::string& fileName);
	void loadMusic(const std::string& id, const std::string& fileName);

	void removeSound(const std::string& id);
	void removeMusic(const std::string& id);

	void playSound(const std::string& id);
	void playMusic(const std::string& id);

	sf::Sound& getSound(const std::string& id);
	sf::Music& getMusic(const std::string& id);

private:
	std::map<std::string, std::pair<sf::Sound, std::unique_ptr<sf::SoundBuffer>>> sounds_;
	std::map<std::string, std::unique_ptr<sf::Music>> music_;
};