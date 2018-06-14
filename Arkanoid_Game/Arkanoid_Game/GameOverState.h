#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.h"
#include "Game.h" 
#include "Ball.h"


class GameOverState : public State
{
public:
	GameOverState(GameDataRef data, int &_score, std::vector<sf::CircleShape> &circle, std::vector<sf::RectangleShape> &rectangle, sf::Sprite background);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);



private:
	GameDataRef _data;

	sf::Sprite _background;
	sf::RectangleShape _shape;
	sf::Text tittle;
	sf::Text points;
	sf::Text name;

	sf::Text nameText;
	sf::String name_str;

	int score;
	std::string  _highScore;

	//delta time clock
	//sf::Clock GameStateframeClock;

	//vector of static objects
	std::vector<sf::RectangleShape> solidObjects;
	//vector of static circular objects
	std::vector<sf::CircleShape> circleObjects;

};
