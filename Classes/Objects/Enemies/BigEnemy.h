#pragma once
#include "BaseEnemy.h"
class BigEnemy : public BaseEnemy
{
	public:
		//Constructor
		BigEnemy(sf::Vector2f Pos);

		//Destructor
		~BigEnemy();

		void ResetCooldown();
};

