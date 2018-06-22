//#include "Level_1.h"
//
//
//Level_1::Level_1(GameDataRef data, int _score, int _lifes) 
//	: _data(data),
//	score(_score),
//	lifes(_lifes)
//{
//
//}
//
//void Level_1::Init()
//{
//	_data->window.setMouseCursorVisible(false);
//
//	_data->resource.LoadTexture("Lvl_1_Bg", "Recources/img/lvl1.jpg");
//	background.setTexture(this->_data->resource.GetTexture("Lvl_1_Bg"));
//
//	/*_data->resource.LoadMusic("Recources/audio/game_music.wav");
//	_data->resource.PlayMusic();*/
//
//	/*_data->resource.LoadAudio("HitPaddle", "Recources/audio/Ping.wav");
//	_data->resource.LoadAudio("HitCircle", "Recources/audio/Pong.wav");
//	_data->resource.LoadAudio("LosingSound", "Recources/audio/LosingSound.wav");
//	_data->resource.LoadAudio("GameOver", "Recources/audio/gameover.wav");*/
//
//	headsUpDisplay = std::unique_ptr<HeadsUpDisplay>(new HeadsUpDisplay(_data));
//	headsUpDisplay->UpdateScore(score);
//	headsUpDisplay->UpdateLife(lifes);
//
//	createSolidObjects();
//	createCircleObjects(circleObjects);
//
//	paddle = &solidObjects.back();
//
//	ball = std::unique_ptr<Ball>(new Ball(solidObjects, circleObjects, _data));
//	ball->setPosition((float)SCREEN_WIDTH / 2.f, 715.f);
//}
//
////void Level_1::HandleInput()
////{
////	sf::Event event;
////	while (_data->window.pollEvent(event))
////	{
////		if (sf::Event::Closed == event.type)
////		{
////			_data->window.close();
////		}
////		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
////		{
////			game_start = true;
////		}
////		if (event.type == sf::Event::MouseMoved && game_start)
////		{
////			setPaddlePosition(event);
////		}
////		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
////		{
////			game_start = false;
////			_data->machine.AddState(StateRef(new PauseState(_data, circleObjects, background, score)), false);
////		}
////	}
////}
//
////void Level_1::Update(float dt)
////{
////
////}
//
//
////void Level_1::Draw(float dt)
////{
////
////}
