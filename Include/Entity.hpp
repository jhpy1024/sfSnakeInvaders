#pragma once

#include <memory>

#include "Game.hpp"

class Entity
{
public:
	Entity(const sf::Vector2f& position, std::shared_ptr<Game> game);

	virtual void handleInput() = 0;
	virtual void update(sf::Time delta) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

	sf::Vector2f getPosition() const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	void setPosition(const sf::Vector2f& position);
	void move(const sf::Vector2f& offset);

protected:
	std::shared_ptr<Game> game_;

private:
	sf::Sprite sprite_;
};