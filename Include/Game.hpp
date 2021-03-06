#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <memory>
#include <stack>

#include "TextureHolder.hpp"
#include "AudioHolder.hpp"
#include "Screen.hpp"

class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();

	void quit();

	int getWidth() const;
	int getHeight() const;
	sf::Time getFps() const;
	
	std::stack<std::unique_ptr<Screen>>& getScreens();
	sf::RenderWindow& getWindow();

	TextureHolder& getTextureHolder();
	AudioHolder& getAudioHolder();

private:
	const int Width;
	const int Height;
	const std::string Title;
	const sf::Time TimePerFrame;
	sf::RenderWindow window_;
	std::stack<std::unique_ptr<Screen>> screens_;

	TextureHolder textures_;
	AudioHolder audio_;
};