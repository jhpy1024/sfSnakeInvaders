#pragma once

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

	bool isDead() const;

private:
	void grow();
	void move(sf::Time delta);
	void checkEdgeCollisions();
	void checkBulletCollisions(std::vector<Bullet>::size_type bullet);
	void checkEnemyBulletCollisions();
	void fireBullet();

	bool hitTop() const;
	bool hitBottom() const;
	bool hitLeft() const;
	bool hitRight() const;

private:
	enum class Direction { Left, Right, Up, Down };
	Direction direction_;

	sf::Vector2f position_;

	std::vector<SnakeNode> nodes_;
	std::vector<std::vector<SnakeNode>::size_type> nodesToRemove_;
	std::vector<Bullet> bullets_;
	std::vector<std::vector<Bullet>::size_type> bulletsToErase_;
		
	bool canShoot_;
	sf::Clock fireClock_;
	sf::Time lastFireTime_;
	const sf::Time FireRate;

	bool dead_;

	Game* game_;
};