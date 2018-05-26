#pragma once
#include<SFML\Graphics.hpp>

class Entity
{
public:
	Entity() = default;
	~Entity() = default;

	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;

private:
	// initial sf::Vector2f is equal 0
	sf::Vector2f Velocity;
};

