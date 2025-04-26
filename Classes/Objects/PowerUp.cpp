#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f pos, int type, sf::Texture& tex)
{
	circle.setRadius(16.0f);
	circle.setFillColor(sf::Color{ 255, 255, 255, 255 });
	circle.setOutlineThickness(4.0f);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOrigin(circle.getGeometricCenter());
	circle.setPosition(pos);

	//speed and quickfire has higher probability than heal
	//type 0 is speed, type 1 is quickfire, type 2 is heal
	this->type = type;
	circle.setTexture(&tex);
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
