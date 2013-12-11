#include "../Include/Game.hpp"
#include "../Include/GameScreen.hpp"

#include <iostream>

Game::Game()
: Width(640)
, Height(480)
, Title("SnakeInvaders!")
, TimePerFrame(sf::seconds(1.f / 30.f))
, window_(sf::VideoMode(Width, Height), Title, sf::Style::Close)
{
	textures_.addTexture("bullets", "Assets/bullets.png");
	textures_.addTexture("spaceship", "Assets/spaceship.png");
	textures_.addTexture("background", "Assets/stars.png");
	textures_.addTexture("enemyBullets", "Assets/enemyBullets.png");
	textures_.addTexture("explosion", "Assets/explosion.png");

	screens_.push(std::unique_ptr<Screen>(new GameScreen(this)));
}

std::stack<std::unique_ptr<Screen>>& Game::getScreens()
{
	return screens_;
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}

	if (!screens_.empty())
		screens_.top()->handleInput();
}

void Game::update(sf::Time delta)
{
	if (!screens_.empty())
		screens_.top()->update(delta);
}

void Game::render()
{
	window_.clear();

	if (!screens_.empty())
		screens_.top()->render(window_);

	window_.display();
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