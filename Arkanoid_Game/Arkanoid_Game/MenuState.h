#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h" 

class MenuState: public State
{
public:
	MenuState(GameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;

	sf::Sprite _background;
	sf::Text tittle;
	sf::Text playText;
	sf::Text exitText;
	sf::Text author;
	sf::RectangleShape playButton;
	sf::RectangleShape exitButton;
	sf::Sprite muteButton;
	sf::Music bgMusic;

	bool mute = false;
	
};

