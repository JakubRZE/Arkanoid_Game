#include "Entity.h"

void Entity::setVelocity(sf::Vector2f velocity)
{
	Velocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	Velocity.x = vx;
	Velocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
	return Velocity;
}
