#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.h"
#include "Game.h" 
#include "Ball.h"
#include "HeadsUpDisplay.h"
#include "GameOverState.h"
#include "PauseState.h"


class GameState: public State
{
public:
	GameState(GameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

	//-------builds scene-----//
	void createSolidObjects(std::vector<sf::RectangleShape>& shapes);
	void createCircleObjects(std::vector<sf::CircleShape>& shapes);

	bool nextLevel();

private:

	sf::Clock GameStateframeClock;
	GameDataRef _data;

	sf::Sprite _background;
	sf::RectangleShape win_scr;
	
	std::vector<sf::RectangleShape> solidObjects;
	std::vector<sf::CircleShape> circleObjects;
	sf::RectangleShape* paddle;
	std::unique_ptr<Ball> ball;

	std::unique_ptr<HeadsUpDisplay> headsUpDisplay;

	int _score{ 0 };
	int _life{ 3 };
	bool game_start{ false };
};

