#pragma once
#include "../Headers.h"

class PowerUp
{
	private:
		sf::Texture tex;
		sf::CircleShape circle;

		int type = 0;      //powerup type; 0 is speed, 1 is quickfire, 2 is heal

	public:
		//Constructor
		PowerUp(sf::Vector2f pos, int type, sf::Texture& tex);

		//Draw
		void drawPowerUp(sf::RenderWindow& window);

		//getters
		sf::Vector2f getPowerupPos();
		int getType();
		float getRadius();
};