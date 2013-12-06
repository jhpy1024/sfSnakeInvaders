#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

class Game;
class Entity
{
public:
	Entity(const sf::Vector2f& position, Game* game);
	
	virtual void handleInput() = 0;
	virtual void update(sf::Time delta) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

	sf::Vector2f getPosition() const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	void setPosition(const sf::Vector2f& position);
	void move(const sf::Vector2f& offset);

protected:
	Game* game_;
	sf::Sprite sprite_;
};