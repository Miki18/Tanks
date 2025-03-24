#include "Player.h"

//Constructor
Player::Player(sf::Vector2f PlayerPos)
{
	circle.setRadius(25.0f);
	circle.setFillColor(sf::Color{ 0, 100, 0, 255 });
	circle.setOutlineThickness(5.0f);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOrigin(circle.getGeometricCenter());

	rectangle.setSize(sf::Vector2f(50, 22));
	rectangle.setFillColor(sf::Color{128, 128, 128, 255});
	rectangle.setOutlineThickness(5.0f);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOrigin(sf::Vector2f(0, 11.0));

	circle.setPosition(PlayerPos);
	rectangle.setPosition(PlayerPos);

	Health = 100;
	Cooldown = 0.75;
	PlayerSpeed = 10;
}

void Player::calculateMovement(sf::Vector2f MousePos)
{
	Direction = { MousePos.x - circle.getPosition().x, MousePos.y - circle.getPosition().y };   //direction
	length = sqrt((Direction.x * Direction.x) + (Direction.y * Direction.y));     //lenght
	if (length != 0)    //check if length != 0 to avoid division by 0
	{
		Direction = { Direction / length };   //Normalize
	}
}

void Player::movePlayer(sf::Vector2f MousePos, int WindowXSize, int WindowYSize, float dt)
{
	circle.move(Direction * PlayerSpeed * dt * 1000.0f);
	rectangle.move(Direction * PlayerSpeed * dt * 1000.0f);

	//Check if player will go outside map
	//We can check only circle position, because rectangle has the same position as circle
	if (circle.getPosition().x < 0)
	{
		circle.setPosition(sf::Vector2f{ 0, circle.getPosition().y});
		rectangle.setPosition(sf::Vector2f{ 0, rectangle.getPosition().y });
	}
	else if (circle.getPosition().x > WindowXSize)
	{
		circle.setPosition(sf::Vector2f{ static_cast<float>(WindowXSize), circle.getPosition().y });
		rectangle.setPosition(sf::Vector2f{ static_cast<float>(WindowXSize), rectangle.getPosition().y });
	}

	if (circle.getPosition().y < 0)
	{
		circle.setPosition(sf::Vector2f{ circle.getPosition().x, 0 });
		rectangle.setPosition(sf::Vector2f{ rectangle.getPosition().x, 0 });
	}
	else if (circle.getPosition().y > WindowYSize)
	{
		circle.setPosition(sf::Vector2f{ circle.getPosition().x, static_cast<float>(WindowYSize) });
		rectangle.setPosition(sf::Vector2f{ rectangle.getPosition().x, static_cast<float>(WindowYSize) });
	}
}

void Player::rotatePlayer(sf::Vector2f MousePos)
{
	double a, b;
	a = MousePos.x - circle.getPosition().x;
	b = MousePos.y - circle.getPosition().y;
	float angle = -atan2(a, b) * 180 / 3.14;
	circle.setRotation(sf::degrees(angle + 90));
	rectangle.setRotation(sf::degrees(angle + 90));
}

void Player::DrawPlayer(sf::RenderWindow& window)
{
	window.draw(rectangle);
	window.draw(circle);
}

void Player::TransformPlayer(sf::Vector2f MousePos, int WindowXSize, int WindowYSize, float dt, bool IsPlayerMove)
{
	calculateMovement(MousePos);

	if (IsPlayerMove)
	{
		movePlayer(MousePos, WindowXSize, WindowYSize, dt);
	}

	if (length > 1)
	{
		rotatePlayer(MousePos);
	}
}

sf::Vector2f Player::getPosition()
{
	return circle.getPosition();
}
