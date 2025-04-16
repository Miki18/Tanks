#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f pos, int type)
{
	circle.setRadius(16.0f);
	circle.setFillColor(sf::Color{ 255, 255, 255, 255 });
	circle.setOutlineThickness(4.0f);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOrigin(circle.getGeometricCenter());
	circle.setPosition(pos);

	//speed and quickfire has higher probability than heal
	if (type == 0 or type == 1 or type == 2)
	{
		this->type = 0;
		circle.setFillColor(sf::Color{ 255, 255, 0, 255 });   //change later for real textures
	}
	else if (type == 3 or type == 4 or type == 5)
	{
		this->type = 1;
		circle.setFillColor(sf::Color{ 255, 0, 255, 255 });
	}
	else if (type == 6)
	{
		this->type = 2;
		circle.setFillColor(sf::Color{ 0, 255, 255, 255 });
	}
}

void PowerUp::drawPowerUp(sf::RenderWindow& window)
{
	window.draw(circle);
}

sf::Vector2f PowerUp::getPowerupPos()
{
	return circle.getPosition();
}

int PowerUp::getType()
{
	return type;
}

float PowerUp::getRadius()
{
	return 20.0f;
}
