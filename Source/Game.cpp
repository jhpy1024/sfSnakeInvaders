#include "../Include/Game.hpp"

Game::Game()
: Width(640)
, Height(480)
, Title("SnakeInvaders!")
, TimePerFrame(sf::seconds(1.f / 10.f))
, window_(sf::VideoMode(Width, Height), Title, sf::Style::Close)
, player_({ Width / 2.f, Height / 2.f }, this)
{
	
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
}

void Game::render()
{
	window_.clear();
	player_.render(window_);
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