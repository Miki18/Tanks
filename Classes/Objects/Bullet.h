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
		int BulletDmg = 0;
		bool IsPlayers = false;
		sf::Vector2f ShooterPosition = { 0,0 };     //here will be player position when he shoots (when enemy spawns bullet here will be 0,0 and it will not be used)
	
	public:

		//Constructor
		Bullet(sf::Vector2f StarterPosition, sf::Vector2f MousePos, int WindowXSize, int WindowYSize, int Dmg, bool IsPlayers, float BulletSpeed);

		//functions
		void DrawBullet(sf::RenderWindow& window);
		void CalculateDirection(sf::Vector2f BulletPosition, sf::Vector2f MousePosition);
		void MoveBullet(float dt);
		bool CheckBullet();
		
		//getters
		sf::Vector2f getBulletPosition();
		float getBulletSize();
		bool getIsPlayers();
		int getDamage();
		sf::Vector2f getShooterPosition();
};

