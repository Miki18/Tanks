#include "Coin.h"

//Constructor
//Game class gives texture when it creates object
Coin::Coin(sf::Texture& tex, sf::Vector2f pos) : tex(tex), sprite(tex)
{
	sprite.setScale(sf::Vector2f(0.08, 0.1));
	sprite.setOrigin(sf::Vector2f(250 , 300));
	sprite.setPosition(pos);
}

//Draw function
void Coin::DrawCoin(sf::RenderWindow& window)
{
	window.draw(sprite);
}

//get Position
sf::Vector2f Coin::getPosition()
{
	return sprite.getPosition();
}
