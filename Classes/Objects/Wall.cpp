#include "Wall.h"

Wall::Wall(sf::Vector2f Position)
{
	square.setSize(sf::Vector2f(45,45));
	square.setOutlineThickness(5);
	square.setFillColor(sf::Color(102,65,65,255));
	square.setOutlineColor(sf::Color::Black);
	square.setOrigin(square.getGeometricCenter());
	square.setPosition(Position);
}

sf::Vector2f Wall::getPosition()
{
	return square.getPosition();
}

void Wall::DrawWall(sf::RenderWindow& window)
{
	window.draw(square);
}

float Wall::getWallSize()
{
	return 50.0f;
}
