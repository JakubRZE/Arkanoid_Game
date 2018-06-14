#include "FlashScreen.h"



FlashScreen::FlashScreen(GameDataRef data) : _data(data)
{
	_shape.setSize(sf::Vector2f( _data->window.getSize().x , _data->window.getSize().y));
	_shape.setFillColor(sf::Color(255, 255, 255, 0));
}

void FlashScreen::Show()
{
	sf::Clock clock;

	while (_isFlashing)
	{
		sf::Time elapsed = clock.getElapsedTime();

		_shape.setFillColor(sf::Color(255, 255, 255, 6 * elapsed.asSeconds() ));

		if (_shape.getFillColor().a >= 255.f)
		{
			_isFlashing = false;
		}
	}
}

void FlashScreen::Draw()
{
	_data->window.draw(_shape);
}
