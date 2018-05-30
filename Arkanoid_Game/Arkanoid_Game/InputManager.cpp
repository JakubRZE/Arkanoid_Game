#include "InputManager.h"


bool InputManager::IsSpriteClicked(const sf::RectangleShape object, sf::Mouse::Button button, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect ButtonRect{ object.getGlobalBounds() };

		if (ButtonRect.contains( sf::Mouse::getPosition(window)))
		{
			return true; 
		}
	}
	return false;
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}
