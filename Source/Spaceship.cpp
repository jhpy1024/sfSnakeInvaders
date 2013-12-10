#include <ctime>

#include "../Include/Spaceship.hpp"
#include "../Include/Game.hpp"
#include <iostream>

const int Spaceship::Width = 58;
const int Spaceship::Height = 34;
bool Spaceship::engineSeeded_ = false;

Spaceship::Spaceship(const sf::Vector2f& position, Game* game)
: Entity(position, game, EntityType::Spaceship)
, NumFrames(12)
, AnimationDelay(sf::milliseconds(5))
, currentFrame_(0)
, canShoot_(false)
, BaseFireRate(sf::milliseconds(4000))
, NumColors(4)
, isDead_(false)
{
	sprite_.setTexture(game_->getTextureHolder().getTexture("spaceship"));
	sprite_.setTextureRect(sf::IntRect(0, 0, Width, Height));

	static std::default_random_engine engine;
	static std::uniform_int_distribution<int> distribution(-1000, 1000);

	if (!engineSeeded_)
	{
		srand(time(NULL));
		engine.seed(time(NULL));
		engineSeeded_ = true;
	}
	
	fireRate_ = sf::milliseconds(BaseFireRate.asMilliseconds() + distribution(engine));
	if (fireRate_.asMilliseconds() < 0)
		fireRate_ = -fireRate_;
}

bool Spaceship::isDead() const
{
	return isDead_;
}

void Spaceship::setDead(bool flag)
{
	isDead_ = flag;
}

std::vector<Bullet>& Spaceship::getBullets()
{
	return bullets_;
}

void Spaceship::hitByPlayerBullet()
{
	isDead_ = true;
}

void Spaceship::handleInput()
{

}

void Spaceship::update(sf::Time delta)
{
	if (animationClock_.getElapsedTime() - lastAnimTime_ >= AnimationDelay)
	{
		currentFrame_ = (currentFrame_ + 1) % NumFrames;
		lastAnimTime_ = animationClock_.getElapsedTime();
		
		sprite_.setTextureRect(sf::IntRect(currentFrame_ * Width, sprite_.getTextureRect().top, Width, Height));
	}

	for (auto it = bullets_.begin(); it != bullets_.end(); ++it)
	{
		if (it->outOfBounds())
			bulletsToErase_.push_back(it);

		it->update(delta);
	}

	for (auto& it : bulletsToErase_)
	{
		if (it != bullets_.end())
			bullets_.erase(it);
	}
	bulletsToErase_.clear();

	canShoot_ = fireClock_.getElapsedTime() - lastFireTime_ >= fireRate_;

	if (canShoot_ && shouldShoot())
		fireBullet();

	if (fireClock_.getElapsedTime() - lastFireTime_ >= sf::seconds(0.3f))
		sprite_.setTextureRect(sf::IntRect(currentFrame_ * Width, 0, Width, Height));
}

bool Spaceship::shouldShoot() const
{
	return (rand() % 100) < 5;
}

sf::IntRect Spaceship::randomBulletColor() const
{
	sf::IntRect rect;
	rect.width = game_->getTextureHolder().getTexture("enemyBullets").getSize().x;
	rect.height = game_->getTextureHolder().getTexture("enemyBullets").getSize().y / NumColors;
	rect.left = 0;
	rect.top = (rand() % NumColors) * rect.height;

	return rect;
}

void Spaceship::fireBullet()
{
	bullets_.push_back(Bullet({sprite_.getPosition().x + Width / 2.f, sprite_.getPosition().y + Height},
		game_, Bullet::Direction::Down, EntityType::ShipBullet, "enemyBullets"));
	bullets_.back().setTextureRect(randomBulletColor());
	lastFireTime_ = fireClock_.getElapsedTime();
	sprite_.setTextureRect(sf::IntRect(sprite_.getTextureRect().left, Height, Width, Height));
}

void Spaceship::render(sf::RenderWindow& window)
{
	for (auto& bullet : bullets_)
		bullet.render(window);

	window.draw(sprite_);
}
