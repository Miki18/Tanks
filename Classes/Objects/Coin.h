#pragma once
#include "../Headers.h"

class Coin
{
	private:
		sf::Texture tex;
		sf::Sprite sprite;

	public:
		Coin(sf::Texture& tex, sf::Vector2f pos);

		void DrawCoin(sf::RenderWindow& window);
		sf::Vector2f getPosition();
};