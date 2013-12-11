#pragma once

#include <SFML/Graphics.hpp>

class Game;
class Screen
{
public:
	Screen(Game* game);

	virtual void handleInput() = 0;
	virtual void update(sf::Time delta) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

private:
	Game* game_;
};