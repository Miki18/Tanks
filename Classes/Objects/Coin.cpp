#include "Coin.h"

Coin::Coin(sf::Texture& tex, sf::Vector2f pos) : tex(tex), sprite(tex)
{
	sprite.setScale(sf::Vector2f(0.08, 0.1));
	sprite.setOrigin(sf::Vector2f(225 , 250));
	sprite.setPosition(pos);
}

void Coin::DrawCoin(sf::RenderWindow& window)
{
	window.draw(sprite);
}

sf::Vector2f Coin::getPosition()
{
	return sprite.getPosition();
}
