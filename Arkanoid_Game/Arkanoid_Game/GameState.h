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

private:
	GameDataRef _data;

	sf::Sprite _background;

	//delta time clock
	sf::Clock GameStateframeClock;

	//vector of static objects
	std::vector<sf::RectangleShape> solidObjects;
	//vector of static circular objects
	std::vector<sf::CircleShape> circleObjects;

	//get a ref to the paddle shape
	sf::RectangleShape* paddle;

	std::unique_ptr<Ball> ball;

	std::unique_ptr<HeadsUpDisplay> headsUpDisplay;

	int _score;
	int _life;

	bool game_start = false;

};

