#include "../Include/Entity.hpp"
#include "../Include/Game.hpp"

Entity::Entity(const sf::Vector2f& position, Game* game, EntityType type)
: game_(game)
, type_(type)
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

EntityType Entity::getType() const
{
	return type_;
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