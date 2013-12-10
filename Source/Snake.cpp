#include <cassert>
#include <iostream>

#include "../Include/Snake.hpp"
#include "../Include/Game.hpp"
#include "../Include/Spaceship.hpp"

Snake::Snake(const sf::Vector2f& position, Game* game, unsigned initialSize)
: Entity(position, game, EntityType::Snake)
, position_(position)
, game_(game)
, direction_(Direction::Up)
, canShoot_(true)
, FireRate(sf::seconds(0.25f))
{
	// The initial size should never be zero.
	assert(initialSize != 0);

	for (unsigned i = 0; i < initialSize; ++i)
	{
		nodes_.push_back(SnakeNode({ position.x, position.y + SnakeNode::Size * i }));
	}
}

void Snake::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		fireBullet();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		direction_ = Direction::Up;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		direction_ = Direction::Down;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		direction_ = Direction::Left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		direction_ = Direction::Right;
}

void Snake::fireBullet()
{
	if (canShoot_)
	{
		Bullet::Direction bulletDirection;
		switch (direction_)
		{
		case Direction::Left:
			bulletDirection = Bullet::Direction::Left;
			break;
		case Direction::Right:
			bulletDirection = Bullet::Direction::Right;
			break;
		case Direction::Up:
			bulletDirection = Bullet::Direction::Up;
			break;
		case Direction::Down:
			bulletDirection = Bullet::Direction::Down;
			break;
		}
	
		bullets_.push_back(Bullet(nodes_[0].getPosition(), game_, bulletDirection, EntityType::SnakeBullet));
		lastFireTime_ = fireClock_.getElapsedTime();
	}
}

void Snake::update(sf::Time delta)
{
	for (auto it = bullets_.begin(); it != bullets_.end(); ++it)
	{
		if (it->outOfBounds())
			bulletsToErase_.push_back(std::distance(bullets_.begin(), it));

		checkBulletCollisions(std::distance(bullets_.begin(), it));
		it->update(delta);
	}

	for (auto& it: bulletsToErase_)
	{
		if (it != bullets_.size())
			bullets_.erase(bullets_.begin() + it);
	}
	bulletsToErase_.clear();

	checkEdgeCollisions();
	checkEnemyBulletCollisions();
	move(delta);

	canShoot_ = fireClock_.getElapsedTime() - lastFireTime_ >= FireRate;
}

void Snake::checkEnemyBulletCollisions()
{
	for (auto& spaceship : game_->getSpaceships())
	{
		for (auto& bullet : static_cast<Spaceship*>(spaceship.get())->getBullets())
		{
			for (auto& node : nodes_)
			{
				if (bullet.getGlobalBounds().intersects(node.getGlobalBounds()))
					hitByEnemyBullet();
			}
		}
	}
}

void Snake::hitByEnemyBullet()
{
	std::cout << "Player hit by enemy bullet" << std::endl;
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto& bullet : bullets_)
		bullet.render(window);
	for (auto& node : nodes_)
		node.render(window);
}

void Snake::checkBulletCollisions(std::vector<Bullet>::size_type bullet)
{
	for (auto& spaceship : game_->getSpaceships())
	{
		if (bullets_[bullet].getGlobalBounds().intersects(spaceship->getGlobalBounds()))
		{
			static_cast<Spaceship*>(spaceship.get())->hitByPlayerBullet();
			bulletsToErase_.push_back(bullet);
		}
	}
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

void Snake::move(sf::Time delta)
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}

	switch (direction_)
	{
	case Direction::Up:
		nodes_[0].move({ 0.f, -SnakeNode::Size });
		break;
	case Direction::Down:
		nodes_[0].move({ 0.f, SnakeNode::Size });
		break;
	case Direction::Left:
		nodes_[0].move({ -SnakeNode::Size, 0.f });
		break;
	case Direction::Right:
		nodes_[0].move({ SnakeNode::Size, 0.f });
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