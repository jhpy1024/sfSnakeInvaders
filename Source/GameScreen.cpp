#include "../Include/GameScreen.hpp"
#include "../Include/GameOverScreen.hpp"
#include "../Include/Game.hpp"
#include "../Include/Spaceship.hpp"

GameScreen::GameScreen(Game* game)
: Screen(game)
, NumShipRows(3)
, NumShipColumns(5)
, ShipHorizontalSpacing(30)
, ShipVerticalSpacing(10)
, player_({ game->getWidth() / 2.f, game->getHeight() / 2.f }, game)
{
	game->getTextureHolder().getTexture("background").setRepeated(true);
	bgSprite_.setTexture(game->getTextureHolder().getTexture("background"));
	bgSprite_.setPosition(0.f, 0.f);
	bgSprite_.setTextureRect(sf::IntRect(0, 0, game->getWidth(), game->getHeight()));

	for (unsigned y = 0; y < NumShipRows; ++y)
	{
		for (unsigned x = 1; x < NumShipColumns + 1; ++x)
		{
			spaceships_.push_back(std::unique_ptr<Entity>(
				new Spaceship({ static_cast<float>((Spaceship::Width + ShipHorizontalSpacing) * x),
				static_cast<float>((Spaceship::Height + ShipVerticalSpacing) * y) }, game)));
		}
	}

}

void GameScreen::handleInput()
{
	player_.handleInput();
}

void GameScreen::update(sf::Time delta)
{
	if (player_.isDead())
	{
		game_->getScreens().push(std::unique_ptr<Screen>(new GameOverScreen(game_)));

	}

	player_.update(delta);

	for (auto it = animations_.begin(); it != animations_.end(); ++it)
	{
		if (it->isFinished())
		{
			animsToRemove_.push_back(std::distance(animations_.begin(), it));
		}
	}

	for (auto index : animsToRemove_)
	{
		if (index != animsToRemove_.size())
			animations_.erase(animations_.begin() + index);
	}
	animsToRemove_.clear();

	updateShips(delta);
}

void GameScreen::updateShips(sf::Time delta)
{
	for (auto it = spaceships_.begin(); it != spaceships_.end(); ++it)
	{
		if (static_cast<Spaceship*>(it->get())->isDead())
		{
			Animation explosion("explosion", sf::milliseconds(10), 8, 8, { 128, 128 }, game_);
			explosion.setPosition({ (*it)->getPosition().x + (*it)->getLocalBounds().width / 2.f,
				(*it)->getPosition().y });
			animations_.push_back(explosion);
			shipsToRemove_.push_back(std::distance(spaceships_.begin(), it));
		}

		(*it)->update(delta);
	}

	for (auto ship : shipsToRemove_)
	{
		if (ship != spaceships_.size())
		{
			spaceships_.erase(spaceships_.begin() + ship);
		}
	}
	shipsToRemove_.clear();
}

std::vector<std::unique_ptr<Entity>>& GameScreen::getSpaceships()
{
	return spaceships_;
}

void GameScreen::render(sf::RenderWindow& window)
{
	window.draw(bgSprite_);

	for (auto& ship : spaceships_)
		ship->render(window);
	for (auto& anim : animations_)
		anim.render(window);

	player_.render(window);
}