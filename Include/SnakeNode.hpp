#pragma once

#include <SFML/Graphics.hpp>

class SnakeNode
{
public:
	SnakeNode(const sf::Vector2f& position);

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	void move(const sf::Vector2f& offset);
	void render(sf::RenderWindow& window);

	static const float Size;
private:
	sf::RectangleShape shape_;
};