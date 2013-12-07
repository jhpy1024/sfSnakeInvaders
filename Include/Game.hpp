#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <memory>
#include <vector>

#include "Snake.hpp"
#include "TextureHolder.hpp"

class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();

	int getWidth() const;
	int getHeight() const;

	sf::Time getFps() const;

	TextureHolder& getTextureHolder();

private:
	const int Width;
	const int Height;
	const std::string Title;
	const sf::Time TimePerFrame;

	std::vector<std::unique_ptr<Entity>> spaceships_;

	sf::RenderWindow window_;
	sf::Sprite bgSprite_;

	TextureHolder textures_;

	Snake player_;
};