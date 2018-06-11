#include "GameOverState.h"
#include "Definitions.h"

#include <iostream>
#include <stdlib.h>
#include <time.h> 


GameOverState::GameOverState(GameDataRef data, int _score) : _data(data)
{

}

void GameOverState::Init()
{
	//_data->resource.LoadTexture("Menu Background", ...);
	//_background.setTexture(this->_data->resource.GetTexture("Menu Background"));

	std::cout << "GAME OVER!";

	_data->window.setMouseCursorVisible(true);

}

void GameOverState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		// left key is pressed: move our character
		
	}
}

void GameOverState::Update(float dt)
{
	
}

void GameOverState::Draw(float dt)
{
	_data->window.clear();

	//_data->window.draw(*ball);
	//for (const auto& o : solidObjects)
	//{
	//	_data->window.draw(o);
	//}
	//for (const auto& o : circleObjects)
	//{
	//	_data->window.draw(o);
	//}

	_data->window.display();

}
