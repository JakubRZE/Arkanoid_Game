#include "Ball.h"


Ball::Ball(const std::vector<sf::RectangleShape>& solidObjects,  std::vector<sf::CircleShape>& circleObjects, GameDataRef data)
	: m_solidObjects(solidObjects),
	m_circleObjects(circleObjects),
	m_velocity(1.2f, -0.75f), // ball movement adjustment
	_data(data)
{
	m_shape.setRadius(10.f);
	setOrigin(10.f, 10.f);

	m_velocity = normalise(m_velocity);
}


void Ball::update(float dt)
{
	//move the ball
	move(m_velocity * m_speed * dt);

	//check each object for collision
	sf::FloatRect overlap; //holds overlap data, if any
	sf::FloatRect ballBounds = getTransform().transformRect(m_shape.getLocalBounds()); //mutliply the shape bounds by our transform
	for (const auto& o : m_solidObjects)
	{
		if (o.getGlobalBounds().intersects(ballBounds, overlap))
		{
			auto collisionNormal = o.getPosition() - getPosition();
			auto manifold = getManifold(overlap, collisionNormal);
			resolve(manifold);
			break; //skip the rest of the objects
		}
	}

	//check circle shapes

	int m_size = m_circleObjects.size();
	bool isDeleting=false;
	int del_pos;

	for (int i = 0 ; i < m_size ; i++)
	{
		auto collisionNormal = m_circleObjects[i].getPosition() - getPosition();
		if (lengthSquared(collisionNormal) < ((m_circleObjects[i].getRadius() * m_circleObjects[i].getRadius()) + (m_shape.getRadius() * m_shape.getRadius())))
		{
			//we have a collision
			auto manifold = getManifold(m_circleObjects[i].getRadius() + m_shape.getRadius(), collisionNormal);
			resolve(manifold);
			//delate an object
			isDeleting = true;
			del_pos = i;
			break;
		}
	}

	if (!m_circleObjects.empty() && isDeleting)
	{
		m_circleObjects.erase(m_circleObjects.begin() + del_pos);
	}
}

sf::Vector3f Ball::getManifold(const sf::FloatRect& overlap, const sf::Vector2f& collisionNormal)
{
	//the collision normal is stored in x and y, with the penetration in z
	sf::Vector3f manifold;

	if (overlap.width < overlap.height)
	{
		manifold.x = (collisionNormal.x < 0) ? 1.f : -1.f;
		manifold.z = overlap.width;
	}
	else
	{
		manifold.y = (collisionNormal.y < 0) ? 1.f : -1.f;
		manifold.z = overlap.height;
	}

	return manifold;
}

sf::Vector3f Ball::getManifold(float summedDistance, const sf::Vector2f& collisionNormal)
{
	auto collisionDistance = std::sqrt(lengthSquared(collisionNormal));
	auto normal = normalise(collisionNormal);
	sf::Vector3f manifold;
	manifold.x = normal.x;
	manifold.y = normal.y;
	manifold.z = collisionDistance - summedDistance;
	return manifold;
}


void Ball::resolve(const sf::Vector3f& manifold)
{
	//move the ball out of the solid object by the penetration amount
	sf::Vector2f normal(manifold.x, manifold.y);
	move(normal * manifold.z);

	//reflect the current velocity to make the ball bounce
	m_velocity = reflect(m_velocity, normal);
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_shape, states);
}


	//------vector maths------//
float  Ball::dot(const sf::Vector2f& lv, const sf::Vector2f& rv)
{
	return lv.x * rv.x + lv.y * rv.y;
}

sf::Vector2f  Ball::normalise(sf::Vector2f source)
{
	float length = std::sqrt(dot(source, source));
	if (length != 0) source /= length;
	return source;
}

sf::Vector2f  Ball::reflect(const sf::Vector2f& velocity, const sf::Vector2f& normal)
{
	return -2.f * dot(velocity, normal) * normal + velocity;
}

float  Ball::lengthSquared(const sf::Vector2f& source)
{
	return dot(source, source);
}


