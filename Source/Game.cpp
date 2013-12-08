#include "../Include/Game.hpp"
#include "../Include/Spaceship.hpp"

Game::Game()
: Width(640)
, Height(480)
, Title("SnakeInvaders!")
, TimePerFrame(sf::seconds(1.f / 30.f))
, NumShipRows(3)
, NumShipColumns(5)
, ShipSpeed(125.f)
, LeftShipPadding(30)
, RightShipPadding(500)
, TopShipPadding(10)
, BottomShipPadding(Height / 2)
, ShipHorizontalSpacing(30)
, ShipVerticalSpacing(10)
, shipHorizontalDirection_(1) // 1 == right, -1 == left
, shipVerticalDirection_(1) // 1 == down, -1 == up
, shipsMoveVertical_(false)
, window_(sf::VideoMode(Width, Height), Title, sf::Style::Close)
, player_({ Width / 2.f, Height / 2.f }, this)
{
	textures_.addTexture("bullets", "Assets/bullets.png");
	textures_.addTexture("spaceship", "Assets/spaceship.png");
	textures_.addTexture("background", "Assets/stars.png");
	textures_.addTexture("enemyBullets", "Assets/enemyBullets.png");

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

	// If the rightmost ship is near the right edge of the screen, flip the direction
	// of the ships and move them down.
	if (spaceships_[NumShipColumns]->getPosition().x >= Width - RightShipPadding)
	{
		shipHorizontalDirection_ = -1;
		shipsMoveVertical_ = true;
	}

	// If the leftmost ship is near the left edge of the screen, flip the direction
	// of the ships and move them down.
	else if (spaceships_[0]->getPosition().x <= LeftShipPadding)
	{
		shipHorizontalDirection_ = 1;
		shipsMoveVertical_ = true;
	}

	// The ships aren't at an edge, don't move down.
	else
	{
		shipsMoveVertical_ = false;
	}

	// If the bottommost ship is at the center of the screen, start moving
	// back upwards.
	if (spaceships_[NumShipColumns * NumShipRows - 1]->getPosition().y >= BottomShipPadding)
	{
		shipsMoveVertical_ = true;
		shipVerticalDirection_ = -1;
	}

	// If the topmost ship is near the top of the screen, start moving downwards.
	else if (spaceships_[0]->getPosition().y <= TopShipPadding)
	{
		shipsMoveVertical_ = true;
		shipVerticalDirection_ = 1;
	}

	for (auto& ship : spaceships_)
	{
		ship->move({ ShipSpeed * shipHorizontalDirection_ * delta.asSeconds(),
			(shipsMoveVertical_ ? ShipSpeed * shipVerticalDirection_ * delta.asSeconds() : 0.f) });
		ship->update(delta);
	}
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