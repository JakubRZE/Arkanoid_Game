#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Ball.h"
#include "HeadsUpDisplay.h"
#include "GameOverState.h"
#include "PauseState.h"


class GameState: public State
{
public:
	GameState() = default;
	GameState(GameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

	//-------builds scene-----//
	void oneSoildObject(std::vector<sf::RectangleShape>& shapes, float height, float width, float x, float y);
	void createSolidObjects();
	void createCircleObjects(std::vector<sf::CircleShape>& shapes);
	void oneCircleObject(std::vector<sf::CircleShape>& shapes, float radius, float x, float y);
	void oneCircleObject(std::vector<sf::CircleShape>& shapes, float radius, float x, float y, bool color);
	bool isCircleIntersecting(std::vector<sf::CircleShape>& shapes);

	void setPaddlePosition(sf::Event event);
	void centerPaddle();
	void pointLoss();
	void addMoreCircleObject(std::vector<sf::CircleShape>& shapes);
	void gameOver();

private:
	sf::Clock GameStateframeClock;
	sf::Clock moreBlocks;
	sf::Clock ballSpeed;
	GameDataRef _data;

	sf::Sprite background;
	sf::Text clickToStart;
	
	std::vector<sf::RectangleShape> solidObjects;
	std::vector<sf::CircleShape> circleObjects;
	sf::RectangleShape* paddle;
	std::unique_ptr<Ball> ball;

	std::unique_ptr<HeadsUpDisplay> headsUpDisplay;

	int score{ 0 };
	int lifes{ 3 };
	float circleRespawnSpeed{ 3.f };
	bool game_start{ false };
	bool makeMorePoints{ false };
};

