#pragma once
#include "../Headers.h"

class Coin
{
	private:
		//Visual
		sf::Texture tex;
		sf::Sprite sprite;

	public:
		//Constructor
		Coin(sf::Texture& tex, sf::Vector2f pos);

		//Draw function
		void DrawCoin(sf::RenderWindow& window);

		//get position
		sf::Vector2f getPosition();
};