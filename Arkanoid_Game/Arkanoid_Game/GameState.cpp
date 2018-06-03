#include "GameState.h"
#include "Definitions.h"

#include <iostream>


GameState::GameState(GameDataRef data) : _data(data)
{

}

void GameState::Init()
{
	//_data->resource.LoadTexture("Menu Background", ...);
	//_background.setTexture(this->_data->resource.GetTexture("Menu Background"));

	std::cout << "We are in the game!";

	createSolidObjects(solidObjects);
	createCircleObjects(circleObjects);

	paddle = &solidObjects.back();

	ball = std::unique_ptr<Ball>(new Ball(solidObjects, circleObjects, _data));
	
	ball->setPosition(300.f, 400.f);

}

void GameState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}
		//update the paddle position
		else if (event.type == sf::Event::MouseMoved)
		{
			auto x = std::max( 0 + (int)paddle->getSize().x/2 , std::min(SCREEN_WIDTH - (int)paddle->getSize().x/2 , event.mouseMove.x));
			auto position = paddle->getPosition();
			position.x = static_cast<float>(x);
			paddle->setPosition(position);
		}

	

}

void GameState::Update(float dt)
{
	//update the dynamic object
	ball->update(GameStateframeClock.restart().asSeconds());
}

void GameState::Draw(float dt)
{
	_data->window.clear();

	_data->window.draw(*ball);
	for (const auto& o : solidObjects)
	{
		_data->window.draw(o);
	}
	for (const auto& o : circleObjects)
	{
		_data->window.draw(o);
	}

	_data->window.display();

}

//-------builds scene-----//
void  GameState::createSolidObjects(std::vector<sf::RectangleShape>& shapes)
{
	//we set the shape origins to the centre of the object
	//so that comparing the position with the ball's position
	//gives us a good idea of the direction the ball is moving

	shapes.emplace_back(sf::Vector2f(SCREEN_WIDTH, 1.5f)); //top
	shapes.back().setOrigin(shapes.back().getSize() / 2.f);
	shapes.back().setPosition(SCREEN_WIDTH / 2.f, 0.f);

	shapes.emplace_back(sf::Vector2f(1.5f , SCREEN_HEIGHT)); //left
	shapes.back().setOrigin(shapes.back().getSize() / 2.f);
	shapes.back().setPosition(0.f, SCREEN_HEIGHT / 2.f);

	shapes.emplace_back(sf::Vector2f(1.5f, SCREEN_HEIGHT)); //right
	shapes.back().setOrigin(shapes.back().getSize() / 2.f);
	shapes.back().setPosition(SCREEN_WIDTH, SCREEN_HEIGHT / 2.f);

	shapes.emplace_back(sf::Vector2f(SCREEN_WIDTH, 1.5f)); //bottom
	shapes.back().setOrigin(shapes.back().getSize() / 2.f);
	shapes.back().setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT);

	//make the paddle last so we can easily grab a reference to it
	shapes.emplace_back(sf::Vector2f(100.f, 20.f));
	shapes.back().setOrigin(shapes.back().getSize() / 2.f);
	shapes.back().setPosition(300.f, 700.f);
}

void  GameState::createCircleObjects(std::vector<sf::CircleShape>& shapes)
{
	shapes.emplace_back(30.f);
	shapes.back().setPosition(420.f, 80.f);
	shapes.back().setOrigin(shapes.back().getRadius(), shapes.back().getRadius());

	shapes.emplace_back(60.f);
	shapes.back().setPosition(220.f, 180.f);
	shapes.back().setOrigin(shapes.back().getRadius(), shapes.back().getRadius());

	shapes.emplace_back(20.f);
	shapes.back().setPosition(400.f, 580.f);
	shapes.back().setOrigin(shapes.back().getRadius(), shapes.back().getRadius());

	shapes.emplace_back(45.f);
	shapes.back().setPosition(120.f, 340.f);
	shapes.back().setOrigin(shapes.back().getRadius(), shapes.back().getRadius());

	shapes.emplace_back(50.f);
	shapes.back().setPosition(320.f, 410.f);
	shapes.back().setOrigin(shapes.back().getRadius(), shapes.back().getRadius());
}