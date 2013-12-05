#include "../Include/Entity.hpp"

Entity::Entity(const sf::Vector2f& position, std::shared_ptr<Game> game)
: game_(game)
{
	sprite_.setPosition(position);
}

void Entity::setPosition(const sf::Vector2f& position)
{
	sprite_.setPosition(position);
}

void Entity::move(const sf::Vector2f& offset)
{
	sprite_.move(offset);
}

sf::Vector2f Entity::getPosition() const
{
	return sprite_.getPosition();
}

sf::FloatRect Entity::getLocalBounds() const
{
	return sprite_.getLocalBounds();
}

sf::FloatRect Entity::getGlobalBounds() const
{
	return sprite_.getGlobalBounds();
}