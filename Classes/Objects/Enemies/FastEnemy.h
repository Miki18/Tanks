#pragma once
#include "BaseEnemy.h"
class FastEnemy : public BaseEnemy
{
	public:
		//Constructor
		FastEnemy(sf::Vector2f Pos);

		//Destructor
		~FastEnemy();

		void ResetCooldown();
};

