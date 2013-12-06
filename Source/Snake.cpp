#include "../Include/Snake.hpp"
#include "../Include/Game.hpp"

Snake::Snake(const sf::Vector2f& position, Game* game, unsigned initialSize)
: position_(position)
, game_(game)
, direction_(Direction::Up)
{
	for (unsigned i = 0; i < initialSize; ++i)
	{
		nodes_.push_back(SnakeNode({ position.x, position.y + (SnakeNode::Size / 2) * i }));
	}
}

void Snake::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		direction_ = Direction::Up;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		direction_ = Direction::Down;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		direction_ = Direction::Left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		direction_ = Direction::Right;
}

void Snake::update(sf::Time delta)
{
	checkEdgeCollisions();
	move();
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto& node : nodes_)
		node.render(window);
}

bool Snake::hitTop() const
{
	return nodes_[0].getPosition().y < 0;
}

bool Snake::hitBottom() const
{
	return nodes_[0].getPosition().y > game_->getHeight() - SnakeNode::Size;
}

bool Snake::hitLeft() const
{
	return nodes_[0].getPosition().x < 0;
}

bool Snake::hitRight() const
{
	return nodes_[0].getPosition().x > game_->getWidth() - SnakeNode::Size;
}

void Snake::checkEdgeCollisions()
{
	if (hitLeft())
		nodes_[0].setPosition({ game_->getWidth() - SnakeNode::Size, nodes_[0].getPosition().y });
	else if (hitRight())
		nodes_[0].setPosition({ 0.f, nodes_[0].getPosition().y });

	if (hitTop())
		nodes_[0].setPosition({ nodes_[0].getPosition().x, game_->getHeight() - SnakeNode::Size });
	else if (hitBottom())
		nodes_[0].setPosition({ nodes_[0].getPosition().x, 0.f });
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}

	switch (direction_)
	{
	case Direction::Up:
		nodes_[0].move({ 0, -SnakeNode::Size });
		break;
	case Direction::Down:
		nodes_[0].move({ 0, SnakeNode::Size });
		break;
	case Direction::Left:
		nodes_[0].move({ -SnakeNode::Size, 0 });
		break;
	case Direction::Right:
		nodes_[0].move({ SnakeNode::Size, 0 });
		break;
	}
}

void Snake::grow()
{
	switch (direction_)
	{
	case Direction::Up:
		nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
			nodes_[nodes_.size() - 1].getPosition().y + SnakeNode::Size)));
		break;
	case Direction::Down:
		nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
			nodes_[nodes_.size() - 1].getPosition().y - SnakeNode::Size)));
		break;
	case Direction::Left:
		nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x + SnakeNode::Size,
			nodes_[nodes_.size() - 1].getPosition().y)));
		break;
	case Direction::Right:
		nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - SnakeNode::Size,
			nodes_[nodes_.size() - 1].getPosition().y)));
		break;
	}
}