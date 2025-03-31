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
		int Points;

		sf::Vector2f Direction;
		float length;
		
		void calculateMovement(sf::Vector2f MousePos);
		void movePlayer(sf::Vector2f MousePos, int WindowXSize, int WindowYSize, float dt);
		void rotatePlayer(sf::Vector2f MousePos);

	public:

		void DrawPlayer(sf::RenderWindow& window);
		void TransformPlayer(sf::Vector2f MousePos, int WindowXSize, int WindowYSize, float dt, bool IsPlayerMove);
		void AddPoint();
		void SetPlayerXPosition(float value);
		void SetPlayerYPosition(float value);
		
		sf::Vector2f getPosition();
		int getPoints();
		int getHealth();
		float getCooldown();
		float getPlayerRadius();
};