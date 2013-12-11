#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <memory>
#include <vector>

#include "Snake.hpp"
#include "TextureHolder.hpp"
#include "Animation.hpp"

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
	std::vector<std::unique_ptr<Entity>>& getSpaceships();

	TextureHolder& getTextureHolder();

private:
	void updateShips(sf::Time delta);

private:
	const int Width;
	const int Height;
	const std::string Title;
	const sf::Time TimePerFrame;

	const unsigned NumShipRows;
	const unsigned NumShipColumns;
	const int ShipHorizontalSpacing;
	const int ShipVerticalSpacing;
	std::vector<std::unique_ptr<Entity>> spaceships_;
	std::vector<std::vector<std::unique_ptr<Entity>>::size_type> shipsToRemove_;

	sf::RenderWindow window_;
	sf::Sprite bgSprite_;

	TextureHolder textures_;

	std::vector<Animation> animations_;
	std::vector<std::vector<Animation>::size_type> animsToRemove_;

	Snake player_;
};