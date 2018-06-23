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
	player_Score = std::unique_ptr<int>(new int(_score));
}

void GameOverState::Init()
{
	_data->window.setMouseCursorVisible(true);

	readScoreFile(SCORE_FILEPATH);
	
	isEnoughPointsToSave = compareToScoreMap(score_map, *player_Score);

	mapToString(score_map, str_Top_score, str_Top_name);

	player_Name = std::unique_ptr<sf::String>(new sf::String(""));


	//---------------------------shapes and texts atributes---------------------------------------------
	// ranking
	top_Scores.setFont(this->_data->resource.GetFont("Intro"));
	top_Scores.setString(str_Top_score);
	top_Scores.setCharacterSize(30);
	top_Scores.setOrigin(top_Scores.getGlobalBounds().width / 2.f, top_Scores.getGlobalBounds().height / 2.f);
	top_Scores.setPosition(835, 475 );

	top_Names.setFont(this->_data->resource.GetFont("Intro"));
	top_Names.setString(str_Top_name);
	top_Names.setCharacterSize(30);
	top_Names.setOrigin(top_Names.getGlobalBounds().width / 2.f, top_Names.getGlobalBounds().height / 2.f);
	top_Names.setPosition(520 , 475);
	// title
	tittle.setFont(this->_data->resource.GetFont("Intro"));
	tittle.setString("Game Over");
	tittle.setCharacterSize(120);
	tittle.setOrigin(tittle.getGlobalBounds().width / 2.f, tittle.getGlobalBounds().height / 2.f);
	tittle.setPosition(_data->window.getSize().x / 2.f, 50);
	// score owned
	player_scoreText.setFont(this->_data->resource.GetFont("Intro"));
	player_scoreText.setFillColor(sf::Color::Red);
	player_scoreText.setString("Your score : " + std::to_string(*player_Score));
	player_scoreText.setCharacterSize(40);
	player_scoreText.setOrigin(player_scoreText.getGlobalBounds().width / 2.f, player_scoreText.getGlobalBounds().height / 2.f);
	player_scoreText.setPosition(_data->window.getSize().x / 2.f, tittle.getPosition().y + 115 );
	
	if (isEnoughPointsToSave)
	{   // chosen name
		enter_nameText.setFont(this->_data->resource.GetFont("Intro"));
		enter_nameText.setString("Enter your name:");
		enter_nameText.setCharacterSize(30);
		enter_nameText.setOrigin(enter_nameText.getGlobalBounds().width / 2.f, enter_nameText.getGlobalBounds().height / 2.f);
		enter_nameText.setPosition(_data->window.getSize().x / 2.f - enter_nameText.getGlobalBounds().width / 2.f, player_scoreText.getPosition().y + 70);

		player_nameText.setFont(this->_data->resource.GetFont("Intro"));
		player_nameText.setFillColor(sf::Color::Red);
		player_nameText.setString("Player");
		player_nameText.setCharacterSize(30);
		player_nameText.setOrigin(player_nameText.getGlobalBounds().width / 2.f, player_nameText.getGlobalBounds().height / 2.f);
		player_nameText.setPosition(enter_nameText.getPosition().x + enter_nameText.getGlobalBounds().width / 2.f + 60, player_scoreText.getPosition().y + 75);

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
		enter_nameText.setFont(this->_data->resource.GetFont("Intro"));
		enter_nameText.setString("Not enoguh points to be in TOP 5 :(");
		enter_nameText.setCharacterSize(30);
		enter_nameText.setOrigin(enter_nameText.getGlobalBounds().width / 2.f, enter_nameText.getGlobalBounds().height / 2.f);
		enter_nameText.setPosition(_data->window.getSize().x / 2.f , player_scoreText.getPosition().y + 70);
	}
	//MenuButton 
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

	_shape.setSize(sf::Vector2f(_data->window.getSize()));
	_shape.setFillColor(sf::Color(0, 0, 0, 230));
	//-----------------------------------------------------------------------------------------------------
}

void GameOverState::HandleInput() 
{
	sf::Event event;

	while (_data->window.pollEvent(event)) {
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}

		if (event.type == sf::Event::TextEntered && !isSubmited && isEnoughPointsToSave)
		{
			if (event.text.unicode >= 33 && event.text.unicode <= 128) {
				if (player_Name->getSize() <= 15)
					*player_Name += static_cast<char>(event.text.unicode);
			}
			else if (event.text.unicode == 8)
			{
				*player_Name = player_Name->substring(0, player_Name->getSize() - 1);
			}
		}

		if (_data->input.IsSpriteClicked(SubmitButton, sf::Mouse::Left, _data->window) && !isSubmited && isEnoughPointsToSave)
		{
			_data->resource.Play("Click");
			SubmitText.setString("Done!");
			score_map.insert(std::make_pair(*player_Score, *player_Name));
			updateHighScore(score_map, str_Top_score, str_Top_name);
			saveScoreToFile(SCORE_FILEPATH);
			isSubmited = true;
		}

		if (_data->input.IsSpriteClicked(MenuButton, sf::Mouse::Left, _data->window))
		{
			_data->resource.Play("Click");
			*player_Score = 0;
			_data->machine.AddState(StateRef(new MenuState(this->_data)), true);
		}
	}
}

void GameOverState::Update(float dt)
{
	if(!(*player_Name == ""))
	player_nameText.setString(*player_Name);

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
	_data->window.draw(player_scoreText); 
	_data->window.draw(enter_nameText);
	_data->window.draw(player_nameText);
	_data->window.draw(MenuButton);
	_data->window.draw(MenuText);
	if (!isSubmited) {
		_data->window.draw(SubmitButton);
	}
	_data->window.draw(SubmitText);
	_data->window.draw(top_Scores);
	_data->window.draw(top_Names);

	_data->window.display();
}

void GameOverState::readScoreFile(std::string path)
{
	std::ifstream readFile;
	readFile.open(path);

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
}

bool GameOverState::compareToScoreMap(std::multimap< int, std::string> _score_map, int _score) const
{
	if (_score_map.empty())
	{
		 return true;
	}
	else
	{
		for (const auto it : _score_map)
		{
			if (_score > it.first || _score_map.size() < 5)
			{
				return true;
			}
			break;
		}
	}
	return false;
}

void GameOverState::mapToString(std::multimap<int, std::string> _score_map, std::string &str_score, std::string &str_name)
{
	int i = 1;
	for (auto it = _score_map.rbegin(); it != _score_map.rend(); ++it)
	{
		str_name += std::to_string(i) + "." + "  " + it->second + '\n';
		i++;
	}

	for (auto it = _score_map.rbegin(); it != _score_map.rend(); ++it)
	{
		str_score += std::to_string(it->first) + '\n';
	}
}

void GameOverState::updateHighScore(std::multimap< int, std::string> &_score_map , std::string &str_score, std::string &str_name)
{
	str_score = "";
	str_name = "";
	int i = 1;
	for (auto it = _score_map.rbegin(); it != _score_map.rend(); ++it)
	{
		str_score += std::to_string(it->first) + '\n';
		i++;
		if (i > 5) break;
	}

	i = 1;
	for (auto it = _score_map.rbegin(); it != _score_map.rend(); ++it)
	{
		str_name += std::to_string(i) + "." + "  " + it->second + '\n';
		i++;
		if (i > 5) break;
	}
	top_Scores.setString(str_score);
	top_Names.setString(str_name);
}

void GameOverState::saveScoreToFile(std::string path)
{
	std::ofstream writeFile;
	writeFile.open(path, std::ios::trunc);

	if (writeFile.is_open())
	{
		auto it = score_map.rbegin();

		for (int j = 0; it != score_map.rend(); j++)
		{
			if (j >= 5) break;
			std::string saveLine = std::to_string(it->first) + "*" + it->second + '\n';
			writeFile << saveLine;
			++it;
		}
	}
	writeFile.close();
}
