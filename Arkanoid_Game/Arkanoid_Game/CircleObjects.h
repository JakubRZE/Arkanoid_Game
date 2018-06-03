#pragma once

#include <SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include "Game.h"
#include "Definitions.h"

#include <vector>


class CircleObjects : public sf::Drawable
{
public:
	CircleObjects(GameDataRef data); //float radius, sf::Vector2f position, sf::Color color
	~CircleObjects() = default;

	int randomizer();
	int rand_poz_x();
	int rand_poz_y();

	sf::Vector2f getPosition() const;
	float getRadius() const;

private:
	GameDataRef _data;

	sf::CircleShape o_shape;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

