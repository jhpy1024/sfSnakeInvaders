#pragma once

#include "Screen.hpp"

class Game;
class WinScreen : public Screen
{
public:
	WinScreen(Game* game);

	void handleInput() override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

private:
	sf::Sprite quitBtn_;
	sf::Sprite retryBtn_;
	sf::Sprite msgSprite_;

	sf::IntRect mouseRect_;
};