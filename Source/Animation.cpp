#include "../Include/Animation.hpp"
#include "../Include/Game.hpp"

Animation::Animation(const std::string& textureName, const sf::Time& delay, unsigned numHorizontalFrames,
	unsigned numVerticalFrames, const sf::Vector2f& frameSize, Game* game)
: delay_(delay)
, numHorizontalFrames_(numHorizontalFrames)
, numVerticalFrames_(numVerticalFrames)
, horizontalPos_(0)
, verticalPos_(0)
, frameSize_(frameSize)
, game_(game)
{
	sprite_.setTexture(game->getTextureHolder().getTexture(textureName));
	sprite_.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
	sprite_.setOrigin(sprite_.getLocalBounds().left + sprite_.getLocalBounds().width / 2.f,
		sprite_.getLocalBounds().top + sprite_.getLocalBounds().height / 2.f);
}

void Animation::update()
{
	// If the delay between frames is over
	if (clock_.getElapsedTime() >= delay_)
	{
		// If we are at the end column
		if (horizontalPos_ == numHorizontalFrames_ - 1)
		{
			horizontalPos_ = 0;
			++verticalPos_;

			// If we are on the bottom row
			if (verticalPos_ == numVerticalFrames_ - 1)
			{
				// If repeated, reset the positions to (0, 0)
				if (repeated_)
				{
					horizontalPos_ = 0;
					verticalPos_ = 0;
				}
				else
				{
					finished_ = true;
				}
			}
		}

		++horizontalPos_;

		// Update the area of the texture that is being rendered and reset the clock
		sprite_.setTextureRect(sf::IntRect(horizontalPos_ * frameSize_.x, verticalPos_ * frameSize_.y, frameSize_.x, frameSize_.y));
		clock_.restart();
	}
}

void Animation::render(sf::RenderWindow& window)
{
	update();

	window.draw(sprite_);
}

bool Animation::isFinished() const
{
	return finished_;
}

void Animation::setFrameSize(const sf::Vector2f& frameSize)
{
	frameSize_ = frameSize;
}

void Animation::setHorizontalFrames(unsigned n)
{
	numHorizontalFrames_ = n;
}

void Animation::setVerticalFrames(unsigned n)
{
	numVerticalFrames_ = n;
}

void Animation::setRepeated(bool flag)
{
	repeated_ = flag;
}

void Animation::setPosition(const sf::Vector2f& position)
{
	sprite_.setPosition(position);
}