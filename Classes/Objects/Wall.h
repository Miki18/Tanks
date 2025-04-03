#pragma once
#include "../Headers.h"

class Wall
{
	private:
		//Visualization
		sf::RectangleShape square;

	public:
		//Constructor
		Wall(sf::Vector2f Position);

		//Draw
		void DrawWall(sf::RenderWindow& window);

		//getters
		sf::Vector2f getPosition();
		float getWallSize();
};

