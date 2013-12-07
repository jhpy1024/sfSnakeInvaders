#include "../Include/Game.hpp"
#include "../Include/Spaceship.hpp"

Game::Game()
: Width(640)
, Height(480)
, Title("SnakeInvaders!")
, TimePerFrame(sf::seconds(1.f / 30.f))
, window_(sf::VideoMode(Width, Height), Title, sf::Style::Close)
, player_({ Width / 2.f, Height / 2.f }, this)
{
	textures_.addTexture("bullets", "Assets/bullets.png");
	textures_.addTexture("spaceship", "Assets/spaceship.png");
	textures_.addTexture("background", "Assets/stars.png");

	textures_.getTexture("background").setRepeated(true);
	bgSprite_.setTexture(textures_.getTexture("background"));
	bgSprite_.setPosition(0.f, 0.f);
	bgSprite_.setTextureRect(sf::IntRect(0, 0, Width, Height));

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			spaceships_.push_back(std::unique_ptr<Entity>(
				new Spaceship({ (72.f + 30.f) * i, (32.f + 10.f) * j }, this)));
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

	for (auto& ship : spaceships_)
		ship->update(delta);
}

void Game::render()
{
	window_.clear();
	window_.draw(bgSprite_);

	for (auto& ship : spaceships_)
		ship->render(window_);

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