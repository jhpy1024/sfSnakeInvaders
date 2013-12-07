#include "../Include/Bullet.hpp"
#include "../Include/Game.hpp"

Bullet::Bullet(const sf::Vector2f& position, Game* game, Direction direction)
: Entity(position, game)
, speed_(300.f)
, acceleration_(1.1f)
, direction_(direction)
, outOfBounds_(false)
{
	sprite_.setTexture(game_->getTextureHolder().getTexture("bullets"));

	switch (direction)
	{
	case Direction::Left:
	case Direction::Right:
		sprite_.setTextureRect(sf::IntRect(0, 0, 30, 12));
		break;
	case Direction::Up:
	case Direction::Down:
		sprite_.setTextureRect(sf::IntRect(30, 0, 12, 30));
		break;
	}
}

void Bullet::handleInput()
{

}

void Bullet::update(sf::Time delta)
{
	speed_ *= acceleration_;

	if (!outOfBounds())
	{
		switch (direction_)
		{
		case Direction::Left:
			sprite_.move(-speed_ * delta.asSeconds(), 0.f);
			break;
		case Direction::Right:
			sprite_.move(speed_ * delta.asSeconds(), 0.f);
			break;
		case Direction::Up:
			sprite_.move(0.f, -speed_ * delta.asSeconds());
			break;
		case Direction::Down:
			sprite_.move(0.f, speed_ * delta.asSeconds());
			break;
		}
	}
}

bool Bullet::outOfBounds() const
{
	return getPosition().x < 0
		|| getPosition().x > game_->getWidth()
		|| getPosition().y < 0
		|| getPosition().y > game_->getHeight();
}

void Bullet::render(sf::RenderWindow& window)
{
	window.draw(sprite_);
}