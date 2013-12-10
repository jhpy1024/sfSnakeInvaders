#pragma once

#include <SFML/Graphics.hpp>

class SnakeNode
{
public:
	SnakeNode(const sf::Vector2f& position, bool head = false);

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& position);

	void move(const sf::Vector2f& offset);
	void render(sf::RenderWindow& window);

	static const float Size;
private:
	sf::RectangleShape shape_;
};