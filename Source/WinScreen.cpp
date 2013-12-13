#include "../Include/WinScreen.hpp"
#include "../Include/GameScreen.hpp"
#include "../Include/Game.hpp"

WinScreen::WinScreen(Game* game)
: Screen(game)
{
	quitBtn_.setTexture(game->getTextureHolder().getTexture("quitBtn"));
	quitBtn_.setOrigin(quitBtn_.getLocalBounds().left + quitBtn_.getLocalBounds().width / 2,
		quitBtn_.getLocalBounds().top + quitBtn_.getLocalBounds().height / 2);
	quitBtn_.setPosition(game->getWidth() / 2 - quitBtn_.getLocalBounds().width / 1.5, game->getHeight() * 0.9f);

	retryBtn_.setTexture(game->getTextureHolder().getTexture("retryBtn"));
	retryBtn_.setOrigin(retryBtn_.getLocalBounds().left + retryBtn_.getLocalBounds().width / 2,
		retryBtn_.getLocalBounds().top + retryBtn_.getLocalBounds().height / 2);
	retryBtn_.setPosition(game->getWidth() / 2 + retryBtn_.getLocalBounds().width / 1.5, game->getHeight() * 0.9f);

	msgSprite_.setTexture(game->getTextureHolder().getTexture("winMsg"));
	msgSprite_.setOrigin(msgSprite_.getLocalBounds().left + msgSprite_.getLocalBounds().width / 2,
		msgSprite_.getLocalBounds().top + msgSprite_.getLocalBounds().height / 2);
	msgSprite_.setPosition(game->getWidth() / 2, game->getHeight() * 0.1f);

	mouseRect_.width = 1;
	mouseRect_.height = 1;
}

void WinScreen::handleInput()
{
	mouseRect_.left = sf::Mouse::getPosition(game_->getWindow()).x;
	mouseRect_.top = sf::Mouse::getPosition(game_->getWindow()).y;
}

void WinScreen::update(sf::Time delta)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (mouseRect_.intersects(static_cast<sf::IntRect>(retryBtn_.getGlobalBounds())))
			game_->getScreens().push(std::unique_ptr<Screen>(new GameScreen(game_)));
		else if (mouseRect_.intersects(static_cast<sf::IntRect>(quitBtn_.getGlobalBounds())))
			game_->quit();
	}
}

void WinScreen::render(sf::RenderWindow& window)
{
	window.draw(quitBtn_);
	window.draw(retryBtn_);
	window.draw(msgSprite_);
}