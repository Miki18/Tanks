#include "Wall.h"

//Constructor
Wall::Wall(sf::Vector2f Position)
{
	square.setSize(sf::Vector2f(45,45));
	square.setOutlineThickness(5);
	square.setFillColor(sf::Color(102,65,65,255));
	square.setOutlineColor(sf::Color::Black);
	square.setOrigin(square.getGeometricCenter());
	square.setPosition(Position);
}

//Draw
void Wall::DrawWall(sf::RenderWindow& window)
{
	window.draw(square);
}

//Getters
sf::Vector2f Wall::getPosition()
{
	return square.getPosition();
}

float Wall::getWallSize()
{
	return 50.0f;
}
