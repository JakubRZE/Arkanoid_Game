#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "State.h"
#include "Game.h" 
#include "GameState.h"



class PauseState : public State
{
public:
	PauseState(GameDataRef data, std::vector<sf::CircleShape> &circle, sf::Sprite background, int &_score);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;

	sf::RectangleShape _shape;

	//vector of static objects
	std::vector<sf::CircleShape> circleObjects;

	sf::Sprite _background;
	std::unique_ptr<int> score;

	sf::RectangleShape MenuButton;
	sf::Text MenuText;

	sf::Text tittle1;
	sf::Text tittle2;
	
};

