#include <cassert>
#include <iostream>

#include <Thor/Math/Distributions.hpp>
#include <Thor/Graphics/ColorGradient.hpp>
#include <Thor/Animation.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Time.hpp>

#include "../Include/Snake.hpp"
#include "../Include/Game.hpp"
#include "../Include/GameScreen.hpp"
#include "../Include/Spaceship.hpp"

Snake::Snake(const sf::Vector2f& position, Game* game, unsigned initialSize)
: Entity(position, game, EntityType::Snake)
, position_(position)
, game_(game)
, direction_(Direction::Up)
, canShoot_(true)
, life_(100)	
, score_(0)
, FireRate(sf::seconds(0.25f))
, TakeDamageDelay(sf::seconds(0.4f))
{
	// The initial size should never be zero.
	assert(initialSize != 0);

	for (unsigned i = 0; i < initialSize; ++i)
	{	
		nodes_.push_back(SnakeNode({ position.x, position.y + SnakeNode::Size * i }, (i == 0 ? true : false)));
	}

	srand(time(NULL));

	particleSystem_.setTexture(game_->getTextureHolder().getTexture("particle"));
	thor::ColorGradient gradient;
	gradient[0.f] = sf::Color::Green;
	gradient[0.5f] = sf::Color::Red;
	gradient[1.f] = sf::Color::Black;
	thor::ColorAnimation colorizer(gradient);
	thor::FadeAnimation fader(0.1f, 0.1f);

	particleSystem_.addAffector(thor::AnimationAffector(colorizer));
	particleSystem_.addAffector(thor::AnimationAffector(fader));

}

thor::UniversalEmitter Snake::createEmitter(const sf::Vector2f& position)
{
	thor::UniversalEmitter emitter;

	emitter.setEmissionRate(300.f);
	emitter.setParticleLifetime(sf::seconds(1.f));
	emitter.setParticlePosition(thor::Distributions::circle({ position.x, position.y }, 30.f));
	emitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));
	float xVel = rand() % 360 + 120;
	float yVel = rand() % 360 + 120;
	emitter.setParticleVelocity(thor::Distributions::deflect({ xVel, yVel }, 360));

	return emitter;
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

int Snake::getLife() const
{
	return life_;
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
	if (life_ <= 0)
		return;

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

	particleSystem_.update(delta);
}

bool Snake::isDead() const
{
	return life_ <= 0;
}

void Snake::checkEnemyBulletCollisions()
{
	for (auto& spaceship : static_cast<GameScreen*>(game_->getScreens().top().get())->getSpaceships())
	{
		for (auto& bullet : static_cast<Spaceship*>(spaceship.get())->getBullets())
		{
			for (auto it = nodes_.begin(); it != nodes_.end(); ++it)
			{
				if (it->getGlobalBounds().intersects(bullet.getGlobalBounds()))
				{
					hitByBullet(it);
				}
			}
		}
	}
}

void Snake::hitByBullet(std::vector<SnakeNode>::iterator nodeHit)
{
	if (fireClock_.getElapsedTime() - lastTimeShot_ >= TakeDamageDelay)
	{
		life_ -= 10;
		lastTimeShot_ = fireClock_.getElapsedTime();
		particleSystem_.addEmitter(createEmitter(nodeHit->getPosition()), sf::milliseconds(200));
	}
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto& bullet : bullets_)
		bullet.render(window);
	for (auto& node : nodes_)
		node.render(window);

	window.draw(particleSystem_);
}

void Snake::checkBulletCollisions(std::vector<Bullet>::size_type bullet)
{
	for (auto& spaceship : static_cast<GameScreen*>(game_->getScreens().top().get())->getSpaceships())
	{
		if (bullets_[bullet].getGlobalBounds().intersects(spaceship->getGlobalBounds()))
		{
			static_cast<Spaceship*>(spaceship.get())->hitByPlayerBullet();
			bulletsToErase_.push_back(bullet);
			grow();
			score_ += 10;
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