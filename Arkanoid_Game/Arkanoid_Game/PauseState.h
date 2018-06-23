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
	sf::Sprite _background;

	sf::RectangleShape MenuButton;
	sf::Text MenuText;
	sf::Text tittle1;
	sf::Text tittle2;

	std::vector<sf::CircleShape> circleObjects;

	std::unique_ptr<int> score;
};

