#include "GameOverState.h"
#include "Definitions.h"

#include <iostream>
#include <stdlib.h>
#include <fstream> 


GameOverState::GameOverState(GameDataRef data, int &_score, std::vector<sf::CircleShape> &circle, std::vector<sf::RectangleShape> &rectangle, sf::Sprite background) 
	: _data(data),
	_background(background),
	solidObjects(rectangle),
	circleObjects(circle),
	score(_score)
{

}

void GameOverState::Init()
{

	std::cout << "GAME OVER!";

	std::ifstream readFile;
	readFile.open("Recources/Score.txt");

	if (readFile.is_open())
	{
		while (!readFile.eof() )
		{
			readFile >> _highScore;
		}
	}
	
	readFile.close();

	//-----------------------------

	_data->window.setMouseCursorVisible(true);

	_shape.setSize(sf::Vector2f(_data->window.getSize()));
	_shape.setFillColor(sf::Color(0, 0, 0, 230));

	tittle.setFont(this->_data->resource.GetFont("Intro"));
	tittle.setString("Game Over");
	tittle.setCharacterSize(120);
	tittle.setOrigin(tittle.getGlobalBounds().width / 2.f, tittle.getGlobalBounds().height / 2.f);
	tittle.setPosition(_data->window.getSize().x / 2.f, 50);

	points.setFont(this->_data->resource.GetFont("Intro"));
	points.setFillColor(sf::Color::Red);
	points.setString("Your score : " + std::to_string(score));
	points.setCharacterSize(40);
	points.setOrigin(points.getGlobalBounds().width / 2.f, points.getGlobalBounds().height / 2.f);
	points.setPosition(_data->window.getSize().x / 2.f, tittle.getPosition().y + 115 );

	name.setFont(this->_data->resource.GetFont("Intro"));
	name.setString("Enter your name:");
	name.setCharacterSize(30);
	name.setOrigin(name.getGlobalBounds().width / 2.f, name.getGlobalBounds().height / 2.f);
	name.setPosition(_data->window.getSize().x / 2.f - name.getGlobalBounds().width / 2.f , points.getPosition().y + 65);

	nameText.setFont(this->_data->resource.GetFont("Intro"));
	nameText.setFillColor(sf::Color::Red);
	nameText.setString("0");
	nameText.setCharacterSize(30);
	nameText.setOrigin(nameText.getGlobalBounds().width / 2.f, nameText.getGlobalBounds().height / 2.f);
	nameText.setPosition(name.getPosition().x + name.getGlobalBounds().width / 2.f + 35 , points.getPosition().y + 65);

}

void GameOverState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event)) {
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}
		////////////////////////////////////////////////////
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode >= 33 && event.text.unicode <= 128) {
				std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
				if (name_str.getSize() <= 15)
					name_str += static_cast<char>(event.text.unicode);
			}
			else if (event.text.unicode == 8)
			{
				name_str = name_str.substring(0, name_str.getSize() - 1);
			}

		}
	}
}

void GameOverState::Update(float dt)
{
	nameText.setString(name_str);
}

void GameOverState::Draw(float dt)
{
	_data->window.clear();

	_data->window.draw(_background);

	for (const auto& o : solidObjects)
	{
		_data->window.draw(o);
	}
	for (const auto& o : circleObjects)
	{
		_data->window.draw(o);
	}

	_data->window.draw(_shape);

	_data->window.draw(tittle);
	_data->window.draw(points); 
	_data->window.draw(name);
	_data->window.draw(nameText);

	_data->window.display();

}
