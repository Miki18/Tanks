#include "Bullet.h"

//Constructor
Bullet::Bullet(sf::Vector2f TankPosition, sf::Vector2f MousePos, int WindowXSize, int WindowYSize)
{
	//Visual
	circle.setRadius(9.0f);
	circle.setOutlineThickness(2.0f);
	circle.setOrigin(circle.getGeometricCenter());
	circle.setFillColor(sf::Color::Yellow);
	circle.setOutlineColor(sf::Color::Black);

	this->WindowXSize = WindowXSize;
	this->WindowYSize = WindowYSize;

	//We set bullet's starter position
	CalculateDirection(TankPosition, MousePos);
	circle.move(TankPosition + Direction * 40.f);
}

//Draw function
void Bullet::DrawBullet(sf::RenderWindow& window)
{
	window.draw(circle);
}

//Calculate direction where bullet should move
void Bullet::CalculateDirection(sf::Vector2f BulletPosition, sf::Vector2f MousePosition)
{
	Direction = { MousePosition.x - BulletPosition.x, MousePosition.y - BulletPosition.y };
	float length = sqrt((Direction.x * Direction.x) + (Direction.y * Direction.y));
	Direction = Direction / length;
}

//Move bullet function
void Bullet::MoveBullet(float dt)
{
	circle.move(Direction * BulletSpeed * dt);
}

//Check if bullet will not go outside the map
bool Bullet::CheckBullet()
{
	if (circle.getPosition().x > WindowXSize or circle.getPosition().x < 0)
	{
		return true;
	}

	if (circle.getPosition().y > WindowYSize or circle.getPosition().y < 0)
	{
		return true;
	}
	return false;
}

//getters
sf::Vector2f Bullet::getBulletPosition()
{
	return circle.getPosition();
}

float Bullet::getBulletSize()
{
	return 11.0f;
}
