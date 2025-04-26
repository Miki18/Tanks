#include "BaseEnemy.h"

//It calculate distance between enemy and player
void BaseEnemy::CalculateDistanceToPlayer(sf::Vector2f PlayerPos)
{
	DistanceToPlayer = (sqrt(pow(PlayerPos.x - circle.getPosition().x, 2) + pow(PlayerPos.y - circle.getPosition().y, 2)));
}

//Constructor
BaseEnemy::BaseEnemy(sf::Vector2f Pos)
{
	//Main Body
	circle.setPosition(Pos);
	circle.setRadius(20.0f);
	circle.setOutlineThickness(5.0f);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOrigin(circle.getGeometricCenter());

	//Barrel
	barrel.setFillColor(sf::Color{ 128, 128, 128, 255 });
	barrel.setOutlineThickness(5.0f);
	barrel.setOutlineColor(sf::Color::Black);

	ChooseStartRotation();
}

//Destructor
BaseEnemy::~BaseEnemy()
{
}

//movement
//Starting rotation
//Using in constructor
//fully random
void BaseEnemy::ChooseStartRotation()
{
	sf::Angle rotate_value = sf::degrees(rand() % 90 + 90);
	circle.rotate(rotate_value);
	barrel.rotate(rotate_value);
}

//choose random rotation
//using in game after for example collision with wall
//it rotates at least 90 degrees
void BaseEnemy::ChooseRandomRotation()
{
	if (rand() % 2 == 0)
	{
		sf::Angle rotate_value = sf::degrees(rand() % 90 + 90);
		circle.rotate(rotate_value);
		barrel.rotate(rotate_value);
	}
	else
	{
		sf::Angle rotate_value = sf::degrees(rand() % 90 + 90);
		circle.rotate(-rotate_value);
		barrel.rotate(-rotate_value);
	}
}

//Move enemy function
void BaseEnemy::MoveEnemy(int WindowXSize, int WindowYSize, float dt)
{
	//if distance to player is lower than 80 then enemy see player - he will not move
	if (DistanceToPlayer < 80 and SeePlayer == true)
	{
		//Do not move
	}
	else
	{
		float current_rotation = circle.getRotation().asRadians();

		sf::Vector2f dir(std::cos(current_rotation), std::sin(current_rotation));
		circle.move(dir * speed * dt);
		barrel.move(dir * speed * dt);
		KeepEnemyInMap(WindowXSize, WindowYSize);
	}

	//we set it false, because in the next frame we check again if enemy sees player and if it sees we will change it to true before it moves
	SeePlayer = false;
}

//Enemies can't go outside the map
void BaseEnemy::KeepEnemyInMap(int WindowXSize, int WindowYSize)
{
	if (circle.getPosition().x < getEnemyRadius())
	{
		circle.setPosition(sf::Vector2f(getEnemyRadius(), circle.getPosition().y));
		barrel.setPosition(sf::Vector2f(getEnemyRadius(), barrel.getPosition().y));
		ChooseRandomRotation();
	}
	else if (getEnemyPosition().x > WindowXSize - getEnemyRadius())
	{
		circle.setPosition(sf::Vector2f(WindowXSize - getEnemyRadius(), circle.getPosition().y));
		barrel.setPosition(sf::Vector2f(WindowXSize - getEnemyRadius(), barrel.getPosition().y));
		ChooseRandomRotation();
	}

	if (getEnemyPosition().y < getEnemyRadius())
	{
		circle.setPosition(sf::Vector2f(circle.getPosition().x, getEnemyRadius()));
		barrel.setPosition(sf::Vector2f(barrel.getPosition().x, getEnemyRadius()));
		ChooseRandomRotation();
	}
	else if (getEnemyPosition().y > WindowYSize - getEnemyRadius())
	{
		circle.setPosition(sf::Vector2f(circle.getPosition().x, WindowYSize - getEnemyRadius()));
		barrel.setPosition(sf::Vector2f(barrel.getPosition().x, WindowYSize - getEnemyRadius()));
		ChooseRandomRotation();
	}
}

//Check if enemy sees player
bool BaseEnemy::IsEnemySeePlayer(sf::Vector2f PlayerPos)
{
	//calculate distance
	CalculateDistanceToPlayer(PlayerPos);

	//If distance is lower than 80 then enemy always sees player
	if (DistanceToPlayer < 80)
	{
		return true;
	}
	//else do raycasting
	else if (DistanceToPlayer < 750)
	{
		//Calculate normalized Vector from enemy to player
		sf::Vector2f ToPlayer = { (PlayerPos.x - circle.getPosition().x)/DistanceToPlayer, (PlayerPos.y - circle.getPosition().y)/DistanceToPlayer};

		//Enemy move Vector
		float current_rotation = circle.getRotation().asRadians();
		sf::Vector2f dir(std::cos(current_rotation), std::sin(current_rotation));

		//DotProduct
		float DotProduct = ToPlayer.x * dir.x + ToPlayer.y * dir.y;

		//Because we used normalized vectors we can just do DotProduct = cos(angle) and calculate that angle
		float angleToPlayer = std::acos(DotProduct) * 180 / 3.14;

		//If angle is smaller than 50 in left or right than enemy sees player
		if (angleToPlayer <= 50)
		{
			//Enemy can see player - return true
			return true;
		}
	}

	return false;
	//if raycasting also do not detect player than idle
}

//It rotates enemy so it is facing to specyfic point)
void BaseEnemy::RotateToPoint(sf::Vector2f PointCoord)
{
	sf::Vector2f direction = { PointCoord.x - circle.getPosition().x, PointCoord.y - circle.getPosition().y };
	circle.setRotation(sf::degrees(-std::atan2(-direction.y, direction.x) * 180 / 3.14));
	barrel.setRotation(sf::degrees(-std::atan2(-direction.y, direction.x) * 180 / 3.14));
}

void BaseEnemy::EnemySawPlayer()
{
	SeePlayer = true;
}

//Draw function
void BaseEnemy::drawEnemy(sf::RenderWindow& window)
{
	window.draw(barrel);
	window.draw(circle);
}

void BaseEnemy::TakeDamage(int dmg)
{
	health -= dmg;
}

void BaseEnemy::LowerCooldown(float dt)
{
	cooldown = cooldown - dt;
}

void BaseEnemy::ResetCooldown()
{
}

//getters
sf::Vector2f BaseEnemy::getEnemyPosition()
{
	return circle.getPosition();
}

float BaseEnemy::getEnemyRadius()
{
	return 25.0f;
}

int BaseEnemy::getEnemyHealth()
{
	return health;
}

float BaseEnemy::getDistanceToPlayer()
{
	return DistanceToPlayer;
}

float BaseEnemy::getCooldown()
{
	return cooldown;
}

float BaseEnemy::getDamage()
{
	return dmg;
}

float BaseEnemy::getMaxHealth()
{
	return maxHealth;
}

void BaseEnemy::setXPos(float X)
{
	circle.setPosition(sf::Vector2f(X, circle.getPosition().y));
	barrel.setPosition(sf::Vector2f(X, barrel.getPosition().y));
}

void BaseEnemy::setYPos(float Y)
{
	circle.setPosition(sf::Vector2f(circle.getPosition().x, Y));
	barrel.setPosition(sf::Vector2f(barrel.getPosition().x, Y));
}
