#pragma once

#include <SFML\Graphics.hpp>

class InputManager
{
public:
	InputManager() {}
	~InputManager() {}

	bool IsSpriteClicked(sf::RectangleShape object, sf::Mouse::Button button, sf::RenderWindow& window);
	bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

	bool IsSpriteHovered(sf::RectangleShape &object, sf::RenderWindow& window);

	sf::Vector2i GetMousePosition(sf::RenderWindow& window);
};

