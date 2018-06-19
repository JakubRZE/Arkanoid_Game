#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <set>

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

	//bool isEnoughPoints(std::multimap< int, std::string> map);



private:
	GameDataRef _data;

	sf::RectangleShape SubmitButton;
	sf::RectangleShape MenuButton;
	sf::Text SubmitText;
	sf::Text MenuText;

	sf::Text top_scores;
	sf::Text top_names;

	sf::Sprite _background;
	sf::RectangleShape _shape;
	sf::Text tittle;
	sf::Text points;
	sf::Text name;

	sf::Text nameText;
	std::unique_ptr<sf::String> name_str;

	std::unique_ptr<int> score;
	std::string  _highScore;

	//delta time clock
	//sf::Clock GameStateframeClock;

	//vector of static objects
	std::vector<sf::RectangleShape> solidObjects;
	//vector of static circular objects
	std::vector<sf::CircleShape> circleObjects;

	std::multimap< int, std::string> score_map;

	bool isSubmited = false;
	bool isEnough = false;
};
