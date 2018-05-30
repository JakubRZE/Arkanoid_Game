#pragma once

#include <SFML/Graphics.hpp>
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

	//sf::Sprite _background;
	sf::Text tittle;
	sf::RectangleShape playButton;
	sf::RectangleShape exitButton;

	
	
};

