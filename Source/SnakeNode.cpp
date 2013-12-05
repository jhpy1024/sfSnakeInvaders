#include "../Include/SnakeNode.hpp"

const float SnakeNode::Size = 10.f;

SnakeNode::SnakeNode(const sf::Vector2f& position)
: shape_({ Size, Size })
{
	shape_.setPosition(position);
	shape_.setFillColor(sf::Color::Green);
}

sf::FloatRect SnakeNode::getGlobalBounds() const
{
	return shape_.getGlobalBounds();
}

sf::FloatRect SnakeNode::getLocalBounds() const
{
	return shape_.getLocalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return shape_.getPosition();
}

void SnakeNode::setPosition(const sf::Vector2f& position)
{
	shape_.setPosition(position);
}

void SnakeNode::move(const sf::Vector2f& offset)
{
	shape_.move(offset);
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}