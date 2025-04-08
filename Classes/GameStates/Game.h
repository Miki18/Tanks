//includes
#pragma once
#include "../Headers.h"
#include "../Objects/Player.h"
#include "../Objects/Bullet.h"
#include "../Objects/Coin.h"
#include "../Objects/Wall.h"

class Game
{
private:
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
	std::vector<Bullet> bullets;
	std::vector<Coin> coins;
	std::vector<Wall> walls;

	//define clock
	//and time variables
	sf::Clock deltaClock;

	float TimeUntilCoinSpawn = 5.0f;
	float TimeSincePlayerShoot = 100.0f;   //this time is set to 100, because when player shoots it will be set to 0 and increase every frame

	//Mouse position
	sf::Vector2f CurrentMousePos = {0, 0};

	//Texture
	sf::Texture CoinText;

	//to control player movement
	bool MovePlayer = false;

	//load and create level
	void LoadLevel(int LevelNumber);
	
	//Functions connected with coins
	void CoinSpawningControl(float dt);
	bool SpawnCoin(int PosX, int PosY);
	void SpawnCoinAlgorithm(int PosX, int PosY, int Iteration);

	//Collision functions
	void Player_CoinsCollision();
	void Wall_PlayerCollision(int wall_number);
	void Wall_BulletCollision(int wall_number);

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