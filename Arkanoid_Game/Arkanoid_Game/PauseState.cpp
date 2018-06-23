#include "PauseState.h"


PauseState::PauseState(GameDataRef data, std::vector<sf::CircleShape> &circle, sf::Sprite background, int &_score)
	: _data(data),
	circleObjects(circle),
	_background(background)	
{
	score = std::unique_ptr<int>(new int(_score));
}

void PauseState::Init()
{
	_data->window.setMouseCursorVisible(true);
	_shape.setSize(sf::Vector2f(_data->window.getSize()));
	_shape.setFillColor(sf::Color(0, 0, 0, 100));

	//title
	tittle1.setFont(this->_data->resource.GetFont("Intro"));
	tittle1.setString("GAME PAUSED");
	tittle1.setCharacterSize(50);
	tittle1.setOrigin(tittle1.getGlobalBounds().width / 2.f, tittle1.getGlobalBounds().height / 2.f);
	tittle1.setPosition(_data->window.getSize().x / 2.f , _data->window.getSize().y / 2.f + 50);

	tittle2.setFont(this->_data->resource.GetFont("Intro"));
	tittle2.setString("press ESCAPE to resume the game");
	tittle2.setCharacterSize(35);
	tittle2.setOrigin(tittle2.getGlobalBounds().width / 2.f, tittle2.getGlobalBounds().height / 2.f);
	tittle2.setPosition(_data->window.getSize().x / 2.f , tittle1.getPosition().y + 70);

	//menuButton 
	MenuButton.setSize({ 285, 40 });
	MenuButton.setFillColor(sf::Color(28, 52, 63, 160));
	MenuButton.setOrigin(MenuButton.getSize().x / 2.f, MenuButton.getSize().y / 2.f);
	MenuButton.setPosition(_data->window.getSize().x / 2.f, _data->window.getSize().y - 150.f);
	MenuButton.setOutlineThickness(3);
	MenuButton.setOutlineColor(sf::Color::White);
	//menuText
	MenuText.setFont(this->_data->resource.GetFont("Intro"));
	MenuText.setString("Return to Menu");
	MenuText.setFillColor(sf::Color::Red);
	MenuText.setCharacterSize(35);
	MenuText.setOrigin(MenuButton.getGlobalBounds().width / 2.f, MenuButton.getGlobalBounds().height / 2.f);
	MenuText.setPosition(MenuButton.getPosition().x + 8, MenuButton.getPosition().y);
}

void PauseState::HandleInput()
{

	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			_data->machine.RemoveState();
		}

		if (_data->input.IsSpriteClicked(MenuButton, sf::Mouse::Left, _data->window))
		{
			_data->resource.Play("Click");
			*score = 0;
			_data->machine.RemoveState();
			_data->machine.AddState(StateRef(new MenuState(this->_data)), true);
		}
	}
}

void PauseState::Update(float dt)
{
	if (_data->input.IsSpriteHovered(MenuButton, _data->window))
	{
		MenuButton.setFillColor(sf::Color(237, 14, 29, 90));
	}
	else
	{
		MenuButton.setFillColor(sf::Color(28, 52, 63, 160));
	}
}

void PauseState::Draw(float dt)
{
	_data->window.clear();

	_data->window.draw(_background);
	for (const auto& o : circleObjects)
	{
		_data->window.draw(o);
	}
	_data->window.draw(_shape);
	_data->window.draw(tittle1);
	_data->window.draw(tittle2);
	_data->window.draw(MenuButton);
	_data->window.draw(MenuText);

	_data->window.display();
}


