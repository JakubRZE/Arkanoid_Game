#include "CircleObjects.h"
#include <stdlib.h>
#include <time.h> 




CircleObjects::CircleObjects(GameDataRef data) : _data(data)
{	

	o_shape.setPosition(rand_poz_x(), rand_poz_y());
	o_shape.setRadius(randomizer());
	o_shape.setFillColor(sf::Color::White); 
	o_shape.setOrigin(o_shape.getRadius() / 2, o_shape.getRadius() / 2);

}

void CircleObjects::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->o_shape, states);
}

int CircleObjects::randomizer()
{
	/* initialize random seed: */
	srand(time(NULL));

	/* generate secret number between 1 and 10: */
	return rand() % 70 + 40;
}

int CircleObjects::rand_poz_x()
{
	/* initialize random seed: */
	srand(time(NULL));

	/* generate secret number between 1 and 10: */
	return rand() % SCREEN_WIDTH - 105 + 105;
}

int CircleObjects::rand_poz_y()
{
	/* initialize random seed: */
	srand(time(NULL));

	/* generate secret number between 1 and 10: */
	return rand() % SCREEN_HEIGHT - 350 + 105;
}

sf::Vector2f CircleObjects::getPosition() const
{
	return o_shape.getPosition();
}

float CircleObjects::getRadius() const
{
	return o_shape.getRadius();
}
