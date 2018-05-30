#include "GameState.h"

#include <iostream>


GameState::GameState(GameDataRef data) : _data(data)
{

}

void GameState::Init()
{
	//_data->resource.LoadTexture("Menu Background", ...);
	//_background.setTexture(this->_data->resource.GetTexture("Menu Background"));

	std::cout << "We are in the game!";

}

void GameState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}


	/*if (_data->input.IsSpriteClicked(playButton, sf::Mouse::Left, _data->window))
	{
		std::cout << "Go to game!";
	}*/

}

void GameState::Update(float dt)
{

}

void GameState::Draw(float dt)
{
	_data->window.clear();

	// we have to draw all our items
	//_data->window.draw(playButton);


	_data->window.display();

}