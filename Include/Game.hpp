#pragma once

#include <SFML/Graphics.hpp>

#include <string>

#include "Snake.hpp"

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

private:
	const int Width;
	const int Height;
	const std::string Title;
	const sf::Time TimePerFrame;

	sf::RenderWindow window_;

	Snake player_;
};