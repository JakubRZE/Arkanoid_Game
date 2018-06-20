#include "GameState.h"
#include "Definitions.h"

#include <iostream>
#include <stdlib.h>
#include <time.h> 


GameState::GameState(GameDataRef data) : _data(data)
{

}

void GameState::Init()
{
	_data->resource.LoadTexture("MenuBg", "Recources/img/game_bg.jpg");
	_background.setTexture(this->_data->resource.GetTexture("MenuBg"));



	// audio loading

	_data->resource.LoadMusic("Recources/audio/game_music.wav");
	_data->resource.PlayMusic();

	_data->resource.LoadAudio("HitPaddle", "Recources/audio/Ping.wav");
	_data->resource.LoadAudio("HitCircle", "Recources/audio/Pong.wav");
	_data->resource.LoadAudio("LosingSound", "Recources/audio/LosingSound.wav");
	_data->resource.LoadAudio("GameOver", "Recources/audio/gameover.wav");



	std::cout << "We are in the game!";

	_data->window.setMouseCursorVisible(false);

	headsUpDisplay = std::unique_ptr<HeadsUpDisplay>(new HeadsUpDisplay(_data));
	_score = 0;
	_life = 1;
	headsUpDisplay->UpdateScore(_score);
	headsUpDisplay->UpdateLife(_life);

	createSolidObjects(solidObjects);
	createCircleObjects(circleObjects);

	paddle = &solidObjects.back();

	ball = std::unique_ptr<Ball>(new Ball(solidObjects, circleObjects, _data));
	
	ball->setPosition((float)SCREEN_WIDTH/2.f, 715.f);
}

void GameState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}
		//update the paddle position
		else if (event.type == sf::Event::MouseMoved && game_start)
		{

			auto x = std::max(0 + (int)paddle->getSize().x / 2, std::min(SCREEN_WIDTH - (int)paddle->getSize().x / 2, event.mouseMove.x));
			auto position = paddle->getPosition();
			position.x = static_cast<float>(x);
			paddle->setPosition(position);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// left key is pressed: move our character
			game_start = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			game_start = false;
			_data->machine.AddState(StateRef(new PauseState(_data, circleObjects , _background, _score)), false);
			std::cout << "Escape!";
		}

	}

		
}

void GameState::Update(float dt)
{
	//update the dynamic object
	ball->update(GameStateframeClock.restart().asSeconds(), game_start, _score);

	if (ball->getPosition_Y() >= SCREEN_HEIGHT)
	{
		game_start = false;
		_data->resource.Play("LosingSound");
		paddle->setPosition(SCREEN_WIDTH / 2.f, 735.f);
		ball->setPosition((float)SCREEN_WIDTH / 2.f, 715.f);

		_life--;
	}

	headsUpDisplay->UpdateScore(_score);
	headsUpDisplay->UpdateLife(_life);


	if (_life == 0)
	{
		sf::Clock clock;
		_data->resource.PauseMusic();
		_data->resource.Play("GameOver");

		sf::Time elapsed1 = clock.getElapsedTime();

		while (elapsed1.asSeconds() < 1.5f) {
			elapsed1 = clock.getElapsedTime();
		};

		_data->machine.AddState(StateRef(new GameOverState(_data, _score,circleObjects ,solidObjects , _background)), true);
	}

	nextLevel();
}

void GameState::Draw(float dt)
{
	_data->window.clear();

	_data->window.draw(_background);

	headsUpDisplay->Draw();

	_data->window.draw(*ball);
	for (const auto& o : solidObjects)
	{
		_data->window.draw(o);
	}

	for (const auto& o : circleObjects)
	{
		_data->window.draw(o);
	}

	if(nextLevel()) _data->window.draw(win_scr);

	_data->window.display();

}

//-------builds scene-----//

void  GameState::createSolidObjects(std::vector<sf::RectangleShape>& shapes)
{
	// window bounds
	shapes.emplace_back(sf::Vector2f(SCREEN_WIDTH, 6.f)); //top
	shapes.back().setOrigin(shapes.back().getSize() / 2.f);
	shapes.back().setPosition(SCREEN_WIDTH / 2.f, 0.f);

	shapes.emplace_back(sf::Vector2f(6.f , SCREEN_HEIGHT)); //left
	shapes.back().setOrigin(shapes.back().getSize() / 2.f);
	shapes.back().setPosition(0.f, SCREEN_HEIGHT / 2.f);

	shapes.emplace_back(sf::Vector2f(6.f, SCREEN_HEIGHT)); //right
	shapes.back().setOrigin(shapes.back().getSize() / 2.f);
	shapes.back().setPosition(SCREEN_WIDTH, SCREEN_HEIGHT / 2.f);

	//make the paddle last so we can easily grab a reference to it
	shapes.emplace_back(sf::Vector2f(150.f, 20.f));
	shapes.back().setOrigin(shapes.back().getSize() / 2.f);
	shapes.back().setPosition(SCREEN_WIDTH/2.f, 735.f);
}

void  GameState::createCircleObjects(std::vector<sf::CircleShape>& shapes)
{
	//seed for random time
	srand(time(NULL));

	//-------builds block for destroying-----//
	for (unsigned i = 0; i < 3; i++)
	{
		for (unsigned j = 0; j < 8; j++)
		{
			shapes.emplace_back(rand() % 22 + 32);
			shapes.back().setPosition(135 + (float)(rand() % 15) + (j * 150) , 100 + (float)(rand() % 15) + (i * 110));
			shapes.back().setOrigin(shapes.back().getRadius(), shapes.back().getRadius());
			shapes.back().setFillColor( sf::Color::White); // rand() % 255 + 220 , rand() % 17 , rand() % 17
		}
	}
}

bool GameState::nextLevel()
{
	if (circleObjects.empty())
	{
		game_start = false;

		_data->resource.PauseMusic();
		_data->resource.Play("GameOver");

		win_scr.setSize(sf::Vector2f(_data->window.getSize()));
		win_scr.setFillColor(sf::Color(0, 0, 0, 190));

		//_data->machine.AddState(StateRef(new GameOverState(_data, _score, circleObjects, solidObjects, _background)), true);
		return true;
	}
	return false;
}