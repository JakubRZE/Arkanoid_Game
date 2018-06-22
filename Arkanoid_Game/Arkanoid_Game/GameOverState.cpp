#include "GameOverState.h"
#include "Definitions.h"

#include <iostream>
#include <stdlib.h>
#include <fstream> 


GameOverState::GameOverState(GameDataRef data, int &_score, std::vector<sf::CircleShape> &circle, std::vector<sf::RectangleShape> &rectangle, sf::Sprite _background) 
	: _data(data),
	background(_background),
	solidObjects(rectangle),
	circleObjects(circle)
{
	score = std::unique_ptr<int>(new int(_score));
}

GameOverState::~GameOverState()
{

}

void GameOverState::Init()
{

	std::cout << "GAME OVER!";
 
	std::ifstream readFile;
	readFile.open("Recources/Score.txt");

	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			std::string line;
			readFile >> line;
			if (line != "")
			{
				std::size_t found = line.find_first_of("*");

				std::string f_score = line.substr(0, found);
				line.erase(0, found + 1);

				// string -> integer
				int file_score = std::stoi(f_score);

				score_map.insert(std::make_pair(file_score, line));
			}
		}
	}

	readFile.close();

	
	// is eligable to scoretable
	if (score_map.empty())
	{
		isEnough = true;
	}
	else
	{
		for (const auto it : score_map)
		{
			if (*score > it.first || score_map.size() < 5)
			{
				isEnough = true;
			}
			break;
		}
	}
	


	std::string score_B;
	int i = 1;
	for (auto it = score_map.rbegin(); it != score_map.rend(); ++it)
	{
		score_B += std::to_string(it->first)  + '\n';
	}
	
	std::string name_B;
	for (auto it = score_map.rbegin(); it != score_map.rend(); ++it)
	{
		name_B += std::to_string(i) + "." + "  " + it->second + '\n';
		i++;
	}
	

	top_scores.setString(score_B);
	top_names.setString(name_B);

	top_scores.setFont(this->_data->resource.GetFont("Intro"));
	top_scores.setCharacterSize(30);
	top_scores.setOrigin(top_scores.getGlobalBounds().width / 2.f, top_scores.getGlobalBounds().height / 2.f);
	top_scores.setPosition(835, 475 );

	top_names.setFont(this->_data->resource.GetFont("Intro"));
	top_names.setCharacterSize(30);
	top_names.setOrigin(top_names.getGlobalBounds().width / 2.f, top_names.getGlobalBounds().height / 2.f);
	top_names.setPosition(520 , 475);



	//std::unique_ptr<sf::String> name_str (new sf::String);
	name_str = std::unique_ptr<sf::String>(new sf::String(""));


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
	points.setString("Your score : " + std::to_string(*score));
	points.setCharacterSize(40);
	points.setOrigin(points.getGlobalBounds().width / 2.f, points.getGlobalBounds().height / 2.f);
	points.setPosition(_data->window.getSize().x / 2.f, tittle.getPosition().y + 115 );

	
	if (isEnough)
	{
		name.setFont(this->_data->resource.GetFont("Intro"));
		name.setString("Enter your name:");
		name.setCharacterSize(30);
		name.setOrigin(name.getGlobalBounds().width / 2.f, name.getGlobalBounds().height / 2.f);
		name.setPosition(_data->window.getSize().x / 2.f - name.getGlobalBounds().width / 2.f, points.getPosition().y + 70);

		nameText.setFont(this->_data->resource.GetFont("Intro"));
		nameText.setFillColor(sf::Color::Red);
		nameText.setString("Player");
		nameText.setCharacterSize(30);
		nameText.setOrigin(nameText.getGlobalBounds().width / 2.f, nameText.getGlobalBounds().height / 2.f);
		nameText.setPosition(name.getPosition().x + name.getGlobalBounds().width / 2.f + 60, points.getPosition().y + 75);

		//buttons 

		//SubmitButton atributes
		SubmitButton.setSize({ 140, 35 });
		SubmitButton.setFillColor(sf::Color::Transparent);
		SubmitButton.setOrigin(SubmitButton.getSize().x / 2.f, SubmitButton.getSize().y / 2.f);
		SubmitButton.setPosition(_data->window.getSize().x / 2.f, _data->window.getSize().y / 2.f - 70);
		SubmitButton.setOutlineThickness(2);
		SubmitButton.setOutlineColor(sf::Color::White);
		//submitText
		SubmitText.setFont(this->_data->resource.GetFont("Intro"));
		SubmitText.setString("Submit");
		SubmitText.setCharacterSize(30);
		SubmitText.setOrigin(SubmitButton.getGlobalBounds().width / 2.f, SubmitButton.getGlobalBounds().height / 2.f);
		SubmitText.setPosition(SubmitButton.getPosition().x + 20, SubmitButton.getPosition().y);
	}
	else
	{
		name.setFont(this->_data->resource.GetFont("Intro"));
		name.setString("Not enoguh points to be in TOP 5 :(");
		name.setCharacterSize(30);
		name.setOrigin(name.getGlobalBounds().width / 2.f, name.getGlobalBounds().height / 2.f);
		name.setPosition(_data->window.getSize().x / 2.f , points.getPosition().y + 70);
	}


	//MenuButton atributes
	MenuButton.setSize({ 285, 40 });
	MenuButton.setFillColor(sf::Color::Transparent);
	MenuButton.setOrigin(MenuButton.getSize().x / 2.f, MenuButton.getSize().y / 2.f);
	MenuButton.setPosition(_data->window.getSize().x / 2.f, _data->window.getSize().y - 80.f);
	MenuButton.setOutlineThickness(3);
	MenuButton.setOutlineColor(sf::Color::White);
	//menuText
	MenuText.setFont(this->_data->resource.GetFont("Intro"));
	MenuText.setString("Return to Menu");
	MenuText.setFillColor(sf::Color::Red);
	MenuText.setCharacterSize(35);
	MenuText.setOrigin(MenuButton.getGlobalBounds().width / 2.f, MenuButton.getGlobalBounds().height / 2.f);
	MenuText.setPosition(MenuButton.getPosition().x + 8 , MenuButton.getPosition().y);

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
		if (event.type == sf::Event::TextEntered && !isSubmited && isEnough)
		{
			if (event.text.unicode >= 33 && event.text.unicode <= 128) {
				std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
				if (name_str->getSize() <= 15)
					*name_str += static_cast<char>(event.text.unicode);
			}
			else if (event.text.unicode == 8)
			{
				*name_str = name_str->substring(0, name_str->getSize() - 1);
			}

		}

		if (_data->input.IsSpriteClicked(SubmitButton, sf::Mouse::Left, _data->window) && !isSubmited && isEnough)
		{
			_data->resource.Play("Click");
			SubmitText.setString("Done!");

			//---------------- do after submite
			score_map.insert(std::make_pair(*score, *name_str));

			//// na probe!!!!!!!
			std::string score_B;
			int i = 1;
			for (auto it = score_map.rbegin(); it != score_map.rend() ; ++it)
			{
				score_B += std::to_string(it->first) + '\n';
				i++;
				if (i > 5) break;
			}

			i = 1;
			std::string name_B;
			for (auto it = score_map.rbegin(); it != score_map.rend(); ++it)
			{
				name_B += std::to_string(i) + "." + "  " + it->second + '\n';
				i++;
				if (i > 5) break;
			}
			top_scores.setString(score_B);
			top_names.setString(name_B);

			//praca na pliku

			std::ofstream writeFile;
			writeFile.open("Recources/Score.txt", std::ios::trunc);

			if (writeFile.is_open())
			{
				auto it = score_map.rbegin();

				for (int j = 0 ; it != score_map.rend(); j++)
				{
					if (j >= 5) break;
					std::string zapis = std::to_string(it->first) + "*" + it->second + '\n';
					writeFile << zapis;
					++it;
				}
			}
			writeFile.close();

			isSubmited = true;
			
		}

		if (_data->input.IsSpriteClicked(MenuButton, sf::Mouse::Left, _data->window))
		{
			_data->resource.Play("Click");
			*score = 0;
			_data->machine.AddState(StateRef(new MenuState(this->_data)), true);
		}
	}
}

void GameOverState::Update(float dt)
{
	if(!(*name_str == ""))
	nameText.setString(*name_str);

	if (_data->input.IsSpriteHovered(SubmitButton, _data->window))
	{
		SubmitButton.setFillColor(sf::Color(237, 14, 29, 90));
	}
	else
	{
		SubmitButton.setFillColor(sf::Color::Transparent);
	}

	if (_data->input.IsSpriteHovered(MenuButton, _data->window))
	{
		MenuButton.setFillColor(sf::Color(237, 14, 29, 90));
	}
	else
	{
		MenuButton.setFillColor(sf::Color::Transparent);
	}
}

void GameOverState::Draw(float dt)
{
	_data->window.clear();

	_data->window.draw(background);

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
	_data->window.draw(MenuButton);
	_data->window.draw(MenuText);
	if (!isSubmited) {
		_data->window.draw(SubmitButton);
	}
	_data->window.draw(SubmitText);

	_data->window.draw(top_scores);
	_data->window.draw(top_names);

	_data->window.display();

}

//bool GameOverState::isEnoughPoints(std::multimap<int, std::string> map)
//{
//	
//
//}
