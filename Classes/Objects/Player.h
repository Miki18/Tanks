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

		//Variables
		int Health;
		float Cooldown;
		float PlayerSpeed;
		int Points;

		//Variables for movement
		sf::Vector2f Direction;
		float length;
		
		//Movement functions (using inside this class)
		void calculateMovement(sf::Vector2f MousePos);
		void movePlayer(sf::Vector2f MousePos, int WindowXSize, int WindowYSize, float dt);
		void rotatePlayer(sf::Vector2f MousePos);

	public:
		//Functions
		void DrawPlayer(sf::RenderWindow& window);
		void TransformPlayer(sf::Vector2f MousePos, int WindowXSize, int WindowYSize, float dt, bool IsPlayerMove);
		void AddPoint();

		//Setters
		void SetPlayerXPosition(float value);
		void SetPlayerYPosition(float value);
		
		//Getters
		sf::Vector2f getPosition();
		int getPoints();
		int getHealth();
		float getCooldown();
		float getPlayerRadius();
};