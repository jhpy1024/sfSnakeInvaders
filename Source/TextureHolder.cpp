#include "../Include/TextureHolder.hpp"

void TextureHolder::addTexture(const std::string& id, const std::string& fileName)
{
	sf::Texture texture;
	texture.loadFromFile(fileName);

	textures_[id] = texture;
}

void TextureHolder::removeTexture(const std::string& id)
{
	textures_.erase(id);
}

sf::Texture& TextureHolder::getTexture(const std::string& id)
{
	return textures_[id];
}