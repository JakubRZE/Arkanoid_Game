//#pragma once
//
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//
////#include "State.h"
////#include "Game.h" 
////#include "Ball.h"
//#include "GameState.h"
////#include "HeadsUpDisplay.h"
////#include "GameOverState.h"
////#include "PauseState.h"
//
//
//
//class Level_1 : public GameState
//{
//public:
//	Level_1(GameDataRef data, int _score, int _lifes);
//
//	void Init();
//	//void HandleInput();
//	//void Update(float dt);
//	//void Draw(float dt);
//
//private:
//	sf::Clock GameStateframeClock;
//	GameDataRef _data;
//
//	sf::Sprite background;
//	sf::RectangleShape winScreen;
//
//	std::vector<sf::RectangleShape> solidObjects;
//	std::vector<sf::CircleShape> circleObjects;
//	sf::RectangleShape* paddle;
//	std::unique_ptr<Ball> ball;
//
//	std::unique_ptr<HeadsUpDisplay> headsUpDisplay;
//
//	int score;
//	int lifes;
//	bool game_start{ false };
//};
//
