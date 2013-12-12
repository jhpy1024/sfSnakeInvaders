#pragma once

#include <memory>

#include "Screen.hpp"
#include "Entity.hpp"
#include "Animation.hpp"
#include "Snake.hpp"

class Game;
class GameScreen : public Screen
{
public:
	GameScreen(Game* game);

	void handleInput() override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	std::vector<std::unique_ptr<Entity>>& getSpaceships();

private:
	void updateShips(sf::Time delta);

private:
	const unsigned NumShipRows;
	const unsigned NumShipColumns;
	const int ShipHorizontalSpacing;
	const int ShipVerticalSpacing;

	std::vector<std::unique_ptr<Entity>> spaceships_;
	std::vector<std::vector<std::unique_ptr<Entity>>::size_type> shipsToRemove_;
	std::vector<Animation> animations_;
	std::vector<std::vector<Animation>::size_type> animsToRemove_;

	sf::Sprite bgSprite_;
	sf::RectangleShape lifeBar_;
	float lifeBarScale_;

	Snake player_;
};