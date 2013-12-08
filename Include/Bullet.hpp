#pragma once

#include <string>

#include "Entity.hpp"

class Bullet : public Entity
{
public:
	enum class Direction { Left, Right, Down, Up };

	Bullet(const sf::Vector2f& position, Game* game, Direction direction, const std::string& textureId = "bullets");

	void handleInput() override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	bool outOfBounds() const;

	void setTextureRect(const sf::IntRect& rect);

private:
	float speed_;
	float acceleration_;

	Direction direction_;

	bool outOfBounds_;
};