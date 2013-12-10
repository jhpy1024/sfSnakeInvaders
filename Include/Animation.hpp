#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class Game;
class Animation
{
public:
	Animation(const std::string& textureName, const sf::Time& delay, unsigned numHorizontalFrames,
		unsigned numVerticalFrames, const sf::Vector2f& frameSize, Game* game);

	bool isFinished() const;

	void render(sf::RenderWindow& window);

	void setFrameSize(const sf::Vector2f& frameSize);
	void setHorizontalFrames(unsigned n);
	void setVerticalFrames(unsigned n);
	void setRepeated(bool flag);
	void setPosition(const sf::Vector2f& position);

private:
	void update();

private:
	sf::Sprite sprite_;
	sf::Texture texture_;
	sf::Time delay_;
	sf::Clock clock_;
	sf::Vector2f frameSize_;

	unsigned numHorizontalFrames_;
	unsigned numVerticalFrames_;

	unsigned horizontalPos_;
	unsigned verticalPos_;

	bool finished_;
	bool repeated_;

	Game* game_;
};