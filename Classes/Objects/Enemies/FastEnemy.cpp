#include "FastEnemy.h"

//Constructor
FastEnemy::FastEnemy(sf::Vector2f Pos) : BaseEnemy(Pos)
{
	//Main Body Color
	circle.setFillColor(sf::Color(200, 100, 0, 255));

	//Barrel size and position
	barrel.setSize(sf::Vector2f(50, 12));
	barrel.setOrigin(sf::Vector2f(0, 6));
	barrel.setPosition(Pos);

	//set stats for big enemy
	speed = 250.0f;
	health = 25;
	cooldown = 0.3f;
	dmg = 3;
}

//Destructor
FastEnemy::~FastEnemy()
{
}

void FastEnemy::ResetCooldown()
{
	cooldown = 0.3f;
}
