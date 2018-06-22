#include "MenuState.h"
#include "GameState.h"
#include <sstream>
#include <iostream>



MenuState::MenuState(GameDataRef data): _data(data)
{

}

void MenuState::Init()
{
	_data->resource.LoadAudio("Click", "Recources/audio/click.wav");
	_data->resource.Play("Click");

	_data->resource.LoadTexture("Menu Background","Recources/img/stars.jpg");
	_background.setTexture(this->_data->resource.GetTexture("Menu Background"));
	
	//mute button
	_data->resource.LoadTexture("mute", "Recources/img/mute.png");
	muteButton.setTexture(this->_data->resource.GetTexture("mute"));
	muteButton.setTextureRect(sf::IntRect(0, 0, 37, 32));
	muteButton.setOrigin(37/2, 32/2);
	muteButton.setPosition( 30.f ,_data->window.getSize().y - 30.f);


	// music here
	_data->resource.LoadMusic("Recources/audio/intro_music.wav");
	_data->resource.PlayMusic();
	

	// tittle 
	_data->resource.LoadFont("Intro", "Recources/fonts/FFF_Tusj.ttf");
	tittle.setFont(this->_data->resource.GetFont("Intro"));
	tittle.setString("Arkanoid");
	tittle.setCharacterSize(160);
	tittle.setOrigin(tittle.getGlobalBounds().width / 2.f, tittle.getGlobalBounds().height / 2.f);
	tittle.setPosition(_data->window.getSize().x / 2.f, _data->window.getSize().y / 2.f - 240.f);

	//author
	_data->resource.LoadFont("Intro", "Recources/fonts/FFF_Tusj.ttf");
	author.setFont(this->_data->resource.GetFont("Intro"));
	author.setString("Made by J. Rzepka");
	author.setCharacterSize(20);
	author.setOrigin(author.getGlobalBounds().width / 2.f, author.getGlobalBounds().height / 2.f);
	author.setPosition(_data->window.getSize().x - 100.f, _data->window.getSize().y -20.f);

	//playButton atributes
	playButton.setSize({190, 60}); 
	playButton.setFillColor(sf::Color::Transparent);
	playButton.setOrigin(playButton.getSize().x / 2.f, playButton.getSize().y / 2.f);
	playButton.setPosition(_data->window.getSize().x /2.f, _data->window.getSize().y / 2.f + 30.f );
	playButton.setOutlineThickness(4);
	playButton.setOutlineColor(sf::Color::Red);


	//exitButton atributes

	exitButton.setSize({ 190, 60 });
	exitButton.setFillColor(sf::Color::Transparent);
	exitButton.setOrigin(exitButton.getSize().x / 2.f, exitButton.getSize().y / 2.f);
	exitButton.setPosition(_data->window.getSize().x / 2.f, playButton.getPosition().y + 80.f);
	exitButton.setOutlineThickness(4);
	exitButton.setOutlineColor(sf::Color::White);


	//playText
	playText.setFont(this->_data->resource.GetFont("Intro"));
	playText.setString("Play");
	playText.setCharacterSize(50);
	playText.setOrigin(playText.getGlobalBounds().width / 2.f, playText.getGlobalBounds().height / 2.f);
	playText.setPosition( playButton.getPosition().x , playButton.getPosition().y - 7);

	//exitText
	exitText.setFont(this->_data->resource.GetFont("Intro"));
	exitText.setString("Exit");
	exitText.setFillColor(sf::Color::Red);
	exitText.setCharacterSize(50);
	exitText.setOrigin(exitText.getGlobalBounds().width / 2.f, exitText.getGlobalBounds().height / 2.f);
	exitText.setPosition(exitButton.getPosition().x, exitButton.getPosition().y - 7);

}

void MenuState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}


		if (_data->input.IsSpriteClicked(playButton, sf::Mouse::Left, _data->window))
		{
			_data->resource.Play("Click");
			_data->machine.AddState(StateRef(new GameState(_data)), false);
			std::cout << "Go to game!";

		}

		if (_data->input.IsSpriteClicked(exitButton, sf::Mouse::Left, _data->window))
		{
			_data->resource.Play("Click");
			_data->window.close();
		}

		if (_data->input.IsSpriteClicked(muteButton, sf::Mouse::Left, _data->window) && !_data->resource.mute)
		{
			_data->resource.PauseMusic();
			muteButton.setTextureRect(sf::IntRect(37, 0, 37, 32));
			_data->resource.mute = true;
		}
		else if (_data->input.IsSpriteClicked(muteButton, sf::Mouse::Left, _data->window))
		{
			_data->resource.mute = false;
			_data->resource.PlayMusic();
			muteButton.setTextureRect(sf::IntRect(0, 0, 37, 32));
		}
	}
		
}

void MenuState::Update(float dt)
{
	if (_data->input.IsSpriteHovered(exitButton, _data->window))
	{
		exitButton.setFillColor(sf::Color(237, 14, 29, 90));
	}
	else 
	{
		exitButton.setFillColor(sf::Color::Transparent);
	}

	if (_data->input.IsSpriteHovered(playButton, _data->window))
	{
		playButton.setFillColor(sf::Color(237, 14, 29, 90));
	}
	else
	{
		playButton.setFillColor(sf::Color::Transparent);
	}
}

void MenuState::Draw(float dt)
{
	_data->window.clear();

	// we have to draw all our items
	_data->window.draw(_background);
	_data->window.draw(playButton);
	_data->window.draw(exitButton);
	_data->window.draw(tittle);
	_data->window.draw(playText);
	_data->window.draw(exitText);
	_data->window.draw(muteButton);
	_data->window.draw(author);
	
	_data->window.display();

}