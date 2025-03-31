#pragma once
#include "../Headers.h"

class Wall
{
	private:
		sf::RectangleShape square;

	public:
		Wall(sf::Vector2f Position);

		sf::Vector2f getPosition();

		void DrawWall(sf::RenderWindow& window);
		float getWallSize();
};

