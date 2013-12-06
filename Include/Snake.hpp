#pragma once

#include <memory>

#include "SnakeNode.hpp"

class Game;
class Snake
{
public:
	Snake(const sf::Vector2f& position, Game* game, unsigned initialSize = 5U);

	void handleInput();
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

private:
	void grow();
	void move();
	void checkEdgeCollisions();
	bool hitTop() const;
	bool hitBottom() const;
	bool hitLeft() const;
	bool hitRight() const;

private:
	enum class Direction { Left, Right, Up, Down };
	Direction direction_;

	sf::Vector2f position_;
	std::vector<SnakeNode> nodes_;
	Game* game_;
};