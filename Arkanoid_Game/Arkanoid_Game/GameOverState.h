#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.h"
#include "Game.h" 
#include "Ball.h"


class GameOverState : public State
{
public:
	GameOverState(GameDataRef data, int _score);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);



private:
	GameDataRef _data;

	//sf::Sprite _background;

	//delta time clock
	sf::Clock GameStateframeClock;

};
