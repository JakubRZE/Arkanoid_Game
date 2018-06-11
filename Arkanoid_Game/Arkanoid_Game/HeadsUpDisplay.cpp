#include "HeadsUpDisplay.h"
#include <string>


HeadsUpDisplay::HeadsUpDisplay(GameDataRef data) 
	: _data(data)
{
	_scoreText.setFont(_data->resource.GetFont("Intro"));
	_scoreText.setString("0");
	_scoreText.setCharacterSize(30);
	_scoreText.setFillColor(sf::Color::White);
	_scoreText.setPosition(SCREEN_WIDTH - 170 , 5);
	 
	_lifeText.setFont(_data->resource.GetFont("Intro"));
	_lifeText.setString("3");
	_lifeText.setCharacterSize(30);
	_lifeText.setFillColor(sf::Color::Red);
	_lifeText.setPosition(10, 5);
}


void HeadsUpDisplay::Draw()
{
	_data->window.draw(_scoreText);
	_data->window.draw(_lifeText);
}
void HeadsUpDisplay::UpdateScore(int score)
{
	std::string str_score = "Score: " + std::to_string(score);
	_scoreText.setString(str_score);
	str_score = "Score: ";
}

void HeadsUpDisplay::UpdateLife(int life)
{
	std::string str_life = "Life: " + std::to_string(life);
	_lifeText.setString(str_life);
	str_life = "Life: ";
}