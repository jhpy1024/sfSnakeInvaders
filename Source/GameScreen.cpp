#include <Thor/Math/Distributions.hpp>
#include <Thor/Graphics.hpp>
#include <Thor/Animation.hpp>

#include "../Include/GameScreen.hpp"
#include "../Include/GameOverScreen.hpp"
#include "../Include/WinScreen.hpp"
#include "../Include/Game.hpp"
#include "../Include/Spaceship.hpp"

GameScreen::GameScreen(Game* game)
: Screen(game)
, NumShipRows(3)
, NumShipColumns(5)
, ShipHorizontalSpacing(30)
, ShipVerticalSpacing(10)
, player_({ game->getWidth() / 2.f, game->getHeight() / 2.f }, game)
, lifeBarScale_(6.4f) // Window width divided by player life (640 / 100)
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

	lifeBar_.setSize({ static_cast<float>(player_.getLife()) * lifeBarScale_, 20.f });
	lifeBar_.setPosition(0, game_->getHeight() - lifeBar_.getSize().y);
	lifeBar_.setFillColor(sf::Color::Green);

	particleSystem_.setTexture(game_->getTextureHolder().getTexture("fireParticle"));
	thor::ColorGradient gradient;
	gradient[0.f] = sf::Color::Red;
	gradient[0.3f] = sf::Color(165, 0, 0); // Orange
	gradient[1.f] = sf::Color(255, 255, 0); // Yellow
	thor::ColorAnimation colorizer(gradient);
	thor::FadeAnimation fader(0.1f, 0.1f);

	particleSystem_.addAffector(thor::AnimationAffector(colorizer));
	particleSystem_.addAffector(thor::AnimationAffector(fader));
}

thor::UniversalEmitter GameScreen::createEmitter(const sf::Vector2f& position)
{
	thor::UniversalEmitter emitter;

	emitter.setEmissionRate(10000.f);
	emitter.setParticleLifetime(sf::seconds(1.f));
	emitter.setParticlePosition(thor::Distributions::circle({ position.x, position.y }, 15.f));
	emitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));
	float xVel = rand() % 100 + 10;
	float yVel = rand() % 100 + 10;
	emitter.setParticleVelocity(thor::Distributions::deflect({ xVel, yVel }, 360));

	return emitter;
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
	lifeBar_.setSize({ player_.getLife() * lifeBarScale_, lifeBar_.getSize().y });

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
	particleSystem_.update(delta);
}

void GameScreen::updateShips(sf::Time delta)
{
	if (spaceships_.size() == 0)
		game_->getScreens().push(std::unique_ptr<Screen>(new WinScreen(game_)));

	for (auto it = spaceships_.begin(); it != spaceships_.end(); ++it)
	{
		if (static_cast<Spaceship*>(it->get())->isDead())
		{
			Animation explosion("explosion", sf::milliseconds(10), 8, 8, { 128, 128 }, game_);
			explosion.setPosition({ (*it)->getPosition().x + (*it)->getLocalBounds().width / 2.f,
				(*it)->getPosition().y });
			animations_.push_back(explosion);
			sf::Vector2f particlePos = { (*it)->getPosition().x + (*it)->getGlobalBounds().width / 2.f,
				(*it)->getPosition().y + (*it)->getGlobalBounds().height / 2.f };
			particleSystem_.addEmitter(createEmitter(particlePos), sf::milliseconds(200));
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
	window.draw(lifeBar_);
	window.draw(particleSystem_);

	for (auto& ship : spaceships_)
		ship->render(window);
	for (auto& anim : animations_)
		anim.render(window);

	player_.render(window);
}