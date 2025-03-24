#pragma once
#include "../Headers.h"

class Player
{
	public:
		//Player constructor
		Player(sf::Vector2f PlayerPos);

	private:

		//Player Graphic
		sf::CircleShape circle;
		sf::RectangleShape rectangle;

		int Health;
		float Cooldown;
		float PlayerSpeed;

		sf::Vector2f Direction;
		float length;
		
		void calculateMovement(sf::Vector2f MousePos);
		void movePlayer(sf::Vector2f MousePos, int WindowXSize, int WindowYSize, float dt);
		void rotatePlayer(sf::Vector2f MousePos);

	public:

		void DrawPlayer(sf::RenderWindow& window);
		void TransformPlayer(sf::Vector2f MousePos, int WindowXSize, int WindowYSize, float dt, bool IsPlayerMove);
		
		sf::Vector2f getPosition();
};

