#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <set>

#include "Definitions.h"
#include "State.h"
#include "Game.h" 
#include "MenuState.h"
#include "Ball.h"


class GameOverState : public State
{
public:
	GameOverState(GameDataRef data, int &_score, std::vector<sf::CircleShape> &circle, std::vector<sf::RectangleShape> &rectangle, sf::Sprite background);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

	void readScoreFile(std::string path);
	bool compareToScoreMap(std::multimap< int, std::string> _score_map, int _score) const;
	void mapToString(std::multimap< int, std::string> _score_map, std::string &str_score, std::string &str_name);
	void updateHighScore(std::multimap< int, std::string> &_score_map, std::string &str_score, std::string &str_name);
	void saveScoreToFile(std::string path);

private:
	GameDataRef _data;

	sf::RectangleShape SubmitButton;
	sf::RectangleShape MenuButton;
	sf::Text SubmitText;
	sf::Text MenuText;

	sf::Text top_Scores;
	sf::Text top_Names;
	std::string str_Top_score;
	std::string str_Top_name;

	sf::Sprite background;
	sf::RectangleShape _shape;
	sf::Text tittle;
	sf::Text player_scoreText;
	sf::Text enter_nameText;

	sf::Text player_nameText;
	std::unique_ptr<sf::String> player_Name;

	std::unique_ptr<int> player_Score;
	std::string  _highScore;

	std::vector<sf::RectangleShape> solidObjects;
	std::vector<sf::CircleShape> circleObjects;

	std::multimap< int, std::string> score_map;

	bool isSubmited = false;
	bool isEnoughPointsToSave = false;
};
