#pragma once

#include <vector>
#include <random>

#include "Entity.hpp"
#include "Bullet.hpp"

class Spaceship : public Entity
{
public:
	Spaceship(const sf::Vector2f& position, Game* game);

	void handleInput() override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	std::vector<Bullet>& getBullets();

	static const int Width;
	static const int Height;

	void hitByPlayerBullet();
	bool isDead() const;
	void setDead(bool flag);
	
private:
	void fireBullet();
	bool shouldShoot() const;
	sf::IntRect randomBulletColor() const;

private:
	const unsigned NumFrames;
	unsigned currentFrame_;
	
	const sf::Time AnimationDelay;
	sf::Clock animationClock_;
	sf::Time lastAnimTime_;

	std::vector<Bullet> bullets_;
	std::vector<std::vector<Bullet>::iterator> bulletsToErase_;
	sf::Clock fireClock_;
	sf::Time lastFireTime_;
	sf::Time fireRate_;
	bool canShoot_;
	const sf::Time BaseFireRate;

	static bool engineSeeded_;

	bool isDead_;

	const unsigned NumColors;
};