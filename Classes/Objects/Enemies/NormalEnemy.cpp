#include "NormalEnemy.h"

//Constructor
NormalEnemy::NormalEnemy(sf::Vector2f Pos) : BaseEnemy(Pos)
{
	//Main Body Color
	circle.setFillColor(sf::Color{ 100, 0, 0, 255 });

	//Barrel set size and position
	barrel.setSize(sf::Vector2f(40, 15));
	barrel.setOrigin(sf::Vector2f(0, 7.5));
	barrel.setPosition(Pos);

	//no need to set stats here
}

//Destructor
NormalEnemy::~NormalEnemy()
{

}

void NormalEnemy::ResetCooldown()
{
	cooldown = 0.75f;
}
