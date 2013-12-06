#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

class TextureHolder
{
public:
	void addTexture(const std::string& id, const std::string& fileName);
	void removeTexture(const std::string& id);
	
	sf::Texture& getTexture(const std::string& id);

private:
	std::map<std::string, sf::Texture> textures_;
};