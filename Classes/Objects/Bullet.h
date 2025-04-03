#pragma once
#include "../Headers.h"

class Bullet
{
	private:
		//Shape (circle) and direction
		sf::CircleShape circle;

		sf::Vector2f Direction;

		//Window size
		int WindowXSize;
		int WindowYSize;

		//Bullet speed
		float BulletSpeed = 400;
	
	public:

		//Constructor
		Bullet(sf::Vector2f StarterPosition, sf::Vector2f MousePos, int WindowXSize, int WindowYSize);

		//functions
		void DrawBullet(sf::RenderWindow& window);
		void CalculateDirection(sf::Vector2f BulletPosition, sf::Vector2f MousePosition);
		void MoveBullet(float dt);
		bool CheckBullet();
		
		//getters
		sf::Vector2f getBulletPosition();
		float getBulletSize();
};

