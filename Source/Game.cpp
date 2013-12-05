#include "../Include/Game.hpp"

Game::Game()
: Width(640)
, Height(480)
, Title("SnakeInvaders!")
, TimePerFrame(sf::seconds(1.f / 60.f))
, window_(sf::VideoMode(Width, Height), Title, sf::Style::Close)
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
}

void Game::update(sf::Time delta)
{

}

void Game::render()
{
	window_.clear();

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