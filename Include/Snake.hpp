#pragma once

#include <Thor/Particles/ParticleSystem.hpp>
#include <Thor/Particles/Emitters.hpp>

#include <memory>

#include "SnakeNode.hpp"
#include "Bullet.hpp"

class Game;
class Snake : public Entity
{
public:
	Snake(const sf::Vector2f& position, Game* game, unsigned initialSize = 5U);

	void handleInput() override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	int getLife() const;
	bool isDead() const;

private:
	void grow();
	void hitByBullet(std::vector<SnakeNode>::iterator nodeHit);
	void move(sf::Time delta);
	void checkEdgeCollisions();
	void checkBulletCollisions(std::vector<Bullet>::size_type bullet);
	void checkEnemyBulletCollisions();
	void fireBullet();

	bool hitTop() const;
	bool hitBottom() const;
	bool hitLeft() const;
	bool hitRight() const;

	thor::UniversalEmitter createEmitter(const sf::Vector2f& position);

private:
	enum class Direction { Left, Right, Up, Down };
	Direction direction_;

	sf::Vector2f position_;

	std::vector<SnakeNode> nodes_;
	std::vector<Bullet> bullets_;
	std::vector<std::vector<Bullet>::size_type> bulletsToErase_;
		
	bool canShoot_;
	sf::Clock fireClock_;
	sf::Time lastFireTime_;
	const sf::Time FireRate;

	int life_;
	int score_;
	sf::Time lastTimeShot_;
	const sf::Time TakeDamageDelay;

	Game* game_;

	thor::ParticleSystem particleSystem_;
	sf::Clock particleClock_;
};