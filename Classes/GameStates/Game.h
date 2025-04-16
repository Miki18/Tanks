//includes
#pragma once
#include "../Headers.h"
#include "../Objects/Player.h"
#include "../Objects/Bullet.h"
#include "../Objects/Coin.h"
#include "../Objects/Wall.h"
#include "../Objects/PowerUp.h"
#include "../Objects/Enemies/BaseEnemy.h"
#include "../Objects/Enemies/NormalEnemy.h"
#include "../Objects/Enemies/BigEnemy.h"
#include "../Objects/Enemies/FastEnemy.h"

class Game
{
private:
	//Enum with all object types
	enum ObjectType
	{
		CoinType,
		EnemyType,
		PowerUpType
	};

	//variables for state manage
	sf::RenderWindow& window;
	bool& changeState;
	int& level;
	int& Score;

	//Window constant values
	const int WindowXSize = 1600;
	const int WindowYSize = 900;

	//Create player class
	//And arrays for objects
	Player player;
	std::vector<BaseEnemy*>enemies;
	std::vector<Bullet> bullets;
	std::vector<Coin> coins;
	std::vector<Wall> walls;
	std::vector<PowerUp> powerups;

	//define clock
	//and time variables
	sf::Clock deltaClock;

	float TimeUntilCoinSpawn = 1.0f;
	float TimeUntilPowerUpSpawn = rand()%10 + 5;     //PowerUp spawns every 4 - 8 seconds
	float TimeUntilEnemySpawn = 15.0f;     //this is used to count down time until next enemy spawns
	float NextEnemySpawnAfter = 15.0f;     //this is used to reset TimeUntilEnemySpawn. It is necessary to use new variable, because time will not have constant value
	float TimeSincePlayerShoot = 100.0f;   //this time is set to 100, because when player shoots it will be set to 0 and increase every frame

	//Mouse position
	sf::Vector2f CurrentMousePos = {0, 0};

	//Texture
	sf::Texture CoinText;

	//to control player movement
	bool MovePlayer = false;

	//load and create level
	void LoadLevel(int LevelNumber);
	
	//Functions for object spawning
	void ObjectSpawningControl(float dt);
	bool SpawnObject(int PosX, int PosY, ObjectType Object);
	void SpawnObjectAlgorithm(int PosX, int PosY, ObjectType Object, int Iteration);

	//Collision functions
	void Player_CoinsCollision();
	void Wall_PlayerCollision(int wall_number);
	void Wall_BulletCollision(int wall_number);
	void Wall_EnemesCollision(int wall_number);
	void Player_BulletsCollision(int* bulletNum);
	void Enemies_BulletsCollision(int* bulletNum);
	void Player_PowerupsCollision();
	void EnemyVisionLimitedbyWalls(int enemyNum);

	//ImGui Part
	void ImGuiRender();
	void ImGuiHeathAndPoinsWindow();

public:
	//constructor
	Game(sf::RenderWindow& window, bool& changeState, int& level, int& Score);

	//input, update, render
	void input();
	void update();
	void render();
};