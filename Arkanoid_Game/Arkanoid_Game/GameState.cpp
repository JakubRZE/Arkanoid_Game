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
	_data->window.setMouseCursorVisible(false);
	//seed for random time
	srand(static_cast<unsigned int>(time(NULL)));

	_data->resource.LoadTexture("MenuBg", "Recources/img/lvl.jpg");
	background.setTexture(this->_data->resource.GetTexture("MenuBg"));

	clickToStart.setFont(this->_data->resource.GetFont("Intro"));
	clickToStart.setString("Click to START the GAME");
	clickToStart.setCharacterSize(60);
	clickToStart.setOrigin(clickToStart.getGlobalBounds().width / 2.f, clickToStart.getGlobalBounds().height / 2.f);
	clickToStart.setPosition(_data->window.getSize().x / 2.f, _data->window.getSize().y - 200.f);

	_data->resource.LoadMusic("Recources/audio/game_music.wav");
	_data->resource.PlayMusic();

	_data->resource.LoadAudio("HitPaddle", "Recources/audio/Ping.wav");
	_data->resource.LoadAudio("HitCircle", "Recources/audio/Pong.wav");
	_data->resource.LoadAudio("LosingSound", "Recources/audio/LosingSound.wav");
	_data->resource.LoadAudio("GameOver", "Recources/audio/gameover.wav");
	_data->resource.LoadAudio("Pop", "Recources/audio/pop.wav");

	headsUpDisplay = std::unique_ptr<HeadsUpDisplay>(new HeadsUpDisplay(_data));
	headsUpDisplay->UpdateScore(score);
	headsUpDisplay->UpdateLife(lifes);

	createSolidObjects();
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			game_start = true;
		}
		if (event.type == sf::Event::MouseMoved && game_start)
		{
			setPaddlePosition(event);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			game_start = false;
			_data->machine.AddState(StateRef(new PauseState(_data, circleObjects , background, score)), false);
		}
	}
}

void GameState::Update(float dt)
{
	ball->update(GameStateframeClock.restart().asSeconds(), game_start, score);

	if (ball->getPosition_Y() >= SCREEN_HEIGHT)
	{
		pointLoss();
	}

	headsUpDisplay->UpdateScore(score);
	headsUpDisplay->UpdateLife(lifes);

	if (lifes == 0)
	{
		gameOver();
	}

	if (circleObjects.size() < 14)
	{
		addMoreCircleObject(circleObjects);
	}
}

void GameState::Draw(float dt)
{
	_data->window.clear();

	_data->window.draw(background);
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
	if(game_start == false) _data->window.draw(clickToStart);

	_data->window.display();
}

void GameState::createSolidObjects()
{
	// window bounds
	oneSoildObject(solidObjects, SCREEN_WIDTH , 6.f , SCREEN_WIDTH / 2.f, 0.f); //top
	oneSoildObject(solidObjects, 6.f, SCREEN_HEIGHT , 0.f, SCREEN_HEIGHT / 2.f); //left
	oneSoildObject(solidObjects, 6.f, SCREEN_HEIGHT , SCREEN_WIDTH, SCREEN_HEIGHT / 2.f); //right

	//the paddle is last so we can easily grab a reference to it
	oneSoildObject(solidObjects, 165.f, 20.f, SCREEN_WIDTH / 2.f, 735.f);
}

void GameState::oneSoildObject(std::vector<sf::RectangleShape>& shapes, float width, float height, float x, float y)
{
	shapes.emplace_back(sf::Vector2f(width, height));
	shapes.back().setOrigin(shapes.back().getSize() / 2.f);
	shapes.back().setPosition(x,y);
}

void GameState::createCircleObjects(std::vector<sf::CircleShape>& shapes)
{
	//-------builds block for destroying-----//
	for (unsigned i = 0; i < 3; i++)
	{
		for (unsigned j = 0; j < 8; j++)
		{
			oneCircleObject(circleObjects, (float)(rand() % 22 + 32.f), 135 + (float)(rand() % 15) + (j * 150), 100 + (float)(rand() % 15) + (i * 110));
		}
	}
}

void GameState::oneCircleObject(std::vector<sf::CircleShape>& shapes, float radius, float x, float y)
{
	shapes.emplace_back(radius);
	shapes.back().setPosition(x, y);
	shapes.back().setOrigin(shapes.back().getRadius(), shapes.back().getRadius());
	shapes.back().setFillColor(sf::Color::White); 
}

void GameState::oneCircleObject(std::vector<sf::CircleShape>& shapes, float radius, float x, float y, bool color)
{
	shapes.emplace_back(radius);
	shapes.back().setPosition(x, y);
	shapes.back().setOrigin(shapes.back().getRadius(), shapes.back().getRadius());
	if (color)shapes.back().setFillColor(sf::Color(rand() % 255 + 238, rand() % 255 + 238, rand() % 255 + 238));
	while (isCircleIntersecting(circleObjects))
	{
		shapes.pop_back();
		oneCircleObject(circleObjects, rand() % 22 + 32, rand() % 1200 + 100, rand() % 470 + 80, true);
	}

}

bool GameState::isCircleIntersecting(std::vector<sf::CircleShape>& shapes)
{
	int size = shapes.size();
	sf::IntRect circleRect_Last{ shapes[size - 1].getGlobalBounds() };

	for (auto it = shapes.begin(); it != shapes.end()-1; ++it)
	{
		sf::IntRect circleRect{ it->getGlobalBounds() };
		if (  circleRect_Last.intersects(circleRect)  )
		return true;
	}
	return false;
}

void GameState::setPaddlePosition(sf::Event event)
{
	auto x = std::max(0 + (int)paddle->getSize().x / 2, std::min(SCREEN_WIDTH - (int)paddle->getSize().x / 2, event.mouseMove.x));
	auto position = paddle->getPosition();
	position.x = static_cast<float>(x);
	paddle->setPosition(position);
}

void GameState::centerPaddle()
{
	paddle->setPosition(SCREEN_WIDTH / 2.f, 735.f);
	ball->setPosition((float)SCREEN_WIDTH / 2.f, 715.f);
}

void GameState::pointLoss()
{
	game_start = false;
	_data->resource.Play("LosingSound");
	centerPaddle();
	lifes--;
}

void GameState::addMoreCircleObject(std::vector<sf::CircleShape>& shapes)
{
		sf::Time elapsed = moreBlocks.getElapsedTime();
		if (elapsed.asSeconds() > circleRespawnSpeed)
		{
			_data->resource.Play("Pop");
			oneCircleObject(circleObjects, rand() % 22 + 32, rand() % 1200 + 100, rand() % 470 + 45, true);
			moreBlocks.restart();
			circleRespawnSpeed -= 0.025f;
			ball->speedUp();
		}
}

void GameState::gameOver()
{
	sf::Clock clock;
	_data->resource.PauseMusic();
	_data->resource.Play("GameOver");

	sf::Time elapsed1 = clock.getElapsedTime();
	while (elapsed1.asSeconds() < 1.5f) {
		elapsed1 = clock.getElapsedTime();
	};

	_data->machine.AddState(StateRef(new GameOverState(_data, score, circleObjects, solidObjects, background)), true);
}
