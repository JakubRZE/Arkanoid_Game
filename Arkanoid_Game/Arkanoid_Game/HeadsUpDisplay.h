#pragma once

#include<SFML/Graphics.hpp>
#include "Definitions.h"
#include"Game.h"


class HeadsUpDisplay
{
public:

	HeadsUpDisplay(GameDataRef _data);

	void Draw();
	void UpdateScore(int score);
	void UpdateLife(int score);

private:

	GameDataRef _data;
	sf::Text _scoreText;
	sf::Text _lifeText;

};

