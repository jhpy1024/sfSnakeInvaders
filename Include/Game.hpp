#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();

private:
	const int Width;
	const int Height;
	const std::string Title;
	const sf::Time TimePerFrame;

	sf::RenderWindow window_;
};