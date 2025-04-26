#pragma once
#include "../Headers.h"

class Coin
{
	private:
		//Visual
		sf::Texture tex;
		sf::CircleShape circle;

	public:
		//Constructor
		Coin(sf::Texture& tex, sf::Vector2f pos);

		//Draw function
		void DrawCoin(sf::RenderWindow& window);

		//getters
		sf::Vector2f getPosition();
		float getRadius();
};