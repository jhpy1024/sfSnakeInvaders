#pragma once

#include "Entity.hpp"

class Bullet : public Entity
{
public:
	enum class Direction { Left, Right, Down, Up };

	Bullet(const sf::Vector2f& position, Game* game, Direction direction);

	void handleInput() override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	bool outOfBounds() const;

private:
	float Speed;

	Direction direction_;

	bool outOfBounds_;
};