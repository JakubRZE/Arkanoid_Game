#include "MenuState.h"
#include "GameState.h"
#include <sstream>
#include <iostream>



MenuState::MenuState(GameDataRef data): _data(data)
{

}

void MenuState::Init()
{
	//_data->resource.LoadTexture("Menu Background", ...);
	//_background.setTexture(this->_data->resource.GetTexture("Menu Background"));

	// tittle 

	_data->resource.LoadFont("Intro", "Recources/fonts/FFF_Tusj.ttf");
	tittle.setFont(this->_data->resource.GetFont("Intro"));
	tittle.setString("Arkanoid");
	tittle.setCharacterSize(160);
	tittle.setOrigin(tittle.getGlobalBounds().width / 2.f, tittle.getGlobalBounds().height / 2.f);
	tittle.setPosition(_data->window.getSize().x / 2.f, _data->window.getSize().y / 2.f - 240.f);

	//playButton atributes

	playButton.setSize({190, 60}); 
	playButton.setFillColor(sf::Color::Transparent);
	playButton.setOrigin(playButton.getSize().x / 2.f, playButton.getSize().y / 2.f);
	playButton.setPosition(_data->window.getSize().x /2.f, _data->window.getSize().y / 2.f + 70.f );
	playButton.setOutlineThickness(4);
	playButton.setOutlineColor(sf::Color::Red);


	//exitButton atributes

	exitButton.setSize({ 190, 60 });
	exitButton.setFillColor(sf::Color::Transparent);
	exitButton.setOrigin(exitButton.getSize().x / 2.f, exitButton.getSize().y / 2.f);
	exitButton.setPosition(_data->window.getSize().x / 2.f, playButton.getPosition().y + 80.f);
	exitButton.setOutlineThickness(4);
	exitButton.setOutlineColor(sf::Color::White);

	// !!!!!!!!! zamienic buttony z rectangle shapów na sprity. W photoshop dorobic buttony za transparentym t³em !!!!!!!!

}

void MenuState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event)) {
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}
	} 
		
		if (_data->input.IsSpriteClicked( playButton , sf::Mouse::Left, _data->window))
		{
			_data->machine.AddState(StateRef(new GameState(_data)), false);
			std::cout << "Go to game!";
			
		}

		if (_data->input.IsSpriteClicked( exitButton, sf::Mouse::Left, _data->window))
		{
			_data->window.close();
		}
}

void MenuState::Update(float dt)
{

}

void MenuState::Draw(float dt)
{
	_data->window.clear();

	// we have to draw all our items
	_data->window.draw(playButton);
	_data->window.draw(exitButton);
	_data->window.draw(tittle);
	
	_data->window.display();

}