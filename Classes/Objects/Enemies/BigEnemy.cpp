#include "BigEnemy.h"

//Constructor
BigEnemy::BigEnemy(sf::Vector2f Pos) : BaseEnemy(Pos)
{
	//Main Body Color
	circle.setFillColor(sf::Color(255, 0, 0, 255));

	//Barrel size and position
	barrel.setSize(sf::Vector2f(50, 30));
	barrel.setOrigin(sf::Vector2f(0, 15));
	barrel.setPosition(Pos);

	//set stats for big enemy
	maxHealth = 150;
	speed = 50.0f;
	health = 150;
	cooldown = 2.5f;
	dmg = 45;
}

//Destructor
BigEnemy::~BigEnemy()
{

}

void BigEnemy::ResetCooldown()
{
	cooldown = 2.5;
}
