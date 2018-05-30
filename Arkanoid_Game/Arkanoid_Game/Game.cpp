#include "Game.h"
#include "MenuState.h"


Game::Game(int width, int height, std::string title)
{
	_data->window.create(sf::VideoMode (width, height), title); //, sf::Style::Fullscreen

	//Adding the initial game state
	_data->machine.AddState(StateRef(new MenuState(this->_data)));

	this->Run();
}

void Game::Run()
{
	float newTime, frameTime, interpolation;
	float currentTime = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while ( this->_data->window.isOpen() )
	{
		this->_data->machine.ProcessStateChanges();

		newTime = this->_clock.getElapsedTime().asSeconds();

		frameTime = newTime - currentTime;
		if ( frameTime > 0.25f )
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while ( accumulator >= dt)
		{
			this->_data->machine.GetActiveState()->HandleInput();
			this->_data->machine.GetActiveState()->Update(dt);

			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState()->Draw(interpolation);
		}

	}

}

