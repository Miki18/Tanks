#include "Player.h"

//Constructor
Player::Player(sf::Vector2f PlayerPos)
{
	//Visualization - main body
	circle.setRadius(20.0f);
	circle.setFillColor(sf::Color{ 0, 100, 0, 255 });
	circle.setOutlineThickness(5.0f);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOrigin(circle.getGeometricCenter());

	//Visualization - barrel
	rectangle.setSize(sf::Vector2f(40, 15));
	rectangle.setFillColor(sf::Color{128, 128, 128, 255});
	rectangle.setOutlineThickness(5.0f);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOrigin(sf::Vector2f(0, 7.5));

	//Set the same position for both
	circle.setPosition(PlayerPos);
	rectangle.setPosition(PlayerPos);

	//set variables values
	Health = 100;
	Cooldown = 0.75;
	PlayerSpeed = 150;
	Dmg = 20;
}

//Movement functions (using inside this class)

//Calculate direction
void Player::calculateMovement(sf::Vector2f MousePos)
{
	Direction = { MousePos.x - circle.getPosition().x, MousePos.y - circle.getPosition().y };   //direction
	length = sqrt((Direction.x * Direction.x) + (Direction.y * Direction.y));     //lenght
	if (length != 0)    //check if length != 0 to avoid division by 0
	{
		Direction = { Direction / length };   //Normalize
	}
}

//Move player
void Player::movePlayer(sf::Vector2f MousePos, int WindowXSize, int WindowYSize, float dt)
{
	circle.move(Direction * PlayerSpeed * dt);
	rectangle.move(Direction * PlayerSpeed * dt);

	//Check if player will go outside map
	//We can check only circle position, because rectangle has the same position as circle
	if (circle.getPosition().x < getPlayerRadius())
	{
		circle.setPosition(sf::Vector2f(getPlayerRadius(), circle.getPosition().y));
		rectangle.setPosition(sf::Vector2f(getPlayerRadius(), rectangle.getPosition().y));
	}
	else if (getPosition().x > WindowXSize - getPlayerRadius())
	{
		circle.setPosition(sf::Vector2f(WindowXSize - getPlayerRadius(), circle.getPosition().y));
		rectangle.setPosition(sf::Vector2f(WindowXSize - getPlayerRadius(), rectangle.getPosition().y));
	}

	if (getPosition().y < getPlayerRadius())
	{
		circle.setPosition(sf::Vector2f(circle.getPosition().x, getPlayerRadius()));
		rectangle.setPosition(sf::Vector2f(rectangle.getPosition().x, getPlayerRadius()));
	}
	else if (getPosition().y > WindowYSize - getPlayerRadius())
	{
		circle.setPosition(sf::Vector2f(circle.getPosition().x, WindowYSize - getPlayerRadius()));
		rectangle.setPosition(sf::Vector2f(rectangle.getPosition().x, WindowYSize - getPlayerRadius()));
	}
}

//rotate player
void Player::rotatePlayer(sf::Vector2f MousePos)
{
	double a, b;
	a = MousePos.x - circle.getPosition().x;
	b = MousePos.y - circle.getPosition().y;
	float angle = -atan2(a, b) * 180 / 3.14;
	circle.setRotation(sf::degrees(angle + 90));
	rectangle.setRotation(sf::degrees(angle + 90));
}

//Functions
//Draw function
void Player::DrawPlayer(sf::RenderWindow& window)
{
	window.draw(rectangle);
	window.draw(circle);
}

//Player move and rotaton
//It manages the whole movement - calculate if player should move or rotate depends given data
void Player::TransformPlayer(sf::Vector2f MousePos, int WindowXSize, int WindowYSize, float dt, bool IsPlayerMove)
{
	//calculate direciton
	calculateMovement(MousePos);

	//Player move only when mouse button is pressed
	if (IsPlayerMove)
	{
		movePlayer(MousePos, WindowXSize, WindowYSize, dt);
	}

	//Player rotation works only when cursor is further than 1 from player's center to avoid rapid rotation
	if (length > 1)
	{
		rotatePlayer(MousePos);
	}
}

//damage player (no need to check if helth>0 - it is done in game.cpp)
void Player::TakeDamage(int dmg)
{
	Health = Health - dmg;
}

//Count down timer until it 0 or less
//If 0 or less - remove power up (that is - set base value)
void Player::CountSpeedTimer(float dt)
{
	if (SpeedTimer > 0)
	{
		SpeedTimer -= dt;
		if (SpeedTimer <= 0)
		{
			PlayerSpeed = 150;
		}
	}
}

void Player::CountQuickfireTimer(float dt)
{
	if (QuickfireTimer > 0)
	{
		QuickfireTimer -= dt;
		if (QuickfireTimer <= 0)
		{
			Cooldown = 0.75;
		}
	}
}

//Powerups function
void Player::GrantPlayerSpeed()
{
	//set player speed to 200 and reset timer
	PlayerSpeed = 250;
	SpeedTimer = 5;
}

void Player::GrantPlayerQuickfire()
{
	Cooldown = 0.25;
	QuickfireTimer = 5;
}

void Player::RestoreHealth()
{
	Health = 100;
}

//Setters
void Player::SetPlayerXPosition(float value)
{
	circle.setPosition(sf::Vector2f(value, circle.getPosition().y));
	rectangle.setPosition(sf::Vector2f(value, rectangle.getPosition().y));
}

void Player::SetPlayerYPosition(float value)
{
	circle.setPosition(sf::Vector2f(circle.getPosition().x, value));
	rectangle.setPosition(sf::Vector2f(rectangle.getPosition().x, value));
}

//Getters
sf::Vector2f Player::getPosition()
{
	return circle.getPosition();
}

int Player::getHealth()
{
	return Health;
}

float Player::getCooldown()
{
	return Cooldown;
}

float Player::getPlayerRadius()
{
	return 25.0f;
}

int Player::getDamage()
{
	return Dmg;
}
