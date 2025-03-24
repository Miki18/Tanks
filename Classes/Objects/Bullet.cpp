#include "Bullet.h"

Bullet::Bullet(sf::Vector2f TankPosition, sf::Vector2f MousePos, int WindowXSize, int WindowYSize)
{
	circle.setOrigin(circle.getGeometricCenter());
	circle.setRadius(BulletRadius);
	circle.setOutlineThickness(3.0f);
	circle.setFillColor(sf::Color::Yellow);
	circle.setOutlineColor(sf::Color::Black);

	this->WindowXSize = WindowXSize;
	this->WindowYSize = WindowYSize;

	CalculateDirection(TankPosition, MousePos);
	circle.move(TankPosition + Direction * 40.f);
}

void Bullet::DrawBullet(sf::RenderWindow& window)
{
	window.draw(circle);
}

void Bullet::CalculateDirection(sf::Vector2f BulletPosition, sf::Vector2f MousePosition)
{
	Direction = { MousePosition.x - BulletPosition.x, MousePosition.y - BulletPosition.y };
	float length = sqrt((Direction.x * Direction.x) + (Direction.y * Direction.y));
	Direction = Direction / length;
}

void Bullet::MoveBullet(float dt)
{
	circle.move(Direction * BulletSpeed * dt * 1000.f);
}

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
