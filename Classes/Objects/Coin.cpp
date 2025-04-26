#include "Coin.h"

//Constructor
//Game class gives texture when it creates object
Coin::Coin(sf::Texture& tex, sf::Vector2f pos) : tex(tex)
{
	circle.setTexture(&tex);
	circle.setRadius(20);
	circle.setScale(sf::Vector2f(0.9, 1.1));
	circle.setOrigin(circle.getGeometricCenter());
	circle.setPosition(pos);
}

//Draw function
void Coin::DrawCoin(sf::RenderWindow& window)
{
	window.draw(circle);
}

//get Position
sf::Vector2f Coin::getPosition()
{
	return circle.getPosition();
}

float Coin::getRadius()
{
	return 20;
}
