#include "../Include/Bullet.hpp"
#include "../Include/Game.hpp"

Bullet::Bullet(const sf::Vector2f& position, Game* game, Direction direction)
: Entity(position, game)
, Speed(300.f)
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
	Speed *= 1.05f;

	if (!outOfBounds())
	{
		switch (direction_)
		{
		case Direction::Left:
			sprite_.move(-Speed * delta.asSeconds(), 0.f);
			break;
		case Direction::Right:
			sprite_.move(Speed * delta.asSeconds(), 0.f);
			break;
		case Direction::Up:
			sprite_.move(0.f, -Speed * delta.asSeconds());
			break;
		case Direction::Down:
			sprite_.move(0.f, Speed * delta.asSeconds());
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