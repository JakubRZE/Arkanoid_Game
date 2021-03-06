#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

#include <vector>


class Ball final : public sf::Drawable, public sf::Transformable
{
public:
	explicit Ball(const std::vector<sf::RectangleShape>& solidObjects, std::vector<sf::CircleShape>& circleObjects, GameDataRef data);
	~Ball() = default;

	void update(float dt, bool game_start, int &_score);
	float getPosition_Y();
	void speedUp();

	//------vector maths------//
	float dot(const sf::Vector2f& lv, const sf::Vector2f& rv);
	sf::Vector2f normalise(sf::Vector2f source);
	sf::Vector2f reflect(const sf::Vector2f& velocity, const sf::Vector2f& normal);
	float lengthSquared(const sf::Vector2f& source);

private:

	GameDataRef _data;

	const std::vector<sf::RectangleShape>& m_solidObjects;
	std::vector<sf::CircleShape>& m_circleObjects;

	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;
	const float m_ballRadius{ 10.0f };
	float m_speed = 680.f;
	int scoreRate{ 10 };

	sf::Vector3f getManifold(const sf::FloatRect& overlap, const sf::Vector2f& collisionNormal);
	sf::Vector3f getManifold(float summedDistance, const sf::Vector2f& collisionNormal);
	void resolve(const sf::Vector3f& manifold);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};



