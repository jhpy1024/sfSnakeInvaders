#include "../Include/Game.hpp"
#include "../Include/Spaceship.hpp"

#include <iostream>

Game::Game()
: Width(640)
, Height(480)
, Title("SnakeInvaders!")
, TimePerFrame(sf::seconds(1.f / 30.f))
, NumShipRows(3)
, NumShipColumns(5)
, ShipHorizontalSpacing(30)
, ShipVerticalSpacing(10)
, window_(sf::VideoMode(Width, Height), Title, sf::Style::Close)
, player_({ Width / 2.f, Height / 2.f }, this)
{
	textures_.addTexture("bullets", "Assets/bullets.png");
	textures_.addTexture("spaceship", "Assets/spaceship.png");
	textures_.addTexture("background", "Assets/stars.png");
	textures_.addTexture("enemyBullets", "Assets/enemyBullets.png");
	textures_.addTexture("explosion", "Assets/explosion.png");

	textures_.getTexture("background").setRepeated(true);
	bgSprite_.setTexture(textures_.getTexture("background"));
	bgSprite_.setPosition(0.f, 0.f);
	bgSprite_.setTextureRect(sf::IntRect(0, 0, Width, Height));

	for (unsigned y = 0; y < NumShipRows; ++y)
	{
		for (unsigned x = 1; x < NumShipColumns + 1; ++x)
		{
			spaceships_.push_back(std::unique_ptr<Entity>(
				new Spaceship({ static_cast<float>((Spaceship::Width + ShipHorizontalSpacing) * x),
				static_cast<float>((Spaceship::Height + ShipVerticalSpacing) * y) }, this)));
		}
	}

}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}

	player_.handleInput();
}

void Game::update(sf::Time delta)
{
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
		if (index != animsToRemove_.size() - 1)
			animations_.erase(animations_.begin() + index);
	}
	animsToRemove_.clear();

	updateShips(delta);
}

void Game::updateShips(sf::Time delta)
{
	for (auto it = spaceships_.begin(); it != spaceships_.end(); ++it)
	{
		if (static_cast<Spaceship*>(it->get())->isDead())
		{
			Animation explosion("explosion", sf::milliseconds(10), 8, 8, { 128, 128 }, this);
			explosion.setPosition({ (*it)->getPosition().x + (*it)->getLocalBounds().width / 2.f, 
				(*it)->getPosition().y });
			animations_.push_back(explosion);
			static_cast<Spaceship*>(it->get())->setDead(false);
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

void Game::render()
{
	window_.clear();
	window_.draw(bgSprite_);

	for (auto& ship : spaceships_)
		ship->render(window_);
	for (auto& anim : animations_)
		anim.render(window_);

	player_.render(window_);

	window_.display();
}

std::vector<std::unique_ptr<Entity>>& Game::getSpaceships()
{
	return spaceships_;
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate;

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}

int Game::getWidth() const
{
	return Width;
}

int Game::getHeight() const
{
	return Height;
}

TextureHolder& Game::getTextureHolder()
{
	return textures_;
}

sf::Time Game::getFps() const
{
	return TimePerFrame;
}