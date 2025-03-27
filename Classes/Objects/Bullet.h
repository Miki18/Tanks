#pragma once
#include "../Headers.h"

class Bullet
{
	private:
		float BulletRadius = 9.0f;
		sf::CircleShape circle;

		sf::Vector2f Direction;

		int WindowXSize;
		int WindowYSize;

		float BulletSpeed = 400;
	
	public:

		Bullet(sf::Vector2f StarterPosition, sf::Vector2f MousePos, int WindowXSize, int WindowYSize);
		void DrawBullet(sf::RenderWindow& window);
		void CalculateDirection(sf::Vector2f BulletPosition, sf::Vector2f MousePosition);
		void MoveBullet(float dt);
		bool CheckBullet();
};

