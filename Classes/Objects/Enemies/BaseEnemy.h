#pragma once
#include "../Headers.h"
//This is base class for all enemies

class BaseEnemy
{
	protected:
		//main body
		sf::CircleShape circle;
		sf::RectangleShape barrel;

		//stats
		//Default values = Normal Enemy values
		float speed = 150.0f;
		int health = 50;
		float cooldown = 0.75f;
		int dmg = 10;
		bool SeePlayer = false;

		//Distance to player is calculater every frame
		//When tanks spawns, DistanceToPlayer has high value so it will not inflict on enemies' behaviour
		float DistanceToPlayer = 1000.0f;

		//private functions for tanks that will not be used in game.cpp
		virtual void CalculateDistanceToPlayer(sf::Vector2f PlayerPos);

	public:
		//Constructor
		BaseEnemy() {};
		BaseEnemy(sf::Vector2f Pos);

		//Destructor
		~BaseEnemy();

		//movement
		virtual void ChooseStartRotation();
		virtual void ChooseRandomRotation();
		virtual void MoveEnemy(int WindowXSize, int WindowYSize, float dt);
		virtual void KeepEnemyInMap(int WindowXSize, int WindowYSize);
		//Detect player section
		virtual bool IsEnemySeePlayer(sf::Vector2f PlayerPos);
		virtual void RotateToPoint(sf::Vector2f PlayerPos);
		virtual void EnemySawPlayer();

		//Draw function
		virtual void drawEnemy(sf::RenderWindow& window);

		//function
		virtual void TakeDamage(int dmg);
		virtual void LowerCooldown(float dt);
		virtual void ResetCooldown();

		//getters
		virtual sf::Vector2f getEnemyPosition();
		virtual float getEnemyRadius();
		virtual int getEnemyHealth();
		virtual float getDistanceToPlayer();
		virtual float getCooldown();
		virtual float getDamage();

		//setters
		virtual void setXPos(float X);
		virtual void setYPos(float Y);
};