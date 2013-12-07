#include <ctime>

#include "../Include/Spaceship.hpp"
#include "../Include/Game.hpp"

Spaceship::Spaceship(const sf::Vector2f& position, Game* game)
: Entity(position, game)
, NumFrames(12)
, Width(58)
, Height(34)
, AnimationDelay(sf::milliseconds(5))
, currentFrame_(0)
{
	sprite_.setTexture(game_->getTextureHolder().getTexture("spaceship"));
	sprite_.setTextureRect(sf::IntRect(0, 0, Width, Height));
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
		
		sprite_.setTextureRect(sf::IntRect(currentFrame_ * Width, 0, Width, Height));
	}
}

void Spaceship::render(sf::RenderWindow& window)
{
	window.draw(sprite_);
}