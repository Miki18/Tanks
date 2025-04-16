#pragma once
#include "BaseEnemy.h"

class NormalEnemy : public BaseEnemy
{
	public:
		//Constructor
		NormalEnemy(sf::Vector2f Pos);

		//Destructor
		~NormalEnemy();

		void ResetCooldown();
};

