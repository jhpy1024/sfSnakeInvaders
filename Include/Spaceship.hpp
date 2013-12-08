#pragma once

#include "Entity.hpp"

class Spaceship : public Entity
{
public:
	Spaceship(const sf::Vector2f& position, Game* game);

	void handleInput() override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	static const int Width;
	static const int Height;

private:
	const unsigned NumFrames;
	unsigned currentFrame_;
	
	const sf::Time AnimationDelay;
	sf::Clock animationClock_;
	sf::Time lastAnimTime_;
};